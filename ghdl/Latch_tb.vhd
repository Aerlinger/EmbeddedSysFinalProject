library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity latch_tb is
end latch_tb;

architecture tb of latch_tb is
	signal clk    : std_logic  := '0';
	signal load   : std_logic  := '0';
	signal enable : std_logic  := '0';
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
			loop
			   load <= '0'; wait for 19ns;
			   load <= '1'; wait for 20ns;
			end loop;
		end process;
		
		process
		begin
			loop
			   Enable <= '0'; wait for 18ns;
			   Enable <= '1'; wait for 20ns;
			end loop;
		end process;
			
		
		process
		  begin
		    Data <= x"0a"; wait for 30ns;
			 Data <= x"cd"; wait for 60ns;
			 Data <= x"ab";
		end process;
		
								  
SIlatch: 
		entity work.SI_Latch
		port map (Load=> load,
						Din=> Data,
						clk=> clk);
SISOlatch: 
		entity work.SISO_Latch
		port map (Load=> load,
						Din=> Data,
						Bus_Enable=>Enable,
						clk=> clk);											
end tb;
