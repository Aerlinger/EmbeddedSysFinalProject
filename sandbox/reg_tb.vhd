library ieee;
use ieee.std_logic_1164.all;

entity reg_tb is
end entity;

architecture tb of reg_tb is
  signal tb_data_in: std_logic_vector(7 downto 0);
  signal tb_clk: std_logic;
  signal tb_data_out: std_logic_vector(7 downto 0);

  component reg
    port(
      data_in: in std_logic_vector(7 downto 0);
      data_out: out std_logic_vector(7 downto 0);
      clk: in std_logic
    );
  end component;

begin

  U_REG: reg port map(tb_data_in, tb_data_out, tb_clk);

  process
    begin 
      tb_clk <= '0';
    wait for 5 ns;
      tb_clk <= '1';
    wait for 5 ns;
  end process;

  process
    variable num_errors: integer := 0;
  begin

    tb_data_in <= "11111111";
    wait for 13 ns;

    assert (tb_data_out="11111111")
    report "Data should be 1111111 after one clock cycle" 
    severity error;

    if (tb_data_out/="11111111") then
      num_errors := num_errors + 1;
    end if;

    if (num_errors=0) then
      assert false
      report "Testbench of register completed successfully!"
      severity note;
    end if;

    wait;

  end process;

end tb;

configuration CFG_TB of reg_tb is
  for TB
  end for;
end CFG_TB;
