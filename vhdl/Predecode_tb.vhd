library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Predecode_tb is
end Predecode_tb;

architecture tb of Predecode_tb is
	signal reset  : std_logic  := '1';
	--signal clk    : std_logic  := '0';
	signal databus : std_logic_vector(7 downto 0) :=x"A9";
	 
 begin

--		process
--		begin
--			loop
--			   clk <= '0'; wait for 20 ns;
--			   clk <= '1'; wait for 20 ns;
--			end loop;
--		end process;
		
  process
  begin
    wait for 101 ns;
    reset <= '0';
    wait;
  end process;

PredecodeLogic: 
  entity work.Predecode
  port map (reset=>reset, databus=>databus);
										
end tb;
