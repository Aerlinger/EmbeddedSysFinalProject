library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity DFlipFlop_tb is
end DFlipFlop_tb;

architecture tb of DFlipFlop_tb is
	signal reset  : std_logic  := '0';
	signal clk    : std_logic  := '0';
	signal enable  : std_logic := '0';
	signal data_in : std_logic_vector(7 downto 0) :=x"ab";
	 
 begin

	process
	begin
		loop
		   clk <= '0'; 
		   wait for 20 ns;
		   clk <= '1'; 
		   wait for 20 ns;
		end loop;
	end process;
	
	process
	begin
		wait for 33 ns;
		enable <= '1';
		wait for 300 ns;
		enable<= '0';
		wait;
	end process;

	process
	begin
		wait for 100 ns;
		data_in<= x"00";
		wait for 300 ns;
		data_in<= x"11";
		wait;
	end process;

	DFF:
		entity work.DFlipFlop
		port map (
			clk=> clk, 
			data_in=>data_in, 
			enable=>enable, 
			reset=>reset
		);
										
end tb;
