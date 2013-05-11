library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity DFF_tb is
end DFF_tb;

architecture tb of DFF_tb is
	signal reset  : std_logic  := '0';
	signal clk    : std_logic  := '0';
	signal enable  : std_logic := '0';
	signal input : std_logic_vector(7 downto 0) :=x"ab";
	 
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
			wait for 33ns;
			enable <= '1';
			wait for 300ns;
			enable<= '0';
			wait;
		end process;

		
		process
		begin
			wait for 100ns;
			input<= x"00";
			wait for 300ns;
			input<= x"11";
			wait;
		end process;

		
								  
DFF: 
		entity work.DFlipFlop
		port map (clk=> clk, input=>input, enable=>enable, reset=>reset);
										
end tb;
