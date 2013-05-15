-------------------------------------------------------------------------------
--
-- Simple VGA raster display
--
-- Stephen A. Edwards
-- sedwards@cs.columbia.edu
--
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity de2_vga_raster is
  
  port (
    reset : in std_logic;
    clk   : in std_logic;                    -- Should be 25.125 MHz

    center: in std_logic_vector(15 downto 0) := X"f0f0"; -- circle center
    --chipselect : in std_logic;
    --write      : in std_logic;
    --address  :  in std_logic_vector(17 downto 0);
    --readdata : out std_logic_vector(15 downto 0);
    --writedata : in std_logic_vector(15 downto 0);
	 
    VGA_CLK,                         -- Clock
    VGA_HS,                          -- H_SYNC
    VGA_VS,                          -- V_SYNC
    VGA_BLANK,                       -- BLANK
    VGA_SYNC : out std_logic;        -- SYNC
    VGA_R,                           -- Red[9:0]
    VGA_G,                           -- Green[9:0]
    VGA_B : out unsigned(9 downto 0) -- Blue[9:0]
    );

end de2_vga_raster;

architecture rtl of de2_vga_raster is
  
  -- Video parameters
  
  constant HTOTAL       : integer := 800;
  constant HSYNC        : integer := 96;
  constant HBACK_PORCH  : integer := 48;
  constant HACTIVE      : integer := 640;
  constant HFRONT_PORCH : integer := 16;
  
  constant VTOTAL       : integer := 525;
  constant VSYNC        : integer := 2;
  constant VBACK_PORCH  : integer := 33;
  constant VACTIVE      : integer := 480;
  constant VFRONT_PORCH : integer := 10;

  --constant RECTANGLE_HSTART : integer := 100;
  --constant RECTANGLE_HEND   : integer := 240;
  --constant RECTANGLE_VSTART : integer := 100;
  --constant RECTANGLE_VEND   : integer := 180;
  
  -- Signals related to ball drawing 
  constant RADIUS	  : integer :=10;   --radius of the ball
  constant Hinitial : integer :=400;  --initial x value of the center of the ball
  constant Vinitial : integer :=263;  --initial y value of the center of the ball
  
	
  -- Signals for the video controller
  signal Hcount : unsigned(9 downto 0);  -- Horizontal position (0-800)
  signal Vcount : unsigned(9 downto 0);  -- Vertical position (0-524)
  signal EndOfLine, EndOfField : std_logic;

  signal vga_hblank, vga_hsync,
    vga_vblank, vga_vsync : std_logic;  -- Sync. signals

  signal rectangle_h, rectangle_v, rectangle : std_logic;  -- rectangle area
  
 -- signal center_in : unsigned(31 downto 0) := X"008000c0";

begin

  -- Horizontal and vertical counters

  HCounter : process (clk)
  begin
    if rising_edge(clk) then      
      if reset = '1' then
        Hcount <= (others => '0');
      elsif EndOfLine = '1' then
        Hcount <= (others => '0');
      else
        Hcount <= Hcount + 1;
      end if;      
    end if;
  end process HCounter;

  EndOfLine <= '1' when Hcount = HTOTAL - 1 else '0';
  
  VCounter: process (clk)
  begin
    if rising_edge(clk) then      
      if reset = '1' then
        Vcount <= (others => '0');
      elsif EndOfLine = '1' then
        if EndOfField = '1' then
          Vcount <= (others => '0');
        else
          Vcount <= Vcount + 1;
        end if;
      end if;
    end if;
  end process VCounter;

  EndOfField <= '1' when Vcount = VTOTAL - 1 else '0';

  -- State machines to generate HSYNC, VSYNC, HBLANK, and VBLANK

  HSyncGen : process (clk)
  begin
    if rising_edge(clk) then     
      if reset = '1' or EndOfLine = '1' then
        vga_hsync <= '1';
      elsif Hcount = HSYNC - 1 then
        vga_hsync <= '0';
      end if;
    end if;
  end process HSyncGen;
  
  HBlankGen : process (clk)
  begin
    if rising_edge(clk) then
      if reset = '1' then
        vga_hblank <= '1';
      elsif Hcount = HSYNC + HBACK_PORCH then
        vga_hblank <= '0';
      elsif Hcount = HSYNC + HBACK_PORCH + HACTIVE then
        vga_hblank <= '1';
      end if;      
    end if;
  end process HBlankGen;

  VSyncGen : process (clk)
  begin
    if rising_edge(clk) then
      if reset = '1' then
        vga_vsync <= '1';
      elsif EndOfLine ='1' then
        if EndOfField = '1' then
          vga_vsync <= '1';
        elsif Vcount = VSYNC - 1 then
          vga_vsync <= '0';
        end if;
      end if;      
    end if;
  end process VSyncGen;

  VBlankGen : process (clk)
  begin
    if rising_edge(clk) then    
      if reset = '1' then
        vga_vblank <= '1';
      elsif EndOfLine = '1' then
        if Vcount = VSYNC + VBACK_PORCH - 1 then
          vga_vblank <= '0';
        elsif Vcount = VSYNC + VBACK_PORCH + VACTIVE - 1 then
          vga_vblank <= '1';
        end if;
      end if;
    end if;
  end process VBlankGen;

  -- Rectangle generator

