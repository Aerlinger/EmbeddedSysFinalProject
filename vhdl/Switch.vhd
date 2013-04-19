library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Switch is 
port(
		DA : inout std_logic_vector(7 downto 0);
		DB : inout std_logic_vector(7 downto 0);
		Enable : in std_logic);
end Switch;

architecture rtl of Switch is
begin
	process(Enable, DA, DB)
	begin
		if Enable='1' then DA<=DB; DB<=DA;
		else DA<=(others=>'Z'); DB<=(others=>'Z');
		end if;
	end Process;
end rtl;

	