library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity LDA_tb is
end LDA_tb;

architecture tb of LDA_tb is
	signal clk    : std_logic  := '0';
	signal Databus : std_logic_vector(7 downto 0) := x"A9";
 
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
			wait for 40ns;
			Databus<= x"10";
			wait for 70ns;
			Databus<= x"A5";
			wait for 90ns;
			Databus<= x"00";
			wait for 80ns;
			Databus<=x"01";
			wait;
		end process;

		
								  
LDA: 
		entity work.LDA
		port map (clk=> clk, Databus=>Databus);
										
end tb;
