------------------------------------------------------------------------------
------------------------------------------------------------------------------
--
--  COMS W480 Final Project
--    Sprint 2013
--    A 6502 CPU reconstructed in VHDL and synthesized on the Altera DE2
--
-- Team Double O Four is:
--     Yu Chen
--     Jaebin Choi
--     Anthony Erlinger
--     Arthy Padma Anandhi Sundaram
--
--
--  An interface testing the 6502 interactively on the 6502
--   Adapted from Lab1 assignment
--
--  Button 1: Clock
--  Button 2: Reset
--
--  Hex1-2: Opcode (leftmost)
--  Hex3-4: PC (leftmost)
--  Hex5-8: ADDR Bus (leftmost)
--
--  Switches 1-7: Opcode Input
------------------------------------------------------------------------------
------------------------------------------------------------------------------

----------------------------------------------
-- RAM Module:
----------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

-- Define pin structure:
entity raminfr is
	port (
		clk 			: in std_logic;
		r_w  			: in std_logic;		-- Write is active low
		addr   		: in unsigned(15 downto 0);	-- From Databus
		data  	: inout unsigned(7 downto 0)
	);
end raminfr;

-- Defines internal arcitecture:
architecture rtl of raminfr is
	type ram_type is array (0 to 65535) of unsigned(7 downto 0);
	signal RAM : ram_type := (others => (others => '0'));
	signal read_a : unsigned(15 downto 0);
begin

	process (clk)
	begin
		if rising_edge(clk) then
			if r_w = '0' then
				RAM(to_integer(addr)) <= data;
			end if;
			read_a <= addr;
		end if;
	end process;

	data <= RAM(to_integer(read_a));
end rtl;


----------------------------------------------
-- Memory Controller
----------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Define pin structure:
--entity ctrl is
--	port (
--		clk : in std_logic;
--		r_w  : out std_logic;
--		key : in std_logic_vector(3 downto 0);
--		addr : out unsigned(15 downto 0);
--		data_in  : in unsigned(7 downto 0);
--		data_out  : out unsigned(7 downto 0)
--	);
--end ctrl;
--
--architecture selector of ctrl is
--	signal current_addr : unsigned (15 downto 0) := x"0000";
--	signal current_val : unsigned (7 downto 0) := (others => '0');
--	
--	signal value_changed : std_logic := '0';
--	
--	-- 200ms at 50 MHz is 10 Million cycles.
--	--  10 Million in Binary is: 100110001001011010000000
--	signal count : unsigned(23 downto 0) := x"FFFFF";
--	signal is_debouncing : std_logic := '0';
--begin
--
--	process (clk)
--	begin
--		if rising_edge(clk) then
--		
--			-- If any key is pressed
--			if (key /= "1111") then
--				-- Wait for about 1.05 million cycles (~1/50th of a second)
--				is_debouncing <= '1';
--				count <= x"FFFFF";		
--				
--				-- Write enable is asyncronous
--				if key(0) = '0' then		-- increment
--					r_w <= '0';
--				elsif key(1) = '0' then		-- decrement
--					r_w <= '0';
--				elsif key(2) = '0' then		-- increment
--					r_w <= '1';
--				elsif key(3) = '0' then		-- decrement
--					r_w <= '1';
--				end if;
--			end if;
--			
--			-- If we're debouncing, increment count by 1:
--			if is_debouncing = '1' then
--				count <= count - 1;
--				
--				-- if count is less than 2
--				if count < "10" then 
--					is_debouncing <= '0';
--					count <= x"FFFFF";
--					
--					current_val <= data_in;
--					
--					-- Input from Keys
--					if key(0) = '0' then		-- next address
--						current_addr <= current_addr + 1;
--					elsif key(1) = '0' then		-- previous address
--						current_addr <= current_addr - 1;
--					elsif key(2) = '0' then		-- increment
--						current_val <= current_val + 1;
--					elsif key(3) = '0' then		-- decrement
--						current_val <= current_val - 1;
--					end if;
--					
--				end if;
--			end if;
--			
--		end if;
--	end process;
--	
--	-- Define our outputs:
--	addr <= current_addr;
--	data_out <= current_val;
--
--end selector;


