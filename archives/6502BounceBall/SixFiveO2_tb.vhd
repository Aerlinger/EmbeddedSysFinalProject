library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SixFiveO2_tb is
end SixFiveO2_tb;

architecture tb of SixFiveO2_tb is
	signal reset  : std_logic  := '1';
	signal clk    : std_logic  := '0';
	signal databus : std_logic_vector(7 downto 0) :=x"00";
	 
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
			wait for 100ns; --why 200ns?
			reset <= '0';
			wait;
		end process;

		
		process  --test the first section cc=01
		begin
			wait for 120ns; --why 520ns?
			databus<= x"e8";  --LDA imm (2)
			wait for 80ns;
			databus<= x"c8";  --ACC<=05
			wait for 80ns;
			
			databus<= x"4c";  --cmp immed (2)
			wait for 40ns;
			databus<= x"00";  --immed<=05
			
			wait for 40ns;
			databus<= x"00";  --BPL (2)
			wait for 40ns;
			databus<= x"e8";  --offset<=22
			
			wait for 40ns;
			databus<= x"c8";  --next opcode LDY 00
				
			wait for 40ns;
			databus<= x"Ad";  --ACC<=11
			wait for 40ns;
			
			databus<= x"12";  --LDX imm (2)
			wait for 40ns;
			databus<= x"00";  --X<=22
			wait for 40ns;
			databus<= x"00";  --X<=22
			
--			--reset A=11,X=22,Y=33
--			databus<= x"A9";  --LDA imm (2)
--			wait for 40ns;
--			databus<= x"11";  --ACC<=11
--			wait for 40ns;
--			
--			databus<= x"A2";  --LDX imm (2)
--			wait for 40ns;
--			databus<= x"22";  --X<=22
--			wait for 40ns;
--			
--			databus<= x"A0";  --LDY imm (2)
--			wait for 40ns;
--			databus<= x"33";  --Y<=33
--			wait for 40ns;
--			
--			
--			--1. LDA, all address modes 
--			databus<= x"A5";  --LDA zp (3)
--			wait for 40ns;
--			databus<= x"40";  --zp address
--			wait for 40ns;
--			databus<= x"ab";  --value in 0040
--			wait for 40ns;
--			
--			databus<= x"B5";  --LDA zp,X (4)
--			wait for 40ns;
--			databus<= x"40";  --operand.
--			wait for 40ns;
--			databus<= x"62";  --40+22
--			wait for 40ns;
--			databus<= x"ef";  --value inside 0062
--			wait for 40ns;
--			
--			databus<= x"AD";  --LDA abs (4)
--			wait for 40ns;
--			databus<= x"cd";  --LL
--			wait for 40ns;
--			databus<= x"ab";  --HH
--			wait for 40ns;
--			databus<= x"99";  --value in abcd
--			wait for 40ns;
--			
--			databus<= x"BD";  --LDA abs,X (4+)
--			wait for 40ns;
--			databus<= x"ef";  --LL
--			wait for 40ns;
--			databus<= x"cd";  --HH
--			wait for 40ns;
--			databus<= x"ff";  --dummy for page crossing.
--			wait for 40ns;
--			databus<= x"07";  --value in cdef+22=ce11
--			wait for 40ns;
--			
--			databus<= x"BD";  --LDA abs,X (4+) --------------same, but without page crossing.
--			wait for 40ns;
--			databus<= x"66";  --LL
--			wait for 40ns;
--			databus<= x"cd";  --HH
--			wait for 40ns;
--			--databus<= x"ff";  --dummy for page crossing.
--			--wait for 40ns;
--			databus<= x"99";  --value in cd66+22=cd88
--			wait for 40ns;
--			
--			databus<= x"B9";  --LDA abs,Y (4+)
--			wait for 40ns;
--			databus<= x"ef";  --LL
--			wait for 40ns;
--			databus<= x"cd";  --HH
--			wait for 40ns;
--			databus<= x"ff";  --dummy for page crossing.
--			wait for 40ns;
--			databus<= x"77";  --value in cdef+22=ce22
--			wait for 40ns;
--						
--			databus<= x"A1";  --LDA ind,X (6): ($77,X)
--			wait for 40ns;
--			databus<= x"88";  --zp address (+1 cycle to compute 88+22=aa. zp wraparound.)
--			wait for 80ns;---80
--			databus<= x"34";  --value in 00aa
--			wait for 40ns;
--			databus<= x"12";  --value in 00ab
--			wait for 40ns;
--			databus<= x"88";  --value in 1234
--			wait for 40ns;
--			
--			databus<= x"B1";  --LDA ind,Y (5+): ($77),Y
--			wait for 40ns;
--			databus<= x"77";  --zp address
--			wait for 40ns;
--			databus<= x"ef";  --value in 0077
--			wait for 40ns;
--			databus<= x"cd";  --value in 0078 (+1 cycle if page crossed)
--			wait for 80ns;---80
--			databus<= x"05";  --value in ce22
--			wait for 40ns;
--			-- end of LDA, all address modes
--			
--			--2. LDX, all address modes
--			
--			databus<= x"A2";  --LDX imm (2)
--			databus<= x"A2";  --LDX zp (3)
--			databus<= x"A2";  --LDX zp,Y (4)
--			databus<= x"A2";  --LDX abs (4)
--			databus<= x"A2";  --LDX abs,Y (4+)
			
			
			
			
			wait;
		end process;

