--RAM Design


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity raminfr is
port (
	clk	: in std_logic;
	we 	: in std_logic;
	a 	: in std_logic_vector(15 downto 0);
	di 	: in std_logic_vector(7 downto 0);
	do 	: out std_logic_vector(7 downto 0)
);
end raminfr;

architecture rtl of raminfr is
	type ram_type is array (0 to 32767) of unsigned(7 downto 0);
	signal RAM : ram_type :=(others => (others => '0'));
	signal read_a : unsigned(15 downto 0);
begin

	process (clk)
		begin
			if rising_edge(clk) then
				if we = '1' then 
					RAM(to_integer(unsigned(a))) <= unsigned(di);
				end if;
				read_a <= unsigned(a);
			end if;
	end process;

	do <= std_logic_vector(RAM(to_integer(read_a)));
end rtl;
