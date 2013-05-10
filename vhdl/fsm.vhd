-- A generic state machine for the timing state input to the Decode ROM.
library ieee;
use ieee.std_logic_1164.all;

entity seq_design is
  port( 
    a: in std_logic;
    clk: in std_logic;
    reset: in std_logic;
    x: out std_logic
  );
end seq_design;


architecture fsm of seq_design is

  -- define the FSM states
  -- The Decode ROM (PLA) only takes T0-T5 as inputs
  type timing_state is (T0, T1, T2, T2_T0, T3, T4, T5, T6);
  signal next_state, current_state: timing_state;

begin

-- concurrent process #1: state registers
  state_reg: process(clock, reset)
  begin

    if (reset='1') then
      current_state <= T0;
    end if;

    -- TODO: Unfinished: Anthony
  end process;
end fsm;
