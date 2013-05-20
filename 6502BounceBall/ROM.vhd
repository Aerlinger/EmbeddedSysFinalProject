library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

use work.roms.all;

entity rom is
	port(addr  : in std_logic_vector(15 downto 0);
			data : out std_logic_vector(7 downto 0));
	end rom;
architecture imp of rom is
	signal address : unsigned(7 downto 0);
begin
	address <= unsigned(addr(7 downto 0));
	data 		<= BOUNCING_BALL(TO_Integer(address));
end imp;