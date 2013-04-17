--------------------------------------------------------------
-- Test Bench for a generic one bit flip flop
-- @author Anthony Erlinger 6502 Project
--------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

-- Empty Test Entity
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

  -- A 50 MHz clock has a 20ns clock cycle (50% duty cycle)
  process 
  begin
    T_clock <= '0';
    wait for 10 ns;

    T_clock <= '1';
    wait for 10 ns;
  end 

  process

    variable num_errors: integer := 0;

  begin

    -- When Input is high for more than one clock cycle the output should also be high.
    T_data_in <= '1';
    wait for 25 ns;
    assert (T_data_out='1') report "Error data out is not high when input is 1 for more than one cycle!" severity error;
    if (T_data_out/='1') then
      num_errors := num_errors + 1;
    end if;

    -- When Input is low for more than one clock cycle the output should also be low.
    T_data_in <= '0';
    wait for 28 ns;
    assert (T_data_out='0') report "Error data is not low when input is 0 for more than one cycle!" severity error;
    if (T_data_out/='0') then
      num_errors := num_errors + 1;
    end if;

    -- Output should not change when Input is high for less than one clock cycle
    T_data_in <= '1';
    wait for 2 ns;
    assert (T_data_out='0') report "Error data is high even though high input was held for less than one clock cycle!" severity error;
    if (T_data_out/='0') then
      num_errors := num_errors + 1;
    end if;

    -- Then input is low for two more clock cycles
    T_data_in <= '0';
    wait for 20 ns;
    assert (T_data_out='0') report "Error data is not low when low input held for more than one clock cycle!" severity error;
    if (T_data_out/='0') then
        num_errors := num_errors + 1;
    end if;

    -- Set input high and Wait two more clock cycles
    T_data_in <= '1';
    wait for 40ns;
    assert (T_data_out='1') report "Output is not high after high input for two cycles");
    if (T_data_out/='1') then
      num_errors = num_errors + 1;
    end

end test_bench;