--  RectangleHGen : process (clk)
--  begin
--    if rising_edge(clk) then     
--      if reset = '1' or Hcount = HSYNC + HBACK_PORCH + RECTANGLE_HSTART then
--        rectangle_h <= '1';
--      elsif Hcount = HSYNC + HBACK_PORCH + RECTANGLE_HEND then
--		  rectangle_h <= '0';
--      end if;      
--    end if;
--  end process RectangleHGen;

--  RectangleVGen : process (clk)
--  begin
--    if rising_edge(clk) then
--      if reset = '1' then       
--        rectangle_v <= '0';
--      elsif EndOfLine = '1' then
--        if Vcount = VSYNC + VBACK_PORCH - 1 + RECTANGLE_VSTART then
--          rectangle_v <= '1';
--        elsif Vcount = VSYNC + VBACK_PORCH - 1 + RECTANGLE_VEND then
--          rectangle_v <= '0';
--        end if;
--      end if;      
--    end if;
--  end process RectangleVGen;

BallGen : process (clk)
variable distance_square : integer;
variable distance_H      : integer;
variable distance_V      : integer;
begin
   
	if rising_edge (clk) then
	distance_H := abs(TO_INTEGER(Hcount)- 3*TO_INTEGER(unsigned(center(7 downto 0)))-144);
	distance_V := abs(TO_INTEGER(Vcount)- 3*TO_INTEGER(unsigned(center(15 downto 8)))-35);
--	distance_H := abs(TO_INTEGER(Hcount)- Hinitial);
--	distance_V := abs(TO_INTEGER(Vcount)- Vinitial);
	distance_square :=(distance_H*distance_H)+(distance_V*distance_V);
		if reset = '1' then 
		rectangle_h<= '0';
		rectangle_v<= '0';
		elsif distance_square < RADIUS*RADIUS then
		rectangle_h<= '1';
		rectangle_v<= '1';
		else
		rectangle_h<= '0';
		rectangle_v<= '0';
		end if;
	end if;
end process BallGen;	
		
		
  rectangle <= rectangle_h and rectangle_v;

  -- Registered video signals going to the video DAC

  VideoOut: process (clk, reset)
  begin
    if reset = '1' then
      VGA_R <= "0000000000";
      VGA_G <= "0000000000";
      VGA_B <= "0000000000";
    elsif clk'event and clk = '1' then
      if rectangle = '1' then --color of ball
        VGA_R <= "1111111111";
        VGA_G <= "0000000000";
        VGA_B <= "1111111111";
      elsif vga_hblank = '0' and vga_vblank ='0' then
        VGA_R <= "0111011100"; --color of background
        VGA_G <= "1110000000";
        VGA_B <= "1110111000";
      else
        VGA_R <= "0000000000";
        VGA_G <= "0000000000";
        VGA_B <= "0000000000";    
      end if;
    end if;
  end process VideoOut;

  VGA_CLK <= clk;
  VGA_HS <= not vga_hsync;
  VGA_VS <= not vga_vsync;
  VGA_SYNC <= '0';
  VGA_BLANK <= not (vga_hsync or vga_vsync);

end rtl;
