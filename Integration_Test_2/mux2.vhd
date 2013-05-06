library IEEE;
use IEEE.std_logic_1164.all;


entity mux2 is

	port(
		sel : in std_logic_vector(1 downto 0);
		
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		
		y	: out	std_logic_vector(7 downto 0)
	);

end mux2;


architecture rtl of mux2 is
begin
	process(a,b,sel)
	begin
	case sel is 
		when "01" => 	y <= a;
		when others => 	y <= b;
	end case;
	end process;
end rtl;
