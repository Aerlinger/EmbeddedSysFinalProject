library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity time_gen_tb is
end time_gen_tb;

architecture tb of time_gen_tb is
	signal clk    : std_logic  := '0';
	signal Cycle_num : std_logic_vector(3 downto 0) := x"0";
	signal clk_mask : std_logic :='0';
 
 begin
    	
		process
		begin
			wait for 18ns; Cycle_num     <= x"2";
			wait for 100ns; Cycle_num    <= x"3";
			wait for 200ns; Cycle_num    <= x"4";
			wait for 200ns; Cycle_num    <= x"5";
			wait for 200ns; Cycle_num    <= x"6";
			wait;
		end process;
		
		
		process
		begin
			loop
			   clk <= '0'; wait for 20ns;
			   clk <= '1'; wait for 20ns;
			end loop;
		end process;
		
		
		process
		begin
			wait for 61ns;
			loop
			   clk_mask <= '1'; wait for 40ns;
			   clk_mask <= '0'; wait for 40ns;
			end loop;
		end process;
--		process
--		begin
--			loop
--			   c      <= '1'after 18ns;
--			   c      <= '1'; 
--			end loop;
--		end process;
		
								  
TimeGen: 
		entity work.Timing_Generator
		port map (clk=>clk,Cycle_num=> Cycle_num, clk_mask=>clk_mask);
										
end tb;
