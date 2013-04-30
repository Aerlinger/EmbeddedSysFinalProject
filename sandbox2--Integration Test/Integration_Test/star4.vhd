library IEEE;
use IEEE.std_logic_1164.all;

entity star4 is

	port(
		SB_ADH, S_SB, ADD_SB, X_SB, Y_SB, AC_SB, SB_DB, DL_DB, PCL_DB, PCH_DB, AC_DB : in std_logic;
		y	: out	std_logic
	);

end star4;


architecture rtl of star4 is
begin
	y<=SB_ADH and (S_SB or ADD_SB or X_SB or Y_SB or AC_SB or (SB_DB and (DL_DB or PCL_DB or PCH_DB or AC_DB)));
end rtl;