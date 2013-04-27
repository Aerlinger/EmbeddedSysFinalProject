library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ALU is
port(
		Din_A  : in std_logic_vector(7 downto 0);
		Din_B  : in std_logic_vector(7 downto 0);
		Dout   : out std_logic_vector(7 downto 0);
		Sum_En : in std_logic;
		I_ADDC : in std_logic; --carry in of ALU
		Carry_out : out std_logic
);
end ALU;

architecture rtl of ALU is
  signal data : unsigned(8 downto 0);
begin
		process(I_ADDC, Din_A, Din_B)
	   begin
			if I_ADDC='1' then
        data<=(('0'&unsigned(Din_A))+('0'&unsigned(Din_B))+1);
			else
        data<=(('0'&unsigned(Din_A))+('0'&unsigned(Din_B)));
			end if;
		end process;
		
		process(data, Sum_En)
		begin
			if (Sum_En='1')then
        Dout<=std_logic_vector(data(7 downto 0));
			end if;
		end process;
		
		Carry_out<=data(8);
end rtl;

