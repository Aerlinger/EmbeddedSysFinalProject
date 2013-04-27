library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Two_Phase_CLK_tb is
end Two_Phase_CLK_tb;

architecture tb of Two_Phase_CLK_tb is
	signal clk    : std_logic  := '0';
	
begin
				
		process
		begin
			loop
			   clk <= '0'; wait for 20 ns;
			   clk <= '1'; wait for 20 ns;
			end loop;
		end process;

TowPhaseCLK: 
		entity work.Two_Phase_CLK
		port map (clk=>clk);
										
end tb;
