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
		clock : in std_logic;
		we  : in std_logic;
		a   : in unsigned(15 downto 0);
		di  : in unsigned(7 downto 0);
		do  : out unsigned(7 downto 0)
	);
end raminfr;

-- Defines internal arcitecture:
architecture rtl of raminfr is
	type ram_type is array (0 to 65535) of unsigned(7 downto 0);
	signal RAM : ram_type := (others => (others => '0'));
	signal read_a : unsigned(7 downto 0);
begin

	process (clock)
	begin
		if rising_edge(clock) then
			if we = '1' then
				RAM(to_integer(a)) <= di;
			end if;
			read_a <= a;
		end if;
	end process;

	do <= RAM(to_integer(read_a));

end rtl;


----------------------------------------------
-- Memory Controller
----------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Define pin structure:
entity ctrl is
	port (
		clock : in std_logic;
		we  : out std_logic;
		key : in std_logic_vector(7 downto 0);
		data_in  : in unsigned(7 downto 0);
		addr : out unsigned(7 downto 0);
		data_out  : out unsigned(7 downto 0)
	);
end ctrl;

architecture selector of ctrl is
	signal current_addr : unsigned (7 downto 0) := "0000";
	signal current_val : unsigned (7 downto 0) := (others => '0');
	
	signal value_changed : std_logic := '0';
	
-- 200ms at 50 MHz is 10 Million cycles.
--  10 Million in Binary is: 100110001001011010000000
	signal count : unsigned(23 downto 0) := "100110001001011010000000";
	signal is_debouncing : std_logic := '0';
begin

	process (clock)
	begin
		if rising_edge(clock) then
		
			if (key /= "1111") then
				is_debouncing <= '1';
				count <= "100110001001011010000000";		
				
				-- Write enable is asyncronous
				if key(0) = '0' then		-- increment
					we <= '0';
				elsif key(1) = '0' then		-- decrement
					we <= '0';
				elsif key(2) = '0' then		-- increment
					we <= '1';
				elsif key(3) = '0' then		-- decrement
					we <= '1';
				end if;
			end if;
			
			-- If we're debouncing, increment count by 1:
			if is_debouncing = '1' then
				count <= count - 1;
				
				-- if count has to 0, 
				if count < "000000000000000000000010" then 
					is_debouncing <= '0';
					count <= "100110001001011010000000";
					
					current_val <= data_in;
					
					-- Input from Keys
					if key(0) = '0' then		-- next address
						current_addr <= current_addr + 1;
					elsif key(1) = '0' then		-- previous address
						current_addr <= current_addr - 1;
					elsif key(2) = '0' then		-- increment
						current_val <= current_val + 1;
					elsif key(3) = '0' then		-- decrement
						current_val <= current_val - 1;
					end if;
					
				end if;
			end if;
			
		end if;
	end process;
	
	-- Define our outputs:
	addr <= current_addr;
	data_out <= current_val;

end selector;


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
		clock: in std_logic;
		key: in std_logic_vector(3 downto 0);
		hex0, hex1, hex2, hex3, hex4, hex5, hex6, hex7 : out std_logic_vector(6 downto 0)
	);
	
	-- internal variables
	signal we : std_logic := '0';
	signal Addrbus : std_logic_vector(15 downto 0) := x"0000";
	signal Databus : std_logic_vector(15 downto 0) := x"0000";
	signal clock_cycles : unsigned(7 downto 0) := x"00";
	signal di : unsigned(7 downto 0);
	signal do : unsigned(7 downto 0);

end lab1;

architecture rtl of lab1 is
--	component SixFiveO2
--	port (
--	    Databus : in std_logic_vector(7 downto 0);
--      Addrbus : out std_logic_vector(15 downto 0);
--      DOR     : out std_logic_vector(7 downto 0);
--      reset, clk: in std_logic;
--
--      XL, XH, YL, YH, ACCL, ACCH : out std_logic_vector(6 downto 0)
--	)
--	end component;
--	
--	signal databus : std_logic_vector(7 downto 0);
--	signal addrbus : std_logic_vector(7 downto 0);
--	signal databus : std_logic_vector(7 downto 0);
--	
begin

  ----------------------------------------------
  -- 6502 Module
  ----------------------------------------------
--  control: entity SixFiveO2 port map (
--    Databus => do,
--    Addrbus => a,
--    clk => key(0),
--    reset => key(1),
--    rdy => '1'
--	);

	-- Input control module
	-- An important note: the output from the control module is 
	--   the input to the RAM, and the output from RAM is the
	--   input to the control
  control: entity work.ctrl port map (
		clock     => clock,
		key 	    => key,
		data_in  	=> do,			-- Data in
    we 	      => we,
    std_logic_vector(addr) 	    => Addrbus,
		data_out	=> di				-- Data out
	);

	-- RAM module:
	ram: entity work.raminfr port map (
		clock => clock,
		we 	=> we,
		a		=> unsigned(Addrbus),
		di 	=> di,
		do 	=> do
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
		input => std_logic_vector(clock_cycles(3 downto 0)),	-- do(4:7)
		output => hex2
	);
	
	-- The ADDR_HIGH 7Seg display
	h1: entity work.hex7seg port map (
		input => std_logic_vector(clock_cycles(3 downto 0)),	-- do(4:7)
		output => hex1
	);

	-- The ADDR_HIGH 7Seg display
	h0: entity work.hex7seg port map (
		input => std_logic_vector(do(3 downto 0)),	-- do(4:7)
		output => hex0
	);

end rtl;
