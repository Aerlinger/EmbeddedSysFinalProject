library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.components.all;

--the delay settings has been changed to enable efficient simulations.
--original settings for the board: 24 bits for 'count'
--new settings for simulation: 7 bits for 'count'

entity debounce is
	port (
		clk, resetsw : in std_logic;
		resetout  : out std_logic
		);
end debounce;

architecture imp of debounce is
signal count: unsigned(23 downto 0) := (others => '0');
signal rout_buf: std_logic := '0';
begin

	detect: process(clk)
	begin

	if rising_edge(clk) then

		--0 to 1 transition of resetsw
		if rout_buf='0' and resetsw='1' then
			count <= count + 1;
			if count(23)='1' then
				rout_buf <= '1';
				resetout <= '1';
				count <= (others => '0'); -- reset count.
			end if;
		end if;
		
		--1 to 0 transition of resetsw
		if rout_buf='1' and resetsw='0' then
			count <= count + 1;
			if count(23)='1' then
				rout_buf <= '0';
				resetout <= '0';
				count <= (others => '0'); -- reset count.
			end if;
		end if;
	
	end if;
		
	end process detect;

end imp;