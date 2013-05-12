library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

-- define constant, signal and procedure within package for ALU
package ALU_package is
  constant INTERVAL: TIME := 8 ns;

  signal sig_A: std_logic_vector(7 downto 0);
  signal sig_B: std_logic_vector(7 downto 0);
  signal sig_ANDS: std_logic;
  signal sig_SUMS: std_logic;
  signal sig_ORS: std_logic;
  signal sig_EORS: std_logic;
  signal sig_SRS: std_logic;
  signal sig_ADD: std_logic_vector(7 downto 0);

  procedure load_data(
    signal A, B: out std_logic_vector(7 downto 0);

    signal ANDS: out std_logic;
    signal SUMS: out std_logic;
    signal ORS:  out std_logic;
    signal EORS: out std_logic;
    signal SRS:  out std_logic
  );

  procedure check_data(
    signal ANDS: out std_logic;
    signal SUMS: out std_logic;
    signal ORS:  out std_logic;
    signal EORS: out std_logic;
    signal SRS:  out std_logic
  );

end ALU_package;

-- put all the procedure descriptions within package body
package body ALU_package is
  
  procedure load_data ( 
    signal A, B: out std_logic_vector(7 downto 0);
    signal ANDS: out std_logic;
    signal SUMS: out std_logic;
    signal ORS:  out std_logic;
    signal EORS: out std_logic;
    signal SRS:  out std_logic
  ) is
  begin
    A <= sig_A;
    B <= sig_B;
    ANDS <= sig_ANDS;
    SUMS <= sig_SUMS;
    ORS  <= sig_ORS;
    EORS <= sig_EORS;
    SRS  <= sig_SRS;
  end load_data;
  
  procedure check_data (
    signal ANDS: out std_logic;
    signal SUMS: out std_logic;
    signal ORS:  out std_logic;
    signal EORS: out std_logic;
    signal SRS:  out std_logic
  ) is
  begin

    ANDS <= sig_ANDS;
    SUMS <= sig_SUMS;
    ORS  <= sig_ORS;
    EORS <= sig_EORS;
    SRS  <= sig_SRS;

    if (sig_ANDS='1') then
      assert(sig_ADD = (sig_B and sig_A))
      report "Error in A and B"
      severity error;
    elsif (sig_SUMS='1') then
      assert(sig_ADD = (sig_A + sig_B))
      report "Error in Addition!"
      severity warning;
    elsif (sig_ORS='1') then
      assert(sig_ADD = (sig_A or sig_B))
      report "Error detected in or operation!"  
      severity warning;
    elsif (sig_EORS='1') then
      assert(sig_ADD = (sig_A xor sig_B))
      report "Error detected in XOR!"
      severity warning;
    elsif (sig_SRS='1') then  
      -- TODO: srl operator not working
      assert(sig_ADD = (sig_A))
      report "Error in SRL!"
      severity warning;
    else
      assert(sig_ADD = "XXXXXXXX") 
      report "Output of ALU is not XXXXXXXX when no mode is selected!"
      severity warning;
    end if;
  end check_data;

end ALU_package;


--------------------------------------------------------------------------
-- Test Bench code for ALU
--------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164. all; 
use work.ALU_package.all;

entity ALU_TB is      -- entity declaration
end ALU_TB;

architecture TB of ALU_TB is

  component ALU
    port(
      A:  in std_logic_vector(7 downto 0);
      B:  in std_logic_vector(7 downto 0);
      ANDS: in std_logic;
      SUMS: in std_logic;
      ORS:  in std_logic;
      EORS: in std_logic;
      SRS:  in std_logic;
      ADD:  out std_logic_vector(7 downto 0)
    );
  end component;

  signal A: std_logic_vector(7 downto 0) := "00000000";
  signal B: std_logic_vector(7 downto 0) := "00000000";
  signal ADD: std_logic_vector(7 downto 0) := "00000000";

  signal ANDS: std_logic;
  signal SUMS: std_logic;
  signal ORS:  std_logic;
  signal EORS: std_logic;
  signal SRS:  std_logic;
begin

  U_ALU: ALU port map (
    A,
    B, 
    ANDS,
    SUMS,
    ORS,
    EORS,
    SRS,
    ADD
  );

  process
  begin

    sig_A <= "11001100";
    sig_B <= "10101010";
    sig_ADD <= "00000000";

    sig_ANDS <= '0';
    sig_SUMS <= '0';
    sig_ORS  <= '0';
    sig_EORS <= '0';
    sig_SRS  <= '0';


    -- case 1: AND
    ----------------------------------------------------------------
    sig_ANDS <= '1';
    wait for 1 ns;
    load_data(A, B, ANDS, SUMS, ORS, EORS, SRS);
    wait for 1 ns;
    sig_ADD <= ADD;
    wait for INTERVAL;
    check_data(ANDS, SUMS, ORS, EORS, SRS);
    sig_ANDS <= '0';


    -- case 2: Addition
    ----------------------------------------------------------------
    sig_SUMS <= '1';
    wait for 1 ns;
    load_data(A, B, ANDS, SUMS, ORS, EORS, SRS);
    wait for 1 ns;
    sig_ADD <= ADD;
    wait for INTERVAL;
    check_data(ANDS, SUMS, ORS, EORS, SRS);
    sig_SUMS <= '0';


    -- case 3: OR operation
    ----------------------------------------------------------------
    sig_ORS <= '1';
    wait for 1 ns;
    load_data(A, B, ANDS, SUMS, ORS, EORS, SRS);
    wait for 1 ns;
    sig_ADD <= ADD;
    wait for INTERVAL;
    check_data(ANDS, SUMS, ORS, EORS, SRS);
    sig_ORS <= '0';


    -- case 4: Addition
    ----------------------------------------------------------------
    sig_EORS <= '1';
    wait for 1 ns;
    load_data(A, B, ANDS, SUMS, ORS, EORS, SRS);
    wait for 1 ns;
    sig_ADD <= ADD;
    wait for INTERVAL;
    check_data(ANDS, SUMS, ORS, EORS, SRS);
    sig_EORS <= '0';


    -- case 5: Shift logical right
    ----------------------------------------------------------------
    sig_SRS <= '1';
    wait for 1 ns;
    load_data(A, B, ANDS, SUMS, ORS, EORS, SRS);
    wait for 1 ns;
    sig_ADD <= ADD;
    wait for INTERVAL;
    check_data(ANDS, SUMS, ORS, EORS, SRS);
    sig_SRS <= '0';

    wait;

  end process;

end TB;

-------------------------------------------------------------------------
configuration CFG_TB of ALU_TB is
  for TB
  end for;
end CFG_TB;
-------------------------------------------------------------------------
