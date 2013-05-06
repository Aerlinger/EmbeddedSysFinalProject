library IEEE;
use IEEE.std_logic_1164.all;


entity mux7 is 

	port(
		sel : in std_logic_vector(6 downto 0);
		
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		c 	: in	std_logic_vector(7 downto 0);
		d 	: in	std_logic_vector(7 downto 0);
		e 	: in	std_logic_vector(7 downto 0);
		f 	: in	std_logic_vector(7 downto 0);
		g 	: in	std_logic_vector(7 downto 0);

		y	: out	std_logic_vector(7 downto 0)
	);

end mux7;


architecture rtl of mux7 is
begin
	process(a,b,c,d,e,f,g,sel)
	begin
	case sel is 
		when "0000001" => 	y <= a;
		when "0000010" => 	y <= b;
		when "0000100" => 	y <= c;
		when "0001000" => 	y <= d;
		when "0010000" => 	y <= e;
		when "0100000" => 	y <= f;
		when others => 	y <= g;
	end case;
	end process;
end rtl;