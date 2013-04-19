library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Open_Drain is
port(
		Dout : out std_logic_vector(7 downto 0);
		O_0  : in std_logic;
		O_17 : in std_logic);
end Open_Drain;

architecture rtl of Open_Drain is
begin
	process(O_0, O_17)
	begin
		if O_0='1' and O_17='1' then Dout<=x"00";
		else Dout<=(others=>'Z');
		end if;
	end process;
end rtl;
		