------------------------------------------------------------------------------
------------------------------------------------------------------------------
--
--  COMS W480 Final Project
--    Sprint 2013
--    A 6502 CPU reconstructed in VHDL and synthesized on the Altera DE2
--
--
-- Team Double O Four is:
--     Yu Chen
--     Jaebin Choi
--     Anthony Erlinger
--     Arthy Padma Anandhi Sundaram
--
------------------------------------------------------------------------------
------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std;
use ieee.std_logic_arith.all;

---------------------------------------------------

entity ALU is

  port(
    AI:  in std_logic_vector(7 downto 0);
    BI:  in std_logic_vector(7 downto 0);
    ADD:  out std_logic_vector(7 downto 0);
    P: in std_logic_vector(7 downto 0);
    opcode: in std_logic_vector(7 downto 0);

    ANDS: in std_logic;
    SUMS: in std_logic;
    ORS: in std_logic;
    EORS: in std_logic;
    SRS: in std_logic;

    I_ADDC: in std_logic;
    Mask_shortcut: in std_logic;
    AVR: out std_logic;
    ACR: out std_logic

    -- DECIMAL MODE NOT YET IMPLEMENTED:
  );

end ALU;

---------------------------------------------------

architecture rtl of ALU is
  signal temp : unsigned(8 downto 0);
begin

    process(AI, BI, ANDS, SUMS, ORS, EORS, SRS, I_ADDC)
    begin

      if (SUMS='1') then
        temp <= x"00"; --('0'&AI) + ('0'&BI) + ("0"&I_ADDC); -- stubbed for now...
        ADD <= std_logic_vector(temp(7 downto 0));
        ACR <= std_logic(temp(8) or Mask_shortcut);
      elsif (ANDS='1') then
        ADD <= AI and BI;
      elsif (ORS='1') then 
        ADD <= AI or BI;
      elsif (EORS='1') then
        ADD <= AI xor BI;

      -- TOOD: Verify this is how shifting works in the 6502
      elsif (SRS='1') then
--        ADD(6 downto 0) <= BI(7 downto 1);
--        ACR <= BI(0);
--        if opcode(7 downto 5)="010" then
--          ADD(7) <= '0';
--        elsif opcode(7 downto 5)="011" then
--          ADD(7) <= P(0);
--        end if;
      else
        ADD <= "XXXXXXXX";
      end if;

    end process;
  -- use case statement to achieve different operations of ALU

end rtl;

----------------------------------------------------
