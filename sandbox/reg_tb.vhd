library ieee;
use ieee.std_logic_1164.all;

entity reg_tb is
end entity;

architecture rtl of reg_tb is
  signal tb_data_in: std_logic(7 downto 0);
  signal tb_clk: std_logic(7 downto 0);
  signal tb_data_out: std_logic;

  component reg
    port(
      data_in: in std_logic(7 downto 0);
      data_out: in std_logic(7 downto 0);
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
