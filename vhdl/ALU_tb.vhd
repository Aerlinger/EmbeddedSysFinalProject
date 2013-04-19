library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ALU_tb is
end ALU_tb;

architecture tb of ALU_tb is
	signal clk    : std_logic  := '0';
	signal c      : std_logic  := '0';
   signal Data_A   : std_logic_vector(7 downto 0) := x"FE";
	signal Data_B   : std_logic_vector(7 downto 0) := x"01";
	signal Enable   : std_logic  := '0';

begin
		c      <= '1'after 18ns;	
	   Enable <= '1' after 5ns;	
		
		process
		begin
			loop
			   clk <= '0'; wait for 20ns;
			   clk <= '1'; wait for 20ns;
			end loop;
		end process;
								  
ALU: 
		entity work.ALU
		port map (I_ADDC=> c, Din_A=> Data_A, Din_B=> Data_B, Sum_En=>Enable);
										
end tb;