----------------------------------------------
-- Top-Level Lab1 Module:
----------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Define interface for lab1
entity lab1 is

	-- external connections
	port (
		clk: in std_logic;
		key: in std_logic_vector(3 downto 0);
		sw : in std_logic_vector(17 downto 0);
		
		hex0, 
		hex1, 
		hex2, 
		hex3, 
		hex4, 
		hex5, 
		hex6, 
		hex7 : out std_logic_vector(6 downto 0);		-- 7 SEG are Active Low
		ledg : out std_logic_vector(8 downto 0);		-- LEDS are Active High (Go figure)
		ledr : out std_logic_vector(17 downto 0) 
	);
	
	-- internal variables
	signal r_w : std_logic := '1';	-- Read by default
	signal Addrbus : std_logic_vector(15 downto 0) := x"0000";
	signal Databus : std_logic_vector(7 downto 0) := x"00";
	signal clock_cycles : unsigned(7 downto 0) := x"00";
	--signal di : unsigned(7 downto 0);
	--signal do : unsigned(7 downto 0);

end lab1;

architecture rtl of lab1 is	
begin

  ----------------------------------------------
  -- 6502 Module (TODO: Not ready yet)
  ----------------------------------------------
	--  control: entity SixFiveO2 port map (
	--    Databus => do,
	--    Addrbus => a,
	--    clk => key(0),
	--    reset => key(1),
	--    rdy => '1'
	--	);

	ledg <= "101010101";
	
	process(sw)
	begin
		ledr <= sw;
	end process;

	-- Input control module
	-- An important note: the output from the control module is 
	--   the input to the RAM, and the output from RAM is the
	--   input to the control
--  control: entity work.ctrl port map (
--		clk     	=> clk,
--		key 	    => key,
--		data_in  	=> data_in,	-- Data in
--    r_w 	    => r_w,
--    std_logic_vector(addr) => Addrbus,
--		data_out	=> data_out	-- Data out
--	);

	-- RAM module:
	ram: entity work.raminfr port map (
		clk 	=> clk,
		r_w 	=> r_w,
		addr	=> unsigned(Addrbus),
		data 	=> unsigned(Databus)
	);
	
  ----------------------------------------------
  -- 7 Segment displays are used for debugging
  ----------------------------------------------

	-- The PC Address
	h7: entity work.hex7seg port map (
		input => Addrbus(3 downto 0),
		output => hex7
	);
	
	-- The PC Address display
	h6: entity work.hex7seg port map (
		input => Addrbus(7 downto 4),
		output => hex6
	);
	
	-- The PC Address 7Seg display
	h5: entity work.hex7seg port map (
		input => Addrbus(11 downto 8),
		output => hex5
	);
	
	-- The PC Address 7Seg display
	h4: entity work.hex7seg port map (
		input =>  Addrbus(15 downto 12),  	-- do(0:3)
		output => hex4
	);
	
	-- The ADDR_LOW 7Seg display
	h3: entity work.hex7seg port map (
		input => Databus(3 downto 0),	-- do(4:7)
		output => hex3
	);
	
	-- The ADDR_LOW 7Seg display
	h2: entity work.hex7seg port map (
		input => std_logic_vector(Databus(3 downto 0)),	-- do(4:7)
		output => hex2
	);
	
	-- The ADDR_HIGH 7Seg display
	h1: entity work.hex7seg port map (
		input => std_logic_vector(clock_cycles(3 downto 0)),	-- do(4:7)
		output => hex1
	);

	-- The ADDR_HIGH 7Seg display
	h0: entity work.hex7seg port map (
		input => std_logic_vector(clock_cycles(7 downto 4)),	-- do(4:7)
		output => hex0
	);

end rtl;
