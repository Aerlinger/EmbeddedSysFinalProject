library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std;

entity PASS_Gate_SBtoDB is
  port(
		Din : in std_logic_vector(7 downto 0);
		Dout : out std_logic_vector(7 downto 0);
		SB_DB, S_SB, ADD_SB06, ADD_SB7, X_SB, Y_SB, AC_SB	: in std_logic;
  );
end PasS_Gate_SBtoDB; 

architecture rtl of PASS_Gate_SBtoDB is
begin
	process(Din, S_SB,ADD_SB06, ADD_SB7, X_SB, Y_SB, AC_SB)
	begin
    if SB_DB='1' and (S_SB='1' or (ADD_SB06='1' and ADD_SB7='1') or X_SB='1' or Y_SB='1' or AC_SB='1') then
      Dout<=Din;
    else 
      Dout<=(others=>'Z');
    end if;
	end process;
end rtl;

