library IEEE;
use IEEE.std_logic_1164.all;


entity mux4 is 

	port(
		sel : in std_logic_vector(3 downto 0);
		
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		c 	: in	std_logic_vector(7 downto 0);
		d 	: in	std_logic_vector(7 downto 0);
		
		y	: out	std_logic_vector(7 downto 0)
	);

end mux4;


architecture rtl of mux4 is
begin
	process(a,b,c,d,sel)
	begin
	case sel is 
		when "0001" => 	y <= a;
		when "0010" => 	y <= b;
		when "0100" => 	y <= c;
		when others => 	y <= d;
	end case;
	end process;
end rtl;
