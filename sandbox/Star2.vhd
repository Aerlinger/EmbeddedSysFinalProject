library IEEE;
use IEEE.std_logic_1164.all;

entity star2 is

	port(
		SB_DB, DL_DB, PCL_DB, PCH_DB, AC_DB : in std_logic;
		y	: out	std_logic
	);

end star2;


architecture rtl of star2 is
begin
	y<= SB_DB and (DL_DB or PCL_DB or PCH_DB or AC_DB);
end rtl;