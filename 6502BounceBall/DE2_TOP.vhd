--
-- DE2 top-level module
--
-- Stephen A. Edwards, Columbia University, sedwards@cs.columbia.edu
--
-- From an original by Terasic Technology, Inc.
-- (DE2_TOP.v, part of the DE2 system board CD supplied by Altera)
--

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

use work.ram_lib.all;
use work.components.all;

entity DE2_TOP is

  port (
    -- Clocks
    
    CLOCK_27,                                      -- 27 MHz
    CLOCK_50,                                      -- 50 MHz
    EXT_CLOCK : in std_logic;                      -- External Clock

    -- Buttons and switches
    
    KEY : in std_logic_vector(3 downto 0);         -- Push buttons
    SW : in std_logic_vector(17 downto 0);         -- DPDT switches

    -- LED displays

    HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7 -- 7-segment displays
       : out std_logic_vector(6 downto 0);         -- (active low)
    LEDG : out std_logic_vector(8 downto 0);       -- Green LEDs (active high)
    LEDR : out std_logic_vector(17 downto 0);      -- Red LEDs (active high)

    -- RS-232 interface

    UART_TXD : out std_logic;                      -- UART transmitter   
    UART_RXD : in std_logic;                       -- UART receiver

    -- IRDA interface

    IRDA_TXD : out std_logic;                      -- IRDA Transmitter
    IRDA_RXD : in std_logic;                       -- IRDA Receiver

    -- SDRAM
   
    DRAM_DQ : inout std_logic_vector(15 downto 0); -- Data Bus
    DRAM_ADDR : out std_logic_vector(11 downto 0); -- Address Bus    
    DRAM_LDQM,                                     -- Low-byte Data Mask 
    DRAM_UDQM,                                     -- High-byte Data Mask
    DRAM_WE_N,                                     -- Write Enable
    DRAM_CAS_N,                                    -- Column Address Strobe
    DRAM_RAS_N,                                    -- Row Address Strobe
    DRAM_CS_N,                                     -- Chip Select
    DRAM_BA_0,                                     -- Bank Address 0
    DRAM_BA_1,                                     -- Bank Address 0
    DRAM_CLK,                                      -- Clock
    DRAM_CKE : out std_logic;                      -- Clock Enable

    -- FLASH
    
    FL_DQ : inout std_logic_vector(7 downto 0);      -- Data bus
    FL_ADDR : out std_logic_vector(21 downto 0);  -- Address bus
    FL_WE_N,                                         -- Write Enable
    FL_RST_N,                                        -- Reset
    FL_OE_N,                                         -- Output Enable
    FL_CE_N : out std_logic;                         -- Chip Enable

    -- SRAM
    
    SRAM_DQ : inout unsigned(15 downto 0);         -- Data bus 16 Bits
    SRAM_ADDR : out unsigned(17 downto 0);         -- Address bus 18 Bits
    SRAM_UB_N,                                     -- High-byte Data Mask 
    SRAM_LB_N,                                     -- Low-byte Data Mask 
    SRAM_WE_N,                                     -- Write Enable
    SRAM_CE_N,                                     -- Chip Enable
    SRAM_OE_N : out std_logic;                     -- Output Enable

    -- USB controller
    
    OTG_DATA : inout std_logic_vector(15 downto 0); -- Data bus
    OTG_ADDR : out std_logic_vector(1 downto 0);    -- Address
    OTG_CS_N,                                       -- Chip Select
    OTG_RD_N,                                       -- Write
    OTG_WR_N,                                       -- Read
    OTG_RST_N,                                      -- Reset
    OTG_FSPEED,                     -- USB Full Speed, 0 = Enable, Z = Disable
    OTG_LSPEED : out std_logic;     -- USB Low Speed, 0 = Enable, Z = Disable
    OTG_INT0,                                       -- Interrupt 0
    OTG_INT1,                                       -- Interrupt 1
    OTG_DREQ0,                                      -- DMA Request 0
    OTG_DREQ1 : in std_logic;                       -- DMA Request 1   
    OTG_DACK0_N,                                    -- DMA Acknowledge 0
    OTG_DACK1_N : out std_logic;                    -- DMA Acknowledge 1

    -- 16 X 2 LCD Module
    
    LCD_ON,                     -- Power ON/OFF
    LCD_BLON,                   -- Back Light ON/OFF
    LCD_RW,                     -- Read/Write Select, 0 = Write, 1 = Read
    LCD_EN,                     -- Enable
    LCD_RS : out std_logic;     -- Command/Data Select, 0 = Command, 1 = Data
    LCD_DATA : inout std_logic_vector(7 downto 0); -- Data bus 8 bits

    -- SD card interface
    
    SD_DAT : in std_logic;      -- SD Card Data      SD pin 7 "DAT 0/DataOut"
    SD_DAT3 : out std_logic;    -- SD Card Data 3    SD pin 1 "DAT 3/nCS"
    SD_CMD : out std_logic;     -- SD Card Command   SD pin 2 "CMD/DataIn"
    SD_CLK : out std_logic;     -- SD Card Clock     SD pin 5 "CLK"

    -- USB JTAG link
    
    TDI,                        -- CPLD -> FPGA (data in)
    TCK,                        -- CPLD -> FPGA (clk)
    TCS : in std_logic;         -- CPLD -> FPGA (CS)
    TDO : out std_logic;        -- FPGA -> CPLD (data out)

    -- I2C bus
    
    I2C_SDAT : inout std_logic; -- I2C Data
    I2C_SCLK : out std_logic;   -- I2C Clock

    -- PS/2 port

    PS2_DAT,                    -- Data
    PS2_CLK : in std_logic;     -- Clock

    -- VGA output
    
    VGA_CLK,                            -- Clock
    VGA_HS,                             -- H_SYNC
    VGA_VS,                             -- V_SYNC
    VGA_BLANK,                          -- BLANK
    VGA_SYNC : out std_logic;           -- SYNC
    VGA_R,                              -- Red[9:0]
    VGA_G,                              -- Green[9:0]
    VGA_B : out unsigned(9 downto 0);   -- Blue[9:0]

    --  Ethernet Interface
    
    ENET_DATA : inout unsigned(15 downto 0);    -- DATA bus 16 Bits
    ENET_CMD,           -- Command/Data Select, 0 = Command, 1 = Data
    ENET_CS_N,                                  -- Chip Select
    ENET_WR_N,                                  -- Write
    ENET_RD_N,                                  -- Read
    ENET_RST_N,                                 -- Reset
    ENET_CLK : out std_logic;                   -- Clock 25 MHz
    ENET_INT : in std_logic;                    -- Interrupt
    
    -- Audio CODEC
    
    AUD_ADCLRCK : inout std_logic;                      -- ADC LR Clock
    AUD_ADCDAT : in std_logic;                          -- ADC Data
    AUD_DACLRCK : inout std_logic;                      -- DAC LR Clock
    AUD_DACDAT : out std_logic;                         -- DAC Data
    AUD_BCLK : inout std_logic;                         -- Bit-Stream Clock
    AUD_XCK : out std_logic;                            -- Chip Clock
    
    -- Video Decoder
    
    TD_DATA : in std_logic_vector(7 downto 0);  -- Data bus 8 bits
    TD_HS,                                      -- H_SYNC
    TD_VS : in std_logic;                       -- V_SYNC
    TD_RESET : out std_logic;                   -- Reset
    
    -- General-purpose I/O
    
    GPIO_0,                                      -- GPIO Connection 0
    GPIO_1 : inout std_logic_vector(35 downto 0) -- GPIO Connection 1   
    );
  
