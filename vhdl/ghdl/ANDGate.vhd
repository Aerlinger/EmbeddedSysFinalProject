library ieee;
use ieee.std_logic_1164.all;

entity ANDGate is
port(
	InA : in std_logic;
	InB : in std_logic;
	Output : out std_logic);
end ANDGate;

architecture rtl of ANDGate is
begin
	Output <= InA and InB;
end rtl;
