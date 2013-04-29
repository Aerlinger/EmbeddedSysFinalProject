library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Int_Test is
port(
		Databus :in std_logic_vector(7 downto 0);
		Addrbus :out std_logic_vector(15 downto 0);
      clock   :in std_logic);
end Int_Test;

architecture imp of Int_Test is

component dff
port ( data_in: in std_logic;
		 clock: in std_logic;
		 data_out: out std_logic
		);
end component;

begin
	Addrbus<=(others => '0');
end imp;