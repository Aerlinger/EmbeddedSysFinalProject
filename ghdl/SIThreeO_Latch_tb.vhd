library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SIThreeO_latch_tb is
end SIThreeO_latch_tb;

architecture tb of SIThreeO_latch_tb is
	signal clk    : std_logic  := '0';
	signal load   : std_logic  := '1';
	signal enable_A, enable_B, enable_C : std_logic  := '0';
	signal Data   : std_logic_vector(7 downto 0) := x"0a";

begin
		process
		begin
			loop
			   clk <= '0'; wait for 20ns;
			   clk <= '1'; wait for 20ns;
			end loop;
		end process;
		
		process
		begin
			wait for 21ns;
			loop
			   load <= '0'; wait for 40ns;
			   load <= '1'; wait for 40ns;
			end loop;
		end process;
		
		process
		begin
			loop
			   Enable_A <= '0'; wait for 100ns;
			   Enable_A <= '1'; wait for 80ns;
			end loop;
		end process;
			
		
--		process
--		  begin
--		    Data <= x"0a"; wait for 30ns;
--			 Data <= x"cd"; wait for 60ns;
--			 Data <= x"ab";
--		end process;
		
								  

SIThreeOlatch: 
		entity work.SIThreeO_Latch
		port map (Load=> load, Din=> Data, bus_enable_A=>enable_A, bus_enable_B=>enable_B, 
					 bus_enable_C=>enable_C, clk=> clk);											
end tb;
