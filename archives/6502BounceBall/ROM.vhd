library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity rom is
port(addr  : in std_logic_vector(15 downto 0);
		data : out std_logic_vector(7 downto 0));
end rom;

architecture imp of rom is
signal address : unsigned(7 downto 0);
type rom_type is array (0 to 255) of std_logic_vector(7 downto 0);
constant ROM : rom_type :=
(	
-- the 6 lines below are for the LDA, LDX and LDY opcodes in all the different address mode.
-- x"A9", x"11", x"a2", x"22", x"a0", x"33", x"a5", x"20", x"b5", x"20", x"ad", x"21", x"00", x"bd", x"21", x"00",
--	x"B9", x"21", x"00", x"a1", x"22", x"b1", x"22", x"ff", x"ff", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
--	x"ab", x"33", x"22", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
--	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
--	x"00", x"00", x"42", x"43", x"20", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
--	x"00", x"00", x"00", x"00", x"54", x"55", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
--	x"00", x"00", x"00", x"00", x"00", x"00", x"66", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",

--the two lines below are for the INC, DEC opcodes test with immediate address mode.	
--	x"EE", x"20", x"00", x"AD", x"20", x"00", x"EE", x"20", x"00", x"AD", x"20", x"00", x"EE", x"20", x"00", x"AD", 
--	x"20", x"00", x"CE", x"20", x"00", x"AD", x"20", x"00", x"CE", x"20", x"00", x"AD", x"20", x"00", x"ff", x"ff",

--the two lines below are for the CMP absolute test.	
--	x"a9", x"12", x"cd", x"10", x"00", x"cd", x"11", x"00", x"cd", x"12", x"00", x"ff", x"ff", x"00", x"00", x"00",
--	x"11", x"12", x"13", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",

--the 3 lines below are for CPX test with immediate and absolute address modes.
--	x"E0", x"21", x"E0", x"22", x"E0", x"23", x"ff", x"ff", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
--	x"EC", x"10", x"00", x"EC", x"11", x"00", x"EC", x"12", x"00", x"ff", x"ff", x"00", x"00", x"00", x"00", x"00",
--	x"23", x"22", x"21", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",

--the 2 lines below are for CPY test with absolute address mode.	
--	x"CC", x"10", x"00", x"CC", x"11", x"00", x"CC", x"12", x"00", x"ff", x"ff", x"00", x"00", x"00", x"00", x"00",
--	x"33", x"32", x"31", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	
--the line below is for INC, LDA and JMP loop, it will keep increase the value in ACC.	
--	x"ee", x"10", x"00", x"ad", x"10", x"00", x"4c", x"00", x"00", x"ff", x"ff", x"00", x"00", x"00", x"00", x"00",
	
	x"A2", x"00", x"A0", x"00", x"A9", x"A0", x"8D", x"70", x"00", x"A9", x"D6", x"8D", x"71", x"00", --Init1/2 (24, x18)
	x"A9", x"01", x"8D", x"72", x"00", x"A9", x"01", x"8D", x"73", x"00", --Init2/2 (24, x18)
	x"AD", x"72", x"00", x"C9", x"01", x"F0", x"0B", x"D0", x"11", --B1: 0018 (9) --B3 and B4
	x"AD", x"73", x"00", x"C9", x"01", x"F0", x"11", x"D0", x"17", --B2: 0021 (9) --B5 and B6
	x"E8", x"EC", x"70", x"00", 		  x"F0", x"18", x"D0", x"39", --B3: 002A (8) --B7 and B12
	x"CA", x"E0", x"00",               x"F0", x"19", x"D0", x"32", --B4: 0032 (7) --B8 and B120
	x"C8", x"CC", x"71", x"00",        x"F0", x"19", x"D0", x"23", --B5: 0039 (8) --B9 and B11
	x"88", x"C0", x"00",               x"F0", x"1A", x"D0", x"20", --B6: 0041 (7) --B10 and B110
	x"A9", x"00", x"8D", x"72", x"00", x"4C", x"21", x"00", --B7: 0048 (8) --J2
	x"A9", x"01", x"8D", x"72", x"00", x"4C", x"21", x"00", --B8: 0050 (8) --J2
	x"A9", x"00", x"8D", x"73", x"00", x"4C", x"18", x"00", --B9: 0058 (8) --J1
	x"A9", x"01", x"8D", x"73", x"00", x"4C", x"18", x"00", --B10: 0060 (8) --J1
	x"4C", x"18", x"00", --B11: 0068 (3) --J1
	x"4C", x"21", x"00", --B12: 006B (3) --J2
	x"ff", x"ff", --6
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", --7
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", --8
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", --9
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", --10
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", --11
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", --12
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", --13
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", --14
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00" --15

	--B1: 0018
	--B2: 0021
	--B3: 002A
	--B4: 0032
	--B5: 0039
	--B6: 0041
	--B7: 0048
	--B8: 004F
	--B9: 0056
	--B10: 005D
	--B11: 0064
	--B12: 0066
	
	
	);
	
begin
	address<=unsigned(addr(7 downto 0));
	data<=ROM(TO_Integer(address));
end imp;
	
	
	