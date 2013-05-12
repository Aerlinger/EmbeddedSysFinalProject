----------------------------------------------
-- RAM Module:
----------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Define pin structure:
entity raminfr is
	port (
		clock : in std_logic;
		we  : in std_logic;
		a   : in unsigned(3 downto 0);
		di  : in unsigned(7 downto 0);
		do  : out unsigned(7 downto 0)
	);
end raminfr;

-- Defines internal arcitecture:
architecture rtl of raminfr is
	type ram_type is array (0 to 15) of unsigned(7 downto 0);
	signal RAM : ram_type := (others => (others => '0'));
	signal read_a : unsigned(3 downto 0);
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
		key : in std_logic_vector(3 downto 0);
		data_in  : in unsigned(7 downto 0);
		we  : out std_logic;
		addr : out unsigned(3 downto 0);
		data_out  : out unsigned(7 downto 0)
	);
end ctrl;

architecture selector of ctrl is
	signal current_addr : unsigned (3 downto 0) := "0000";
	signal current_val : unsigned (7 downto 0) := (others => '0');
	
	signal value_changed : std_logic := '0';
	signal count : unsigned(23 downto 0) := "100110001001011010000000";
	signal is_debouncing : std_logic := '0';
begin

	process (clock)
	begin
		if rising_edge(clock) then
		
			if (key /= "1111") then
				is_debouncing <= '1';
				count <= "100110001001011010000000";
				if key(0) = '0' then		-- increment
					we <= '0';
				elsif key(1) = '0' then		-- decrement
					we <= '0';
				if key(2) = '0' then		-- increment
					we <= '1';
				elsif key(3) = '0' then		-- decrement
					we <= '1';
			end if;
			
			-- If we're debouncing, increment count by 1:
			if is_debouncing = '1' then
				count <= count - 1;
			end if;
			
			-- if count has to 0, 
			if count = "000000000000000000000000" then 
				is_debouncing <= '0';
				
				current_val <= data_in;
				-- Input from Keys
				if key(0) = '0' then		-- next address
					we <= '0';
					current_addr <= current_addr + 1;
				elsif key(1) = '0' then		-- previous address
					we <= '0';
					current_addr <= current_addr - 1;
				elsif key(2) = '0' then		-- increment
					we <= '1';
					current_val <= current_val + 1;
				elsif key(3) = '0' then		-- decrement
					we <= '1';
					current_val <= current_val - 1;
				else
					-- OUTPUTS
					addr <= current_addr;
					data_out <= current_val;
				end if;
			end if;
		end if;
	end process;

end selector;

----------------------------------------------
-- Switch Debouncer
----------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity debouncer is
	port (
		clock  : in std_logic;
		key 	 : in std_logic_vector(3 downto 0);		-- Asynchronous
		output : out std_logic_vector(3 downto 0)
	);
end debouncer;


-- 200ms at 50 MHz is 10 Million cycles.
--  10 Million in Binary is: 100110001001011010000000
architecture behavioral of debouncer is
	signal count : unsigned(23 downto 0) := "100110001001011010000000";
	signal is_debouncing : std_logic := '0';
begin

	process (clock)
		begin
		if rising_edge(clock) then
			-- If any button is pressed set bouncing flag to true, and start count at 0:
			if (key /= "1111") then
				is_debouncing <= '1';
				count <= "100110001001011010000000";
			end if;
			
			-- If we're debouncing, increment count by 1:
			if is_debouncing = '1' then
				count <= count - 1;
			end if;
			
			-- if count has increased to 16, 
			if count = "000000000000000000000000" then 
				is_debouncing <= '0';
				output <= key;
			end if;
		end if;
	end process;

end behavioral;


----------------------------------------------
-- Hex To 7 Segment Decoder
----------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity hex7seg is
	port (input: in unsigned(3 downto 0);	-- Input is a 4 bit number
			output: out std_logic_vector(6 downto 0));	-- 7 bit output to light each of 7 segments
end hex7seg;

architecture combinational of hex7seg is
begin
	with input select output <=
		"1000000" when x"0", 
		"1111001" when x"1",
		"0100100" when x"2", 
		"0110000" when x"3",
		"0011001" when x"4", 
		"0010010" when x"5",
		"0000010" when x"6", 
		"1111000" when x"7",
		"0000000" when x"8", 
		"0010000" when x"9",
		"0001000" when x"A", 
		"0000011" when x"B",
		"1000110" when x"C", 
		"0100001" when x"D",
		"0000110" when x"E", 
		"0001110" when x"F",
		"XXXXXXX" when others;

end combinational;


----------------------------------------------
-- Top-Level Lab1 Module:
----------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Define pin interface
entity lab1 is

	-- external connections
	port (
		clock: in std_logic;
		key: in std_logic_vector(3 downto 0);
		hex4, hex5, hex6 : out std_logic_vector(6 downto 0)
	);
	
	-- internal connections
	signal we : std_logic := '0';
	signal a : unsigned(3 downto 0) := "0000";
	signal di : unsigned(7 downto 0);
	signal do : unsigned(7 downto 0);
	
	signal debounce_out : std_logic_vector(3 downto 0);
	signal addr_delay : std_logic_vector(3 downto 0);
	signal data_delay1 : std_logic_vector(3 downto 0);
	signal data_delay2 : std_logic_vector(3 downto 0);

end lab1;

architecture datapath of lab1 is
begin
  
--	-- debouncer switch as input to control module:
--	debouncer1: entity work.debouncer port map (
--		clock => clock,
--		key => key,
--		output => debounce_out
--	);

	-- Input control module:
	-- An important note: the output from the control module is 
	--   the input to the RAM, and the output from RAM is the
	--   input to the control
  	control: entity work.ctrl port map (
		clock => clock,
		key 	=> key,
		data_in  	=> do,			-- Data in
		we 	=> we,
		addr 	=> a,
		data_out 	=> di				-- Data out
	);

	-- RAM module:
	ram: entity work.raminfr port map (
		clock => clock,
		we 	=> we,
		a 		=> a,
		di 	=> di,
		do 	=> do
	);
	
	-- The address 7Seg display
	h6: entity work.hex7seg port map (
		input => a,
		output => hex6
	);
	
	-- The do[0] 7Seg display
	h5: entity work.hex7seg port map (
		input => do(7 downto 4),  	-- do(0:3)
		output => hex5
	);
	
	-- The do[1] 7Seg display
	h4: entity work.hex7seg port map (
		input => do(3 downto 0),	-- do(4:7)
		output => hex4
	);

end datapath;
