library ieee;
use ieee.std_logic_1164.all;

entity Inverter1b is
  port(
    A  : in std_logic;
    A_bar : out std_logic
  );
end Inverter1b;

architecture rtl of Inverter1b is
begin	
	A_bar<=not A;
end rtl;
