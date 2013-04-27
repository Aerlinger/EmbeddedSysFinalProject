library ieee;
use ieee.std_logic_1164.all;

entity Inverter8b is
  port(
    Din  : in  std_logic_vector(7 downto 0);
    Dout : out std_logic_vector(7 downto 0)
  );
end Inverter8b;

architecture rtl of Inverter8b is
begin
	Dout <= not (Din);
end rtl;
