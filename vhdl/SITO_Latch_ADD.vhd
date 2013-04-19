library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SITO_Latch_ADD is
port (
		Din  : in  std_logic_vector(7 downto 0);
		Dout : out std_logic_vector(7 downto 0);
		Dbus_A : out std_logic_vector(7 downto 0);
		Dbus_B : out std_logic_vector(7 downto 0);
		Load : in std_logic;
		Bus_Enable_A : in std_logic;
		Bus_Enable_B_06 : in std_logic;
		Bus_Enable_B_7  : in std_logic;
		clk  : in std_logic);
end SITO_Latch_ADD;

architecture rtl of SITO_Latch_ADD is
  signal data : std_logic_vector(7 downto 0) := x"00";
  signal q		: std_logic_vector(7 downto 0) := x"00";
begin
	process (clk, Din, Load, Bus_Enable_A, Bus_Enable_B_06, Bus_Enable_B_7, q)
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
		elsif ((Bus_Enable_B_06='1') and (Bus_Enable_B_7='1')) then
      Dbus_B<=q;
      Dbus_A<=(others => 'Z');
		elsif ((Bus_Enable_B_06='1') and (Bus_Enable_B_7='0')) then
      Dbus_B(6 downto 0)<=q(6 downto 0);
      Dbus_B(7)<='Z';
      Dbus_A<=(others => 'Z');
	  elsif ((Bus_Enable_B_06='0') and (Bus_Enable_B_7='1')) then	
      Dbus_B(6 downto 0)<=(others => 'Z');
      Dbus_B(7)<=q(7);
      Dbus_A<=(others => 'Z');	
		else 
      Dbus_A<=(others => 'Z');
      Dbus_B<=(others => 'Z');
		end if;
	end process;
	
	Dout<=q;
end rtl;