--		process  --test the 2nd section cc=10
--		begin
--			wait for 200ns;
--			databus<= x"11";  --(LDA) #=11
--			wait for 40ns;
--			databus<= x"0A";	--ASL ACC
--			wait for 80ns;
--			databus<= x"2A";  --ROL ACC
--			wait for 80ns;
--			databus<= x"4A";  --LSR ACC
--			wait for 80ns;
--			databus<=x"6A";	--ROR ACC
--			
--			wait for 80ns;
--			databus<=x"86";  	 --STX, zero page
--			wait for 40ns;
--			databus<=x"20";    --zeor page value
--			wait for 40ns;
--			databus<=x"22";    --content in 0020
--			wait for 40ns;
--			databus<=x"A2"; 	 --LDX, #
--			wait for 40ns;
--			databus<=x"33";	 --#
--			wait for 40ns;
--			databus<=x"CE";	 --DEC absolute
--			wait for 40ns;		
--			databus<=x"34";	 --ABL
--			wait for 40ns;
--			databus<=x"12";	 --ABH
--			wait for 40ns;
--			databus<=x"05";	 --content in ABH+ABL
--			wait for 120ns;
--			databus<=x"EE";	 --INC absolute
--			wait for 40ns;
--			databus<=x"34";	 --ABL
--			wait for 40ns;
--			databus<=x"12";	 --ABH
--			wait for 40ns;
--			databus<=x"05";	 --content in ABH+ABL
--			wait; 
--		end process;

--		process  --test the address mode with LDA in cc=01
--		begin
--			wait for 200ns;
--			databus<= x"11";  --(LDA) #=11
--			wait for 40ns;
--			databus<= x"A1";	--LDA (zp, X)
--			wait for 40ns;
--			databus<= x"22";	--zp=22 BAL
--			wait for 40ns;
--			databus<= x"29";  --content in 00+zp(BAL), discarded
--			wait for 40ns;
--			databus<= x"34";  --ADL (stored in 00+BAL+X)
--			wait for 40ns;
--			databus<= x"12";  --ADH (stored in 00+BAL+X+1)
--			wait for 40ns;
--			databus<= x"77";  --content in ADH+ADL
--			wait for 40ns;
--			databus<=x"A5";	--LDA zp
--			wait for 40ns;
--			databus<=x"22";	--zp=22
--			wait for 40ns;
--			databus<=x"E9";	--content in 00+ADL
--			wait for 40ns;
--			databus<=x"AD";   --LDA Absolute
--			wait for 40ns;
--			databus<=x"45";   --ADL
--			wait for 40ns;
--			databus<=x"12";	--ADH
--			wait for 40ns;		
--			databus<=x"05";	--content in ADH+ADL
--			wait for 40ns;
--			databus<=x"B1";	--LDA (zp),Y
--			wait for 40ns;
--			databus<=x"43"; 	--zp=43==>IAL
--			wait for 40ns;
--			databus<=x"78";	--BAL (stored in 00+zp)
--			wait for 40ns;
--			databus<=x"56"; 	--BAH (stored in 00+zp+1)
--			wait for 40ns;
--			databus<=x"54"; 	--Data stored in the BAH+C & BAL+Y
--			wait for 40ns;
--			databus<=x"B5";   --LDA zp,X
--			wait for 40ns;
--			databus<=x"20";		--zp=20, BAL
--			wait for 40ns;
--			databus<=x"23";		--content in 00,BAL discarded
--			wait for 40ns;
--			databus<=x"12";		--content in 00,BAL+X
--			wait for 40ns;		
--			databus<=x"B9";		--LDA abs,Y
--			wait for 40ns;
--			databus<=x"34";		--BAL
--			wait for 40ns;
--			databus<=x"12";		--BAH
--			wait for 40ns;
--			databus<=x"44";		--content in BAH, BAL+Y
--			wait for 40ns;		
--			databus<=x"BD";		--LDA zp,X
--			wait for 40ns;
--			databus<=x"34";	 --BAL
--			wait for 40ns;
--			databus<=x"12";		--BAH
--			wait for 40ns;
--			databus<=x"55";		--content in BAH, BAL+X
--			wait;
--		end process;

		
								  
SixFiveOTwo: 
		entity work.SixFiveO2
		port map (clk=> clk, reset=>reset, databus=>databus);
										
end tb;
