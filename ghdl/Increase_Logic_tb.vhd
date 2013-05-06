library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity inc_logic_tb is
end inc_logic_tb;

architecture tb of inc_logic_tb is
	signal clk    : std_logic  := '0';
	signal c      : std_logic  := '0';
   signal Data   : std_logic_vector(7 downto 0) := x"FF";

begin
		c      <= '1'after 18ns;		
		process
		begin
			loop
			   clk <= '0'; wait for 20ns;
			   clk <= '1'; wait for 20ns;
			end loop;
		end process;
		
--		process
--		begin
--			loop
--			   c      <= '1'after 18ns;
--			   c      <= '1'; 
--			end loop;
--		end process;
		
								  
IncreaseLogic: 
		entity work.Increase_Logic
		port map (Carry_in=> c,
						Din=> Data);
										
end tb;
