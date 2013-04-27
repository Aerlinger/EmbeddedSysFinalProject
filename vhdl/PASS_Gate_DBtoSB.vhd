library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std;

entity PASS_Gate_DBtoSB is
  port(Din : in std_logic_vector (7 downto 0);
        Dout : out std_logic_vector (7 downto 0);
        SB_DB,DL_DB,PCL_DB,PCH_DB,AC_DB : in std_logic );
end PASS_Gate_DBtoSB; 

architecture rtl of PASS_Gate_DBtoSB is
begin
	process(Din, SB_DB, DL_DB, PCL_DB, AC_DB, PCH_DB)
	begin
    if SB_DB='1' and (DL_DB='1' or PCL_DB='1' or AC_DB='1' or PCH_DB='1') then
      Dout <= Din;
    else Dout<=(others=>'Z');
    end if;
	end process;
end rtl;

