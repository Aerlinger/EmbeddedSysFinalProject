----------------------------------------------------------------
-- Test Bench for 1-bit D flip-flop
----------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity dff_TB is    -- entity declaration
end dff_TB;

----------------------------------------------------------------

architecture TB of dff_TB is

    signal tb_data_in: std_logic;
    signal tb_clk: std_logic;
    signal tb_data_out: std_logic;

    component dff
      port( data_in:  in std_logic;
            clock:    in std_logic;
            data_out: out std_logic
      );
    end component;

begin

    U_DFF: dff port map (tb_data_in, tb_clk, tb_data_out);

    -- concurrent process to offer clock signal 
    process
      begin
        tb_clk <= '0';
      wait for 5 ns;
        tb_clk <= '1';
      wait for 5 ns;
    end process;
  
    process
      variable err_cnt: integer := 0; 
    begin
    
    -- case 1
    tb_data_in <= '1';
    wait for 13 ns;
    assert (tb_data_out='1') report "Data should be 1 after one clock cycle" severity error;
    if (tb_data_out/='1') then
        err_cnt := err_cnt + 1;
    end if;

    -- case 2
    tb_data_in <=  '0';
    wait for 28 ns;
    assert (tb_data_out='0') report "Output should fall back to 0 after two clock cycles" severity error;
    if (tb_data_out/='0') then
        err_cnt := err_cnt + 1;
    end if;

    -- case 3
    tb_data_in <= '1';           
    wait for 2 ns;
    assert (tb_data_out='0') report "Output should not change after less than a clock cycle" severity error;
    if (tb_data_out/='0') then
        err_cnt := err_cnt + 1;
    end if;
    
    -- case 4
    tb_data_in <= '0';
    wait for 10 ns;
    assert (tb_data_out='0') report "When 0 at input, output should fall back to zero after a clock cycle" severity error;
    if (tb_data_out/='0') then
        err_cnt := err_cnt + 1;
    end if;

    -- case 5
    tb_data_in <=  '1';    
    wait for 20 ns;   
    assert (tb_data_out='1') report "When 1 at the input, the output should rise back to 1" severity error;   
    if (tb_data_out/='0') then
        err_cnt := err_cnt + 1;
    end if;

    -- summary of all the tests
    if (err_cnt=0) then       
        assert false 
        report "Testbench of Adder completed successfully!" 
        severity note; 
    else 
        assert true 
        report "Something wrong, try again" 
        severity error; 
    end if; 

    wait;

  end process;

end TB;

-----------------------------------------------------------------
configuration CFG_TB of dff_TB is
  for TB
  end for;
end CFG_TB;
-----------------------------------------------------------------
