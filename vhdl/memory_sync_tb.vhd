library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity memory_sync_tb is
end memory_sync_tb;

architecture TB of memory_sync_tb is
  component memory_sync is
    port(
      clk: in std_logic;
      enable: in std_logic;
      read: in std_logic;
      write: in std_logic;
      read_addr: in std_logic_vector(7 downto 0);
      write_addr: in std_logic_vector(7 downto 0);
      data_in: in std_logic_vector(7 downto 0);
      data_out: out std_logic_vector(7 downto 0)
    );
  end component;

  signal tb_clk : std_logic;
  signal tb_enable: std_logic;
  signal tb_read: std_logic;
  signal tb_write: std_logic;

  signal tb_read_addr: std_logic_vector(7 downto 0);
  signal tb_write_addr: std_logic_vector(7 downto 0);
  signal tb_data_in: std_logic_vector(7 downto 0);
  signal tb_data_out: std_logic_vector(7 downto 0);

begin

  U_MEMORY_SYNC: memory_sync port map
  (
    tb_clk,
    tb_enable,
    tb_read,
    tb_write,
    tb_read_addr,
    tb_write_Addr,
    tb_data_in,
    tb_data_out
  );

  clk_sig: process
  begin
    tb_clk <= '1';
    wait for 20 ns;
    tb_clk <= '0';
    wait for 20 ns;
  end process;

  process
    variable err_cnt: integer := 0;
  begin
    tb_enable <= '1';
    tb_read <= '0';
    tb_write <= '0';
    tb_write_addr <= (tb_write_addr'range => '0');
    tb_read_addr <= (tb_read_addr'range => '0');
    tb_data_in <= (tb_data_in'range => '0');

    wait for 20 ns;

    -- A test write:
    --for i in 0 to 3 loop
      --tb_write_addr <= tb_write_addr + '1';
      --tb_data_in <= tb_data_in + "10";
      tb_write <= '1';
      wait for 10 ns;
      assert(tb_data_out="ZZZZ")
      report "Couldn't write data" severity Error;
      if(tb_data_out /= "ZZZZ") then
        err_cnt := err_cnt  + 1;
      end if;
    --end loop;

    -- A test read:
    --for i in 0 to 2 loop
      --tb_read_addr <= tb_read_addr + '1';
      --tb_read <= '1';

      wait for 40 ns;

      --assert (conv_integer(tb_data_out) = 2 * conv_integer(tb_read_addr))
      --report "Something is wrong!:" severity Error;
      --if (conv_integer(tb_data_out) /= 2 * conv_integer(tb_read_addr)) then
      --  err_cnt := err_cnt + 1;
      --end if;
    --end loop;

    -- Generate test summary
    if(err_cnt=0) then
      assert false
      report "Testbench of ROM completed successfully!"
      severity note;
    else
      assert true
      report "something is wrong, try again"
      severity error;
    end if;

    wait;

  end process;

end TB;

--------------------------------------------------------------------------------------------
configuration CFG_TB of memory_sync_tb is
  for TB
  end for;
end CFG_TB;
