library IEEE;
use IEEE.std_logic_1164.all;


entity mux3 is 

	port(
		sel : in std_logic_vector(2 downto 0);
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		c 	: in	std_logic_vector(7 downto 0);
		y	: out	std_logic_vector(7 downto 0)
	);

end mux3;


architecture rtl of mux3 is
begin
	process(a,b,c,sel)
	begin
	case sel is 
		when "001" => 	y <= a;
		when "010" => 	y <= b;
		when others => 	y <= c;
	end case;
	end process;
end rtl;
