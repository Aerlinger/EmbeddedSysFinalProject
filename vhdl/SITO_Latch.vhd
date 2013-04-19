library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SITO_Latch is
port (
		Din  : in  std_logic_vector(7 downto 0);
		Dout : out std_logic_vector(7 downto 0);
		Dbus_A : out std_logic_vector(7 downto 0) := x"00";
		Dbus_B : out std_logic_vector(7 downto 0) := x"00"; 
		Load : in std_logic;
		Bus_Enable_A : in std_logic;
		Bus_Enable_B : in std_logic;
		clk  : in std_logic);
end SITO_Latch;

architecture rtl of SITO_Latch is
signal data : std_logic_vector(7 downto 0) := x"00";
signal q		: std_logic_vector(7 downto 0) := x"00";

begin
	process (clk, Din, Load, Bus_Enable_A,Bus_Enable_B,q)
	begin
		if (Load='1') then
		data<=Din;
		else data<=q;
		end if;
		
		if rising_edge(clk) then
		q<=data;
		end if;
		
		if (Bus_Enable_A='1') then
		Dbus_A<=q; 
		Dbus_B<=(others => 'Z');
		elsif (Bus_Enable_B='1') then
		Dbus_B<=q; 
		Dbus_A<=(others => 'Z');
		else 
		Dbus_A<=(others => 'Z');
		Dbus_B<=(others => 'Z');
		end if;
	end process;
	
	Dout<=q;

end rtl;