library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- The adder test bench
-- A testbench has no ports
------------------------------------------------------------------------------------------
entity adder_tb is
end adder_tb;

-- Architecture of test bench
------------------------------------------------------------------------------------------
architecture behav of adder_tb is
  -- Declare the component that will be instantiated. (adder in this case)
  component adder
    port (i0, i1 : in std_logic; ci : in std_logic; s : out std_logic; co : out std_logic);
  end component;

  -- Which entity is bound with which component?
  for adder_0: adder use entity work.adder;

  -- Stores the state of each "signal"
  signal i0, i1, ci, s, co : std_logic;
begin
  -- Component instantiation
  adder_0: adder port map(i0 => i0, i1 => i1, ci => ci, s => s, co => co);

  -- This is where the action happens:
  process
    type pattern_type is record
      -- The inputs of the adder.
      i0, i1, ci : std_logic;
      -- The expected outputs of the adder.
      s, co : std_logic;
    end record;

    -- The patterns to apply.
    type pattern_array is array (natural range <>) of pattern_type;
    constant patterns : pattern_array :=
      -- a, b, ci, s, c0
     (('0', '0', '0', '0', '0'),
      ('0', '0', '1', '1', '0'),
      ('0', '1', '0', '1', '0'),
      ('0', '1', '1', '0', '1'),
      ('1', '0', '0', '1', '0'),
      ('1', '0', '1', '0', '1'),
      ('1', '1', '0', '0', '1'),
      ('1', '1', '1', '1', '1'));
   begin
    -- Check each pattern:
    for i in patterns'range loop
      -- Set the inputs.
      i0 <= patterns(i).i0;
      i1 <= patterns(i).i1;
      ci <= patterns(i).ci;

      -- Wait for the results
      wait for 1 ns;

      -- Check the outputs
      assert s = patterns(i).s
        report "bad sum value" severity error;
      assert co = patterns(i).co
        report "bad carry out value" severity error;
   end loop;

   assert false report "end of test" severity note;
   -- wait forever to let the simulation finish.
   wait;
  end process;
end behav;
