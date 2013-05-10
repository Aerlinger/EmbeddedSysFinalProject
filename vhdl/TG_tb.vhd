library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity TG_tb is
end TG_tb;

architecture tb of TG_tb is
	signal clk    : std_logic  := '0';
	signal cycle_number  : std_logic_vector(3 downto 0) := b"0011";
	signal reset  : std_logic  := '1';
	signal ACR    : std_logic  := '0';
	signal BRC    : std_logic  := '0';
 
 begin
    	

		process
		begin
			loop
			   clk <= '0'; wait for 20 ns;
			   clk <= '1'; wait for 20 ns;
			end loop;
		end process;
		
		process
		begin
			wait for 40 ns;
			reset <= '0';
			wait;
		end process;
		
		process
		begin
			wait for 300 ns;
			cycle_number<= "0010";
			wait for 100 ns;
			cycle_number<= "0100";
			wait for 200 ns;
			cycle_number<= "0101";
			wait for 200 ns;
			cycle_number<= "0110";
			wait for 300 ns;
			cycle_number<= "0111";
			wait for 300 ns;
			cycle_number<= "0000";
			wait;
		end process;

		
								  
TG: 
		entity work.TG
		port map (clk=> clk, cycle_number=>cycle_number, ACR=>ACR, BRC=>BRC, reset=>reset);
										
end tb;
