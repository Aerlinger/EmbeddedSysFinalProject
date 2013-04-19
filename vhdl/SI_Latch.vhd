library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SI_Latch is
port (
		Din  : in  std_logic_vector(7 downto 0);
		Dout : out std_logic_vector(7 downto 0);
		Load : in  std_logic;
		clk  : in  std_logic);
end SI_Latch;

architecture rtl of SI_Latch is
signal data : std_logic_vector(7 downto 0) := x"00";
signal q		: std_logic_vector(7 downto 0) := x"00";

begin
	process (clk, Din, Load)
	begin
		if (Load='1') then
		data<=Din;
		else data<=q;
		end if;
		
		if rising_edge(clk) then
		q<=data;
		end if;
	end process;
	
	Dout<=q;

end rtl;