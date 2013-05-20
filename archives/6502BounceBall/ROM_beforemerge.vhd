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
	
--the 2 lines below are for branch test: BPL 	
--	x"a9", x"05", x"c9", x"05", x"10", x"10", x"a2", x"00", x"ff", x"ff", x"00", x"00", x"00", x"00", x"00", x"00",
--	x"00", x"00", x"00", x"00", x"00", x"00", x"a0", x"00", x"ff", x"ff", x"00", x"00", x"00", x"00", x"00", x"00",
	
	x"e8", x"c8", x"4c", x"00", x"00", x"ff", x"ff", x"ff", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
   x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",	
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
   x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",	
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00");
	
begin
	address<=unsigned(addr(7 downto 0));
	data<=ROM(TO_Integer(address));
end imp;
	
	
	