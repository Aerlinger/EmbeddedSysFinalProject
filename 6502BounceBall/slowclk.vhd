library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.components.all;

--the delay settings has been changed to enable efficient simulations.
--25 bits for ~1/3sec
--26 bits for slower

entity slowclk is
	port (
		clkin : in std_logic;
		clkout  : out std_logic
	);
end slowclk;

architecture imp of slowclk is
	signal cur: std_logic := '0';
	signal count: unsigned(12 downto 0) := (others => '0');
begin

	detect: process(clkin)
	begin

		if rising_edge(clkin) then
			count <= count + 1;
			if count(4)='1' then
				count <= (others => '0'); -- reset count.
				cur <= not(cur);
				clkout <= cur;
			end if;
		end if;
	end process detect;
end imp;