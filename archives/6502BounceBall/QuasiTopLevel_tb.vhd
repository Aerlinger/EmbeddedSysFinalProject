library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity QuasiTopLevel_tb is
end QuasiTopLevel_tb;

architecture tb of QuasiTopLevel_tb is
	signal SW  : std_logic  := '1';
	signal CLOCK_50    : std_logic  := '0';
--signal databus : std_logic_vector(7 downto 0) :=x"A9";
	 
 begin
    	

		process
		begin
			loop
			   CLOCK_50 <= '0'; wait for 20ns;
			   CLOCK_50 <= '1'; wait for 20ns;
			end loop;
		end process;
		
		
		process
		begin
			wait for 1001ns;
			SW <= '0';
			wait;
		end process;

		
TopLevel: 
		entity work.QuasiTopLevel
		port map (CLOCK_50=> CLOCK_50, SW=>SW);
										
end tb;
