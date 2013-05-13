--RAM Design

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Memory is
	port (
	clk, reset : in std_logic;
	we : in std_logic;
	address : in std_logic_vector(15 downto 0);
	di : in std_logic_vector(7 downto 0);
	do : out std_logic_vector(7 downto 0)
   );
end Memory;

architecture rtl of Memory is
	type ram_type is array (0 to 4096) of std_logic_vector(7 downto 0);  --4K byte of memeory
	signal RAM : ram_type :=(others => (others => '0'));
--	signal read_a : std_logic_vector(15 downto 0);

begin
	
	process (clk,di,we,address, reset)
		begin
			if reset='1' then
			RAM(1)<=x"A9";
			RAM(2)<=x"11";
			RAM(3)<=x"09";
			RAM(4)<=x"22";
			RAM(5)<=x"29";
			RAM(6)<=x"77";
			RAM(7)<=x"49";
			RAM(8)<=x"77";
			RAM(9)<=x"69";
			RAM(10)<=x"22";
			RAM(11)<=x"8D";
			RAM(12)<=x"34";
			RAM(13)<=x"02";
			RAM(564)<=x"05";  --address=1234
			RAM(14)<=x"C9";
			RAM(15)<=x"00";
			else
				if rising_edge(clk) and we = '0' then
					RAM(to_integer(unsigned(address))) <= di;
				end if;
			end if;
	end process;


	do <= RAM(to_integer(unsigned(address)));

end rtl;