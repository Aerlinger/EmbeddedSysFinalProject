library IEEE;
use IEEE.std_logic_1164.all;


entity mux8 is 

	port(
		sel : in std_logic_vector(7 downto 0);
		
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		c 	: in	std_logic_vector(7 downto 0);
		d 	: in	std_logic_vector(7 downto 0);
		e 	: in	std_logic_vector(7 downto 0);
		f 	: in	std_logic_vector(7 downto 0);
		g 	: in	std_logic_vector(7 downto 0);
		h 	: in	std_logic_vector(7 downto 0);
		
		y	: out	std_logic_vector(7 downto 0)
	);

end mux8;


architecture rtl of mux8 is
begin
	process(a,b,c,d,e,f,g,h,sel)
	begin
	case sel is 
		when "00000001" => 	y <= a;
		when "00000010" => 	y <= b;
		when "00000100" => 	y <= c;
		when "00001000" => 	y <= d;
		when "00010000" => 	y <= e;
		when "00100000" => 	y <= f;
		when "01000000" => 	y <= g;
		when "10000000" => 	y <= h;
	end case;
	end process;
end rtl;