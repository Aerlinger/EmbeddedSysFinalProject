library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Predecode is
port (
		databus  : in     std_logic_vector(7 downto 0);
		reset    : in  std_logic;
		cycle_number : out	unsigned(3 downto 0);
		Instruction  : out 	std_logic_vector(7 downto 0);
		BRC, RMW 	 : out std_logic);
end Predecode;

architecture rtl of Predecode is

begin
	process(databus, reset)
	begin
	if reset='1' then
		cycle_number <= x"0";
		Instruction <= x"00";
		BRC <= '0';
		RMW <= '0';
	
	else
		Instruction <= databus;
--==============================cc=01 section==================================
		if databus(4 downto 0)= "00001" then --(zero page, X) with cc=01
			cycle_number <= x"6";
			BRC <= '0';
			RMW <= '0';
		elsif databus(4 downto 0) = "00101" then --zero page with cc=01
			cycle_number <= x"3";
			BRC <= '0';
			RMW <= '0';
		elsif databus(4 downto 0) = "01001" then --#immediate with cc=01
			cycle_number <= x"2";
			BRC <= '0';
			RMW <= '0';
		elsif databus(4 downto 0) = "01101" then --absolute with cc=01
			cycle_number <= x"4";
			BRC <= '0';
			RMW <= '0';
		elsif databus(4 downto 0) = "10001" then --(zero page), Y with cc=01
			cycle_number <= x"6";
			BRC <= '0';
			RMW <= '0';
		elsif databus(4 downto 0) = "10101" then --zero page, X with cc=01
			cycle_number <= x"4";
			BRC <= '0';
			RMW <= '0';
		elsif databus(4 downto 0) = "11001" then --absoulte, Y with cc=01
			cycle_number <= x"5";
			BRC <= '0';
			RMW <= '0';
		elsif databus(4 downto 0) = "11001" then --absoulte, X with cc=01
			cycle_number <= x"5";
			BRC <= '0';
			RMW <= '0';
		end if;
--==============================cc=01 section ends==============================	

--==============================cc=10 section==================================	
		if databus(1 downto 0)="10" then
			--STX, LDX (non read-modify-write code)
			if (databus(7 downto 5)="100" or databus(7 downto 5)="101") then	
				BRC <= '0';
				RMW <= '0';
				if databus(4 downto 2)="000" then --immediate
					cycle_number<= x"2";
				elsif databus(4 downto 2)="001" then --zero page
					cycle_number<= x"3";
				elsif databus(4 downto 2)="010" then --accumulator
					cycle_number<= x"2";
				elsif databus(4 downto 2)="011" then --absolute
					cycle_number<= x"4";
				elsif databus(4 downto 2)="101" then --zero page, X/Y
					cycle_number<= x"4";
				elsif databus(4 downto 2)="111" then  --absolute, X/Y
					cycle_number<= x"5";
				end if;
			--6 read-modify-write instructions
			elsif databus(4 downto 2)="010" then --accumulator
				cycle_number<= x"2";
				BRC <= '0';
				RMW <= '0';
			else
				BRC <= '0';
				RMW <= '1';
				if databus(4 downto 2)="001" then cycle_number<=x"5";  --zero page
				elsif databus(4 downto 2)="011" then cycle_number<=x"6"; --absolute
				elsif databus(4 downto 2)="101" then cycle_number<=x"6"; --zero page, X/Y
				elsif databus(4 downto 2)="111" then cycle_number<=x"7"; --absolute, X/Y
				end if;
			end if;
		end if;	
--==============================cc=10 section ends==================================	

  --==============================cc=00 section==================================
        if databus(1 downto 0)="00" then
            if databus(4 downto 2)="000" and databus(7)='0' then --interrupts
                if databus(6 downto 5) = "00" then  --BRK
                    cycle_number<=x"7"; --JB need to define VEC separately!
                    BRC <= '0';
                    RMW <= '0';
                else  --JSR, RTS, RTI
                    cycle_number<=x"6";
                    BRC <= '0';
                    RMW <= '0';
                end if;
            else -- all other than interrupts
                if databus(4 downto 2)="100" then --branch
                    cycle_number<=x"4"; -- 2 for no branch, 3 for branch, 4 for branch w/ page crossing
                    BRC <= '1';
                    RMW <= '0';
                end if;
                if databus(4 downto 2)="000" then --immediate
                    cycle_number<=x"2";
                    BRC <= '0';
                    RMW <= '0';
                end if;
                if databus(4 downto 2)="001" then --zeropage
                    cycle_number<=x"3";
                    BRC <= '0';
                    RMW <= '0';
                end if;
                if databus(4 downto 2)="011" and databus(7 downto 5)="010" then -- absolute, JMP abs
                    cycle_number<=x"3";
                    BRC <= '0';
                    RMW <= '0';
                elsif databus(4 downto 2)="011" and databus(7 downto 5)="011" then -- absolute, JMP ind
                    cycle_number<=x"5";
                    BRC <= '0';
                    RMW <= '0';
                elsif databus(4 downto 2)="011" then --rest of all absolutes
                    cycle_number<=x"4";
                    BRC <= '0';
                    RMW <= '0';
                end if;
                if databus(4 downto 2)="101" then --zeropage,X
                    cycle_number<=x"4";
                    BRC <= '0';
                    RMW <= '0';
                end if;
                if databus(4 downto 2)="111" then --absolute,X
                    cycle_number<=x"5"; --could be 4 w/o page crossing
                    BRC <= '0';
                    RMW <= '0';
                end if;
            end if;
        end if;
--==============================cc=01 section ends==============================
					
	end if;
	end process;
end rtl;


