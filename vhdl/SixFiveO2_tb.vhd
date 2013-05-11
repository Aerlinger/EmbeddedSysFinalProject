library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SixFiveO2_tb is
end SixFiveO2_tb;

architecture tb of SixFiveO2_tb is
	signal reset  : std_logic  := '1';
	signal clk    : std_logic  := '0';
	signal databus : std_logic_vector(7 downto 0) :=x"A9";
	 
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
			wait for 101 ns;
			reset <= '0';
			wait;
		end process;

		
		process  --test the first section cc=01
		begin
			wait for 200 ns;
			databus<= x"11";  --(LDA) #=11
			wait for 40 ns;
			databus<= x"09";	--ORA #
			wait for 40 ns;
			databus<= x"22";	--#=22
			wait for 40 ns;
			databus<= x"29";  --AND #
			wait for 40 ns;
			databus<= x"77";  --#=77
			wait for 40 ns;
			databus<= x"49";  --EOR #
			wait for 40 ns;
			databus<= x"77";  --#=77
			wait for 40 ns;
			databus<=x"69";	--ADC #
			wait for 40 ns;
			databus<=x"22";	--#=22
			wait for 40 ns;
			databus<=x"E9";		--SBC
			wait for 40 ns;
			databus<=x"22";  --#=22
			wait for 40 ns;
			databus<=x"8D";  --STA absolute
			wait for 40 ns;
			databus<=x"34";	--ADL
			wait for 40 ns;
			databus<=x"12";	--ADH
			wait for 40 ns;		
			databus<=x"05";	--content in ADH+ADL
			wait for 40 ns;
			databus<=x"C9";	--CMP #
			wait for 40 ns;
			databus<=x"43"; 	--# (Equal)
			wait for 40 ns;
			databus<=x"C9";	--CMP #
			wait for 40 ns;
			databus<=x"00"; 	--# (A>M)
			wait for 40 ns;
			databus<=x"54"; 	--# (A<M)
			wait;
		end process;

--		process  --test the 2nd section cc=10
--		begin
--			wait for 200 ns;
--			databus<= x"11";  --(LDA) #=11
--			wait for 40 ns;
--			databus<= x"0A";	--ASL ACC
--			wait for 80 ns;
--			databus<= x"2A";  --ROL ACC
--			wait for 80 ns;
--			databus<= x"4A";  --LSR ACC
--			wait for 80 ns;
--			databus<=x"6A";	--ROR ACC
--			
--			wait for 80 ns;
--			databus<=x"86";  	 --STX, zero page
--			wait for 40 ns;
--			databus<=x"20";    --zeor page value
--			wait for 40 ns;
--			databus<=x"22";    --content in 0020
--			wait for 40 ns;
--			databus<=x"A2"; 	 --LDX, #
--			wait for 40 ns;
--			databus<=x"33";	 --#
--			wait for 40 ns;
--			databus<=x"CE";	 --DEC absolute
--			wait for 40 ns;		
--			databus<=x"34";	 --ABL
--			wait for 40 ns;
--			databus<=x"12";	 --ABH
--			wait for 40 ns;
--			databus<=x"05";	 --content in ABH+ABL
--			wait for 120 ns;
--			databus<=x"EE";	 --INC absolute
--			wait for 40 ns;
--			databus<=x"34";	 --ABL
--			wait for 40 ns;
--			databus<=x"12";	 --ABH
--			wait for 40 ns;
--			databus<=x"05";	 --content in ABH+ABL
--			wait; 
--		end process;

--		process  --test the address mode with LDA in cc=01
--		begin
--			wait for 200 ns;
--			databus<= x"11";  --(LDA) #=11
--			wait for 40 ns;
--			databus<= x"A1";	--LDA (zp, X)
--			wait for 40 ns;
--			databus<= x"22";	--zp=22 BAL
--			wait for 40 ns;
--			databus<= x"29";  --content in 00+zp(BAL), discarded
--			wait for 40 ns;
--			databus<= x"34";  --ADL (stored in 00+BAL+X)
--			wait for 40 ns;
--			databus<= x"12";  --ADH (stored in 00+BAL+X+1)
--			wait for 40 ns;
--			databus<= x"77";  --content in ADH+ADL
--			wait for 40 ns;
--			databus<=x"A5";	--LDA zp
--			wait for 40 ns;
--			databus<=x"22";	--zp=22
--			wait for 40 ns;
--			databus<=x"E9";	--content in 00+ADL
--			wait for 40 ns;
--			databus<=x"AD";   --LDA Absolute
--			wait for 40 ns;
--			databus<=x"45";   --ADL
--			wait for 40 ns;
--			databus<=x"12";	--ADH
--			wait for 40 ns;		
--			databus<=x"05";	--content in ADH+ADL
--			wait for 40 ns;
--			databus<=x"B1";	--LDA (zp),Y
--			wait for 40 ns;
--			databus<=x"43"; 	--zp=43==>IAL
--			wait for 40 ns;
--			databus<=x"78";	--BAL (stored in 00+zp)
--			wait for 40 ns;
--			databus<=x"56"; 	--BAH (stored in 00+zp+1)
--			wait for 40 ns;
--			databus<=x"54"; 	--Data stored in the BAH+C & BAL+Y
--			wait for 40 ns;
--			databus<=x"B5";   --LDA zp,X
--			wait for 40 ns;
--			databus<=x"20";		--zp=20, BAL
--			wait for 40 ns;
--			databus<=x"23";		--content in 00,BAL discarded
--			wait for 40 ns;
--			databus<=x"12";		--content in 00,BAL+X
--			wait for 40 ns;		
--			databus<=x"B9";		--LDA abs,Y
--			wait for 40 ns;
--			databus<=x"34";		--BAL
--			wait for 40 ns;
--			databus<=x"12";		--BAH
--			wait for 40 ns;
--			databus<=x"44";		--content in BAH, BAL+Y
--			wait for 40 ns;		
--			databus<=x"BD";		--LDA zp,X
--			wait for 40 ns;
--			databus<=x"34";	 --BAL
--			wait for 40 ns;
--			databus<=x"12";		--BAH
--			wait for 40 ns;
--			databus<=x"55";		--content in BAH, BAL+X
--			wait;
--		end process;

		
								  
SixFiveOTwo: 
		entity work.SixFiveO2
		port map (clk=> clk, reset=>reset, databus=>databus);
										
end tb;
