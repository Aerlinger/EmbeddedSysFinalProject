library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity DFlipFlop is
port(
	data_in  : in std_logic_vector(7 downto 0);
	enable : in  std_logic;
	clk    : in std_logic;
	reset  : in std_logic;
	data_out : out std_logic_vector(7 downto 0));
end DFlipFlop;

architecture rtl of DFlipFlop is
	signal data : std_logic_vector(7 downto 0);
begin
	
	data_out <= data;
	
	process (clk, reset)
		begin
		if reset = '1' then 
			data <= x"00";
		elsif rising_edge(clk) then
			if enable = '1' then
				data <= data_in;	
			end if;
		end if;
	end process;
end rtl;