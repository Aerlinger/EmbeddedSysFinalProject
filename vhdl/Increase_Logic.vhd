library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Increase_Logic is
port(
		Din  :in  std_logic_vector(7 downto 0);
		Dout :out std_logic_vector(7 downto 0);
		Carry_in :in std_logic;
		Carry_out : out std_logic);
end Increase_Logic;

architecture rtl of Increase_Logic is
signal sum : unsigned(8 downto 0);
begin
		process(Carry_in, Din)
	   begin
			if Carry_in='1' then
			sum<=('0'&unsigned(Din)+1);
			else
			sum<=('0'&unsigned(Din));
			end if;
			end process;
		
		Dout<=std_logic_vector(sum(7 downto 0));
		Carry_out<=sum(8);

end rtl;