end DE2_TOP;

architecture datapath of DE2_TOP is
	signal Databus, DOR, ROM_data, X, Y : std_logic_vector(7 downto 0);	--	yuchen0514
	signal Addrbus, ROM_address  : std_logic_vector(15 downto 0);
	signal W_R 		: std_logic;
	signal reset 	: std_logic; --JB0513
	signal Sclk 	: std_logic; --JB0513
	signal clk25 	: std_logic := '0'; --yuchen0514 
	
	signal LCycle 	: std_logic_vector(2 downto 0); -- afe2104 
	signal MCycle 	: std_logic_vector(2 downto 0); -- afe2104
begin
	
  --HEX1     	<= (others => '1');
  --HEX0     	<= (others => '1');          -- Rightmost
  LEDG(8)   <= '0';
  --LEDR     	<= (others => '0');
  LCD_ON   	<= '1';
  LCD_BLON 	<= '1';
  LCD_RW 		<= '1';
  LCD_EN 		<= '0';
  LCD_RS 		<= '0';

  SD_DAT3 <= '1';  
  SD_CMD 	<= '1';
  SD_CLK 	<= '1';

  UART_TXD 		<= '0';
  DRAM_ADDR 	<= (others => '0');
  DRAM_LDQM 	<= '0';
  DRAM_UDQM 	<= '0';
  DRAM_WE_N 	<= '1';
  DRAM_CAS_N 	<= '1';
  DRAM_RAS_N 	<= '1';
  DRAM_CS_N 	<= '1';
  DRAM_BA_0 	<= '0';
  DRAM_BA_1 	<= '0';
  DRAM_CLK 		<= '0';
  DRAM_CKE 		<= '0';
  FL_ADDR 		<= (others => '0');
  FL_WE_N 		<= '1';
  FL_RST_N 		<= '0';
  FL_OE_N 		<= '1';
  FL_CE_N 		<= '1';
  OTG_ADDR 		<= (others => '0');
  OTG_CS_N 		<= '1';
  OTG_RD_N 		<= '1';
  OTG_RD_N 		<= '1';
  OTG_WR_N 		<= '1';
  OTG_RST_N 	<= '1';
  OTG_FSPEED 	<= '1';
  OTG_LSPEED 	<= '1';
  OTG_DACK0_N <= '1';
  OTG_DACK1_N <= '1';

  TDO 				<= '0';

  I2C_SCLK 		<= '0';
  IRDA_TXD 		<= '0';

  ENET_CMD 		<= '0';
  ENET_CS_N 	<= '1';
  ENET_WR_N 	<= '1';
  ENET_RD_N 	<= '1';
  ENET_RST_N 	<= '1';
  ENET_CLK 		<= '0';

  AUD_DACDAT 	<= '0';
  AUD_XCK 		<= '0';

  TD_RESET 		<= '0';

  -- Set all bidirectional ports to tri-state
  DRAM_DQ     <= (others => 'Z');
  FL_DQ       <= (others => 'Z');
  OTG_DATA    <= (others => 'Z');
  LCD_DATA    <= (others => 'Z');
  I2C_SDAT    <= 'Z';
  ENET_DATA   <= (others => 'Z');
  AUD_ADCLRCK <= 'Z';
  AUD_DACLRCK <= 'Z';
  AUD_BCLK    <= 'Z';
  GPIO_0      <= (others => 'Z');
  GPIO_1      <= (others => 'Z');
						
	-- 32 bits total
	-- CYCLE COMPLETE FOR ALL 154 INSTRUCTIONS
	CPUConnect: mos_6502 port map(
		clk 	=> Sclk,
		reset => not reset,
		ready => '1',
		
		A			=> Addrbus,
		DI 		=> Databus, 
		DO 		=> DOR,
		
		IRQ_n => '0',
		NMI_n	=> '0',
		SO_n  => '0',
		R_W_n	=> W_R,
		L_Cycle_out => LCycle,
		M_Cycle_out => MCycle
	);
	
	--JB0513: port map below changed to fit in debounce
	debouncecode: debounce port map(
		clk				=> CLOCK_50, 
		resetsw		=> SW(17), 
		resetout	=> reset
	); --JB0513
	
	slowclkcode: slowclk port map(
		clkin		=>	CLOCK_50, 
		clkout	=>	Sclk
	); --JB0513
											
	InstructionROM: Rom port map(
		addr	=>	ROM_address, 
		data	=>	ROM_data
	);

	MemorySRAM: SRAMCtrl port map(
		reset				=> reset, 
		clk					=> Sclk,
		W_R					=> W_R, 
		ROM_data		=> ROM_data, 
		DOR					=> DOR,
		databus			=> databus, 
		AddressBus	=> Addrbus, 
		ROM_address	=> ROM_address, 
		SRAM_DQ			=> SRAM_DQ,    
		SRAM_ADDR		=> SRAM_ADDR,  
		SRAM_UB_N		=> SRAM_UB_N,
		SRAM_LB_N		=> SRAM_LB_N,            
		SRAM_WE_N		=> SRAM_WE_N,          
		SRAM_CE_N		=> SRAM_CE_N,    
		SRAM_OE_N		=> SRAM_OE_N
	);

	VGAClock: 
	process (CLOCK_50)
		begin
			if rising_edge(CLOCK_50) then
				clk25 <= not clk25;
			end if;
	end process;
										
	VGA:  de2_vga_raster port map (
		reset 			=> reset, 
		clk 				=> clk25,
		VGA_CLK 		=> VGA_CLK,
		VGA_HS 			=> VGA_HS,
		VGA_VS 			=> VGA_VS,
		VGA_BLANK 	=> VGA_BLANK,
		VGA_SYNC 		=> VGA_SYNC,
		VGA_R 			=> VGA_R,
		VGA_G 			=> VGA_G,
		VGA_B 			=> VGA_B,
		center(15 downto 8) 	=> X,
		center(7 downto 0)		=> Y
  );
	
	-- DEBUG
	LEDR(16) <= W_R;
	LEDR(0) <= sw(0);
	
	
	-- ADDR LEDS
	U_HEX0: hex7seg port map(
		input		=> Addrbus(15 downto 12),
		output	=> hex0
	);
	
		U_HEX1: hex7seg port map(
		input		=> Addrbus(11 downto 8),
		output	=> hex1
	);
	
	U_HEX2: hex7seg port map(
		input		=> Addrbus(7 downto 4),
		output	=> hex2
	);
	
	U_HEX3: hex7seg port map(
		input		=> Addrbus(3 downto 0),
		output	=> hex3
	);
	
	-- DATA LEDS
	U_HEX4: hex7seg port map(
		input		=> Databus(3 downto 0),
		output	=> hex4
	);
	
	U_HEX5: hex7seg port map(
		input		=> Databus(7 downto 4),
		output	=> hex5
	);
	
	U_HEX6: hex7seg port map(
		input		=> '0' & LCycle,
		output	=> hex6
	);
	
	U_HEX7: hex7seg port map(
		input		=> '0' & MCycle,
		output	=> hex7
	);
	
end datapath;
