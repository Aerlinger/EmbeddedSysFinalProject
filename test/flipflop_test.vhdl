--------------------------------------------------------------
-- Test Bench for a generic one bit flip flop
-- @author Anthony Erlinger 6502 Project
--------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

-- Test Entity
entity d_flip_flop_test is
end d_flip_flop_test;

architecture test_bench of d_flip_flop_test is 

  signal T_data_in: std_logic;
  signal T_data_out: std_logic;
  signal T_clock: std_logic;

  component dff
    port(
      data_in : in std_logic;
      data_out : out std_logic; 
  );
  end component;

begin

  process 
  begin
    T_clock <= '0';
    wait for 5 ns;

    T_clock <= '1';
    wait for 5 ns;
  end 

  process
    variable num_errors: integer := 0;

  begin

    -- When Input is high the output should also be high.
    T_data_in <= '1';
    wait for 12 ns;

    assert (T_data_out='1') report "Error data out is not high when input is 1!" severity error;
    
    if (T_data_out/='1') then
      num_errors := num_errors + 1;
    end if;

  -- case 2
    T_data_in <= '0';
    wait for 28 ns;
    assert (T_data_out='0') report "Error data is not low when input is 0!" severity error;

    if (



end test_bench;
