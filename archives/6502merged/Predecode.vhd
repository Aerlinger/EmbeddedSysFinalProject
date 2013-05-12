library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Predecode is
port (
		databus  : in     std_logic_vector(7 downto 0);
		reset    : in  std_logic;
		cycle_number : out	unsigned(3 downto 0);
		Instruction  : out 	std_logic_vector(7 downto 0);
		RMW 	 : out std_logic);
end Predecode;

architecture rtl of Predecode is

begin
	process(databus, reset)
	begin
	if reset='1' then
		cycle_number <= x"0";
		Instruction <= x"00";
		RMW <= '0';
	
	else
		Instruction <= databus;
		RMW <= '0';
	--==============================cc=01 section==================================
		if databus(1 downto 0)="01" then
			if databus(4 downto 0)= "00001" then --(zero page, X) with cc=01
				cycle_number <= x"6";
				RMW <= '0';
			elsif databus(4 downto 0) = "00101" then --zero page with cc=01
				cycle_number <= x"3";
				RMW <= '0';
			elsif databus(4 downto 0) = "01001" then --#immediate with cc=01
				cycle_number <= x"2";
				RMW <= '0';
			elsif databus(4 downto 0) = "01101" then --absolute with cc=01
				cycle_number <= x"4";
				RMW <= '0';
			elsif databus(4 downto 0) = "10001" then --(zero page), Y with cc=01
				cycle_number <= x"6";
				RMW <= '0';
			elsif databus(4 downto 0) = "10101" then --zero page, X with cc=01
				cycle_number <= x"4";
				RMW <= '0';
			elsif databus(4 downto 0) = "11001" then --absoulte, Y with cc=01
				cycle_number <= x"5";
				RMW <= '0';
			elsif databus(4 downto 0) = "11001" then --absoulte, X with cc=01
				cycle_number <= x"5";
				RMW <= '0';
			else
				cycle_number<=x"0";
				RMW <= '0';
			end if;
	--==============================cc=01 section ends==============================	

		
	--==============================cc=10 section==================================	
		elsif databus(1 downto 0)="10" then
			--Arthy's code, hex XA: 1xxx1010
			if databus(7)='1' and databus(3 downto 2)="10" then
				RMW <= '0';
				cycle_number<= x"2"; --JB0511. check if wrong.
			
			--Yu's code below..
			--STX, LDX (non read-modify-write code)
			elsif databus(7 downto 6)="10" and not(databus(3 downto 2)="10") then --************arthy
				RMW <= '0';
				if databus(4 downto 2)="000" then --immediate
					cycle_number<= x"2";
				elsif databus(4 downto 2)="001" then --zero page
					cycle_number<= x"3";
				elsif databus(4 downto 2)="010" then --accumulator *****************arthy
					cycle_number<= x"2";
				elsif databus(4 downto 2)="011" then --absolute
					cycle_number<= x"4";
				elsif databus(4 downto 2)="101" then --zero page, X/Y
					cycle_number<= x"4";
				elsif databus(4 downto 2)="111" then  --absolute, X/Y
					cycle_number<= x"5";
				else cycle_number<=x"0"; RMW <= '0';
				end if;
			--6 read-modify-write instructions
			elsif databus(4 downto 2)="010" then --accumulator
				cycle_number<= x"2";
				RMW <= '0';
			else
				RMW <= '1';
				if databus(4 downto 2)="001" then cycle_number<=x"5";  --zero page
				elsif databus(4 downto 2)="011" then cycle_number<=x"6"; --absolute
				elsif databus(4 downto 2)="101" then cycle_number<=x"6"; --zero page, X/Y
				elsif databus(4 downto 2)="111" then cycle_number<=x"7"; --absolute, X/Y
				else cycle_number<=x"0";
				end if;
			end if;
	--==============================cc=10 section ends==================================	

	  --==============================cc=00 section==================================
		elsif databus(1 downto 0)="00" then
			if databus(4 downto 2)="000" and databus(7)='0' then --interrupts
				 if databus(6 downto 5) = "00" then  --BRK
					  cycle_number<=x"7"; --JB need to define VEC separately!
					  RMW <= '0';
				 else  --JSR, RTS, RTI
					  cycle_number<=x"6";
					  RMW <= '0';
				 end if;
			
			else -- among cc=00, all other than interrupts
			
				--Arthy's hex: X8 codes fit here.
				if databus(3 downto 2)="10" then
					RMW <= '0';
					if 	databus(7 downto 4)="0000" then cycle_number<=x"3";
					elsif databus(7 downto 4)="0010" then cycle_number<=x"4";
					elsif databus(7 downto 4)="0100" then cycle_number<=x"3";
					elsif databus(7 downto 4)="0110" then cycle_number<=x"4";
					else											  cycle_number<=x"2";
					end if;
				--end of Arthy's X8 codes.
				
				elsif databus(4 downto 2)="100" then --branch
					  cycle_number<=x"0"; -- 2 for no branch, 3 for branch, 4 for branch w/ page crossing. JB0510: zero.
					  --BRC <= '1'; JB0510 commented out. BRC value is determined by CPU in cycle T2.
					  RMW <= '0';
				--else cycle_number<=x"0"; RMW <= '0';
				--end if;
				elsif databus(4 downto 2)="000" then --immediate
					  cycle_number<=x"2";
					  --BRC <= '0';
					  RMW <= '0';
				--else cycle_number<=x"0"; RMW <= '0';
				--end if;
				elsif databus(4 downto 2)="001" then --zeropage
					  cycle_number<=x"3";
					  --BRC <= '0';
					  RMW <= '0';
				--else cycle_number<=x"0"; RMW <= '0';
				--end if;
				elsif databus(4 downto 2)="011" and databus(7 downto 5)="010" then -- absolute, JMP abs
					  cycle_number<=x"3";
					  --BRC <= '0';
					  RMW <= '0';
				elsif databus(4 downto 2)="011" and databus(7 downto 5)="011" then -- absolute, JMP ind
					  cycle_number<=x"5";
					  --BRC <= '0';
					  RMW <= '0';
				elsif databus(4 downto 2)="011" and not(databus(7 downto 6)="01") then --rest of all absolutes
					  cycle_number<=x"4";
					  --BRC <= '0';
					  RMW <= '0';
				--else cycle_number<=x"0"; RMW <= '0';
				--end if;
				elsif databus(4 downto 2)="101" then --zeropage,X
					  cycle_number<=x"4";
					  --BRC <= '0';
					  RMW <= '0';
				--else cycle_number<=x"0"; RMW <= '0';
				--end if;
				elsif databus(4 downto 2)="111" then --absolute,X
					  cycle_number<=x"5"; --could be 4 w/o page crossing
					  --BRC <= '0';
					  RMW <= '0';
				else cycle_number<=x"0"; RMW <= '0';
				end if;
			end if;
		else cycle_number<=x"0"; RMW <= '0';
		end if;
	--==============================cc=01 section ends==============================
	
	end if;
	end process;
end rtl;


