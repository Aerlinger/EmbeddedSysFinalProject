library IEEE;
use IEEE.std_logic_1164.all;

entity star1 is

	port(
		SB_DB, S_SB, ADD_SB, X_SB, Y_SB, AC_SB, SB_ADH, DL_ADH, O_ADH, PCH_ADH : in std_logic;
		y	: out	std_logic
	);

end star1;


architecture rtl of star1 is
begin
	y<=SB_DB and (S_SB or ADD_SB or X_SB or Y_SB or AC_SB or (SB_ADH and (DL_ADH or O_ADH or PCH_ADH)));
end rtl;