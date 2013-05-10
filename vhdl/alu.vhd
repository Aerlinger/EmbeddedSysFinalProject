-- 6502 ALU implementation
--
-- Anthony Erlinger
--

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std;
use ieee.std_logic_arith.all;

---------------------------------------------------

entity ALU is

port(
  A:  in std_logic_vector(7 downto 0);
  B:  in std_logic_vector(7 downto 0);
  Res:  out std_logic_vector(7 downto 0);

  ANDS: in std_logic;
  SUMS: in std_logic;
  ORS: in std_logic;
  EORS: in std_logic;
  SRS: in std_logic

  --carry: out std_logic;
  --overflow: out std_logic

  -- DECIMAL MODE NOT YET IMPLEMENTED:
  -- decimal_enable: in std_logic;
);

end ALU;

---------------------------------------------------

architecture behv of ALU is
begin            

    process(A, B, ANDS, SUMS, ORS, EORS, SRS)
    begin
      
      if (SUMS='1') then
        Res <= A + B;
      elsif (ANDS='1') then
        Res <= A and B;
      elsif (ORS='1') then 
        Res <= A or B;
      elsif (EORS='1') then
        Res <= A xor B;
      -- TOOD: Verify this is how shifting works in the 6502
      elsif (SRS='1') then
        Res <= A srl 1;
      else
        Res <= "XXXXXXXX";
      end if;

    end process;
  -- use case statement to achieve different operations of ALU

end behv;

----------------------------------------------------
