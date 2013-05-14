--------------------------------------------------------------------------
-- Test Bench code for ALU
--------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std;
use ieee.std_logic_arith.all;


entity ALU_TB is      -- entity declaration
end ALU_TB;

architecture TB of ALU_TB is

  constant INTERVAL: TIME := 8 ns;

  component ALU
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
  );
  end component;

  signal sig_AI: std_logic_vector(7 downto 0)   := "00000000";
  signal sig_BI: std_logic_vector(7 downto 0)   := "00000000";
  signal sig_ADD: std_logic_vector(7 downto 0)  := "00000000";
  signal sig_P: std_logic_vector(7 downto 0)    := "00000000";
  signal sig_opcode: std_logic_vector(7 downto 0)    := "00000000";

  signal sig_I_ADDC: std_logic := '0';
  signal sig_Mask_shortcut: std_logic := '0';
  signal sig_ACR: std_logic := '0';
  signal sig_AVR: std_logic := '0';

  signal sig_ANDS: std_logic := '0';
  signal sig_SUMS: std_logic := '0';
  signal sig_ORS:  std_logic := '0';
  signal sig_EORS: std_logic := '0';
  signal sig_SRS:  std_logic := '0';

begin

  U_ALU: ALU port map (
    sig_AI,
    sig_BI,
    sig_ADD,
    sig_P,
    sig_opcode,
    sig_ANDS,
    sig_SUMS,
    sig_ORS,
    sig_EORS,
    sig_SRS,
    sig_I_ADDC,
    sig_Mask_shortcut,
    sig_AVR,
    sig_ACR
  );

  process
  begin

    -- case 1: AND
    ----------------------------------------------------------------
    -- sig_ANDS <= '1';
    -- sig_AI   <= "11001100";
    -- sig_BI   <= "10101010";

    -- wait for INTERVAL;

    -- assert(sig_ADD="10001000")
    -- report "ERROR in AND"
    -- severity error;

    -- wait for INTERVAL;
    
    -- sig_ANDS <= '0';


    -- case 2: Basic Addition
    ----------------------------------------------------------------
    -- sig_SUMS <= '1';
    -- sig_AI   <= "11111111";
    -- sig_BI   <= "11111111";
    -- sig_I_ADDC  <= '1';

    -- wait for INTERVAL;

    -- assert(sig_ADD="11111111")
    -- report "ERROR in ADDITION"
    -- severity error;

    -- wait for INTERVAL;


    -- case 3: Addition With Carry Input
    ----------------------------------------------------------------
    -- sig_SUMS <= '1';
    -- sig_AI   <= "01001100";
    -- sig_BI   <= "00101010";

    -- wait for INTERVAL;

    -- assert(sig_ADD="01110110")
    -- report "ERROR in ADD w/carry"
    -- severity error;

    -- assert(sig_I_ADDC='1')
    -- report "ERROR in ADD w/carry"
    -- severity error;

    -- wait for INTERVAL;
    
    -- sig_SUMS <= '0';


    -- case 4: Addition that generates carry
    ----------------------------------------------------------------
    -- sig_SUMS <= '1';
    -- sig_AI   <= "11001100";
    -- sig_BI   <= "10101010";

    -- wait for INTERVAL;

    -- assert(sig_ADD="101110110")
    -- report "ERROR in AND"
    -- severity error;

    -- wait for INTERVAL;
    
    -- sig_SUMS <= '0';


    -- case 5: Addition generating Overflow
    ----------------------------------------------------------------
    -- sig_SUMS <= '1';
    -- sig_AI   <= "01001100";
    -- sig_BI   <= "00101010";

    -- wait for INTERVAL;

    -- assert(sig_ADD="01110110")
    -- report "ERROR in AND"
    -- severity error;

    -- wait for INTERVAL;
    
    -- sig_SUMS <= '0';

    wait;
  end process;

end TB;

-------------------------------------------------------------------------
configuration CFG_ALU_TB of ALU_TB is
  for TB
  end for;
end CFG_ALU_TB;
-------------------------------------------------------------------------
