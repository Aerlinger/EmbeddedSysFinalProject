library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SISO_Latch is
port (
		Din  : in  std_logic_vector(7 downto 0);
--		Dout : out std_logic_vector(7 downto 0);
		Dbus : out std_logic_vector(7 downto 0);
		Load : in std_logic;
		Bus_Enable : in std_logic;
		clk  : in std_logic);
end SISO_Latch;

architecture rtl of SISO_Latch is
signal data : std_logic_vector(7 downto 0) := x"00";
signal q		: std_logic_vector(7 downto 0) := x"00";

begin
	process (clk, Din, Load, Bus_Enable,q)
	begin
		if (Load='1') then
		data<=Din;
		else data<=q;
		end if;
		
		if rising_edge(clk) then
		q<=data;
		end if;
		
		if (Bus_Enable='1') then
		Dbus<=q;
		else Dbus<=(others => 'Z');
		end if;
	end process;
	
--	Dout<=q;

end rtl;