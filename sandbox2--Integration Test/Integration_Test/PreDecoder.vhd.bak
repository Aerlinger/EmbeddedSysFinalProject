library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity predecode is
port(
		Din  : in std_logic_vector(7 downto 0);
		Dout : out std_logic_vector(7 downto 0);
		Cycle_number : out std_logic_vector(3 downto 0));
end predecode;

architecture rtl of predecode is
begin
	process (Din)
	begin
	Dout<=Din;
	if Din=x"A9" then
	Cycle_number<=x"2";
	elsif Din=x"A5" then
	Cycle_number<=x"3";
	else 
	Cycle_number<=x"1";
	end if;
	end process;
end rtl;
