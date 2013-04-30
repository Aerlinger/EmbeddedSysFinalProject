library IEEE;
use IEEE.std_logic_1164.all;


entity mux5 is 

	port(
		sel : in std_logic_vector(4 downto 0);
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		c 	: in	std_logic_vector(7 downto 0);
		d 	: in	std_logic_vector(7 downto 0);
		e 	: in	std_logic_vector(7 downto 0);
		y	: out	std_logic_vector(7 downto 0)
	);

end mux5;


architecture rtl of mux5 is
begin
	process(a,b,c,d,e,sel)
	begin
	case sel is 
		when "00001" => 	y <= a;
		when "00010" => 	y <= b;
		when "00100" => 	y <= c;
		when "01000" => 	y <= d;
		when others => 	y <= e;
	end case;
	end process;
end rtl;