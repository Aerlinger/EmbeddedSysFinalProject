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
    AI:   in std_logic_vector(7 downto 0);
    BI:   in std_logic_vector(7 downto 0);
    ADD:  out std_logic_vector(7 downto 0);
    P:    in std_logic_vector(7 downto 0);
    opcode: in std_logic_vector(7 downto 0);

    ANDS: in std_logic;
    SUMS: in std_logic;
    ORS:  in std_logic;
    EORS: in std_logic;
    SRS:  in std_logic;

    I_ADDC: in std_logic;

    Mask_shortcut: in std_logic;
    AVR: out std_logic;
    ACR: out std_logic

    -- DECIMAL MODE NOT YET IMPLEMENTED:
  );

  signal temp : unsigned(9 downto 0) := "1111111111";

end ALU;

-- ---------------------------------------------------


architecture rtl of ALU is
  
begin

  process(SUMS, ANDS, ORS, EORS, SRS)
  begin

    if (SUMS='1') then
      temp <= unsigned("00" & AI) + unsigned("00" & BI) + I_ADDC;

      ACR   <= std_logic(temp(8) or Mask_shortcut);
      AVR   <= std_logic(temp(9));

      -- Set the overflow flag if necessary:
      -- Overflow = C6 xor C7
      -- TODO: What about subtraction?
      -- AVR <= (AI(6) xor temp(6)) and (BI(6) xor temp(6));
      ADD  <= std_logic_vector(temp(7 downto 0));

       -- or P(6); -- TODO: Verify P(6) with is overflow flag on P reg.
    elsif (ANDS='1') then
      ADD   <= AI and BI;
      ACR   <= '0';
    elsif (ORS='1') then 
      ADD   <= AI or BI;
      ACR   <= '0';
    elsif (EORS='1') then
      ADD   <= AI xor BI;
      ACR   <= '0';
    -- TOOD: Shift Right: Verify this is how shifting works in the 6502
    elsif (SRS='1') then
      -- Shift right
      ADD(6 downto 0) <= BI(7 downto 1);

      -- Store rightmost in carry
      ACR <= BI(0);

      -- Rotate or no?
      if opcode(7 downto 5) = "010" then
        ADD(7) <= '0';
      elsif opcode(7 downto 5) = "011" then
        ADD(7) <= P(0);
      end if;
    else
      ADD <= x"FF";
    end if;

  end process;

end rtl;

----------------------------------------------------
