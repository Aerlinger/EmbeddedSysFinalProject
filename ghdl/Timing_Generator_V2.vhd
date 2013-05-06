library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Timing_Generator is
port(
		clk  :in  std_logic;
		Cycle_num :in  unsigned(3 downto 0);
		tcstate   :out  std_logic_vector(6 downto 0));
end Timing_Generator;

architecture rtl of Timing_Generator is
signal Din  : std_logic_vector(6 downto 0) :=b"0000010";
signal Dout : std_logic_vector(6 downto 0) :=b"0000010";
signal D2in : std_logic_vector(6 downto 0);

begin
	process (Dout, Cycle_num)
	begin
	if Dout(1)='1' then  --end of one opcode operation, load new opcode cycle_num.
		case to_integer(Cycle_num) is
			when 2 => Din<=b"0000001"; D2in(0)<='0'; D2in(1)<=Dout(0); D2in(6 downto 2)<=(others=>'0');
			when 3 => Din<=b"0000100"; D2in(0)<=Dout(2); D2in(1)<=Dout(0); D2in(6 downto 2)<=(others=>'0');
			when 4 => Din<=b"0000100"; D2in(0)<=Dout(3); D2in(1)<=Dout(0); D2in(2)<='0'; D2in(3)<=Dout(2); D2in(6 downto 4)<=(others=>'0');
			when 5 => Din<=b"0000100"; D2in(0)<=Dout(4); D2in(1)<=Dout(0); D2in(2)<='0'; D2in(3)<=Dout(2); D2in(4)<=Dout(3); D2in(6 downto 5)<=(others=>'0');
			when 6 => Din<=b"0000100"; D2in(0)<=Dout(5); D2in(1)<=Dout(0); D2in(2)<='0'; D2in(3)<=Dout(2); D2in(4)<=Dout(3); D2in(5)<=Dout(4); D2in(6)<='0';
			when 7 => Din<=b"0000100"; D2in(0)<=Dout(6); D2in(1)<=Dout(0); D2in(2)<='0'; D2in(3)<=Dout(2); D2in(4)<=Dout(3); D2in(5)<=Dout(4); D2in(6)<=Dout(5);
			when others => Din<="0000010";
		end case;
	else Din<=D2in;
	end if;
	end process;
	
	process(clk)
	begin
	if rising_edge(clk) then
	Dout<=Din;
	end if;
	end process;
	
	tcstate<=Dout;
end rtl;

			