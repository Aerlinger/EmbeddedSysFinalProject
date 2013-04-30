library IEEE;
use IEEE.std_logic_1164.all;

entity star3 is

	port(
		SB_ADH, DL_ADH, O_ADH, PCH_ADH : in std_logic;
		y	: out	std_logic
	);

end star3;


architecture rtl of star3 is
begin
	y<= SB_ADH and (DL_ADH or O_ADH or PCH_ADH);
end rtl;