library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Two_Phase_CLK is
port(
		Clk  : in std_logic;
		Clk_mask : out std_logic );
end Two_Phase_CLK;

architecture rtl of Two_Phase_CLK is
signal counter : std_logic :='0';

begin
	process(clk)
	begin
	if rising_edge(clk) then
		if counter='1' then counter<='0';
		else counter<='1';
		end if;
	end if;
	end process;
	Clk_mask<=counter;
end rtl;