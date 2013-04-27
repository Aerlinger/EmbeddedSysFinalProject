library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Control_Logic_tb is
end Control_Logic_tb;

architecture tb of Control_Logic_tb is
	signal clk    : std_logic  := '0';
	signal opcode : std_logic_vector(7 downto 0) := x"A9";
	signal timing : std_logic_vector(5 downto 0) :=b"000000";
	signal clk_mask : std_logic :='0';
 
 begin
    	
		process
		begin
			wait for 20 ns; timing     <= b"011111";
			wait for 80 ns; timing     <= b"101111";
			wait;
		end process;
		
		
		process
		begin
			loop
			   clk <= '0'; wait for 20 ns;
			   clk <= '1'; wait for 20 ns;
			end loop;
		end process;
		
		process
		begin
			wait for 60 ns;
			loop
			   clk_mask <= '1'; wait for 40 ns;
			   clk_mask <= '0'; wait for 40 ns;
			end loop;
		end process;
		
--		process
--		begin
--			loop
--			   c      <= '1'after 18 ns;
--			   c      <= '1'; 
--			end loop;
--		end process;
		
								  
CtrlLog: 
		entity work.Control_Logic
		port map (clk_mask=> clk_mask, opcode=>opcode, timing=>timing);
										
end tb;
