library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Control_Logic is
	port(
		Opcode : in std_logic_vector(7 downto 0);
		Timing : in std_logic_vector(5 downto 0);
		
		--		 CLK     : in std_logic;
		CLK_mask : in std_logic;
		DL_DB, 
		DL_ADL, 
		DL_ADH, 
		ADH_ABH, 
		ADL_ABL, 
		PCL_PCL,
		ADL_PCL,
		I_PC,
		PCL_DB,
		PCL_ADL,
		PCH_PCH,
		ADH_PCH, 
		PCH_DB, 
		PCH_ADH, 
		SB_ADH, 
		SB_DB, 
		DB_ADD, 
		DB_BAR_ADD, 

		ADL_ADD, 
		SUMS, 
		ANDS, 
		EORS, 
		ORS, 
		SRS, 
		DAA, 
		I_ADDC, 
		ADD_ADL, 
		ADD_SB06, 
		ADD_SB7, 
		O_ADD, 

		SB_ADD, 
		SB_AC, 
		AC_DB, 
		AC_SB, 
		SB_X, 
		X_SB, 
		SB_Y, 
		Y_SB, 

		O_ADH0, 
		O_ADH17, 
		O_ADL0, 
		O_ADL1, 
		O_ADL2 : out std_logic
	);
	end Control_Logic;

	architecture rtl of Control_Logic is
	signal Input_Latch : unsigned(2 downto 0);
	signal PCount : unsigned(8 downto 0);
	signal Address_Bus : unsigned(1 downto 0);
	signal Data_Bus : std_logic;
	signal ALU : unsigned(11 downto 0);
	signal ADD : unsigned(2 downto 0);
	signal AC : unsigned(2 downto 0);
	signal XY : unsigned(3 downto 0);
	signal ResetAD : unsigned(4 downto 0);

begin
	process(Opcode, Timing,CLK_mask)
	begin
	--A9T0: 
	    if Opcode=x"A9" and Timing=b"011111" and CLK_mask='0' then
			Input_Latch <= b"000";
			PCount <= b"0000_0011_1";  --seems to be the opposite in our case, double check needed
			Address_Bus <= b"11";  --always 11 on phi_1 and 00 on phi_2 
			Data_Bus <= '1';
			ALU <= b"10000_00_10_010";
			ADD <= b"011";
			AC <= b"000";
			XY <= b"00_00";
			ResetAD <= b"00_000";
			
		elsif Opcode=x"A9" and Timing=b"011111" and CLK_mask='1' then
			Input_Latch <= b"100";  --DL/DB
			PCount <= b"0011_0011_1";
			Address_Bus <= b"00";
			Data_Bus <= '1';
			ALU <= b"10000_00_00_000";
			ADD <= b"000";
			AC <= b"000";
			XY <= b"00_00";
			ResetAD <= b"00_000";
	
	 --A9T1:
         elsif Opcode=x"A9" and Timing=b"101111" and CLK_mask='0' then
			Input_Latch <= b"100";    --DL/DB
			PCount <= b"0000_0011_1";
			Address_Bus <= b"11";
			Data_Bus <= '1';
			ALU <= b"10000_00_10_010";
			ADD <= b"000";
			AC <= b"001";   --SB/AC
			XY <= b"00_00";
			ResetAD <= b"00_000";
			
		elsif Opcode=x"A9" and Timing=b"101111" and CLK_mask='1' then
			Input_Latch <= b"000";  
			PCount <= b"0011_0011_1";
			Address_Bus <= b"00";
			Data_Bus <= '1';
			ALU <= b"10000_00_00_000";
			ADD <= b"011";
			AC <= b"000";
			XY <= b"00_00";
			ResetAD <= b"00_000";	
			
	--A5T2
		elsif Opcode=x"A5" and Timing=b"110111" and CLK_mask='0' then
			Input_Latch <= b"000";    
			PCount <= b"0000_0011_1";
			Address_Bus <= b"11";
			Data_Bus <= '1';
			ALU <= b"10000_00_10_010";
			ADD <= b"011";
			AC <= b"000";   
			XY <= b"00_00";
			ResetAD <= b"00_000";
			
		elsif Opcode=x"A5" and Timing=b"110111" and CLK_mask='1' then
			Input_Latch <= b"000";  
			PCount <= b"1100_0000_0";
			Address_Bus <= b"00";
			Data_Bus <= '0';
			ALU <= b"10000_00_00_000";
			ADD <= b"000";
			AC <= b"000";
			XY <= b"00_00";
			ResetAD <= b"11_000";
	--A5T0
		elsif Opcode=x"A5" and Timing=b"011111" and CLK_mask='0' then
			Input_Latch <= b"010";    
			PCount <= b"0000_0011_0";
			Address_Bus <= b"11";
			Data_Bus <= '0';
			ALU <= b"10000_00_10_010";
			ADD <= b"000";
			AC <= b"000";   
			XY <= b"00_00";
			ResetAD <= b"11_000";
			
		elsif Opcode=x"A5" and Timing=b"011111" and CLK_mask='1' then
			Input_Latch <= b"100";  
			PCount <= b"0011_0011_1";
			Address_Bus <= b"00";
			Data_Bus <= '1';
			ALU <= b"10000_00_00_000";
			ADD <= b"000";
			AC <= b"000";
			XY <= b"00_00";
			ResetAD <= b"00_000";
	--A5T1
		elsif Opcode=x"A5" and Timing=b"101111" and CLK_mask='0' then
			Input_Latch <= b"100";    --DL/DB
			PCount <= b"0000_0011_1";
			Address_Bus <= b"11";
			Data_Bus <= '1';
			ALU <= b"10000_00_10_010";
			ADD <= b"000";
			AC <= b"001";   --SB/AC
			XY <= b"00_00";
			ResetAD <= b"00_000";
			
		elsif Opcode=x"A5" and Timing=b"101111" and CLK_mask='1' then
			Input_Latch <= b"000";  
			PCount <= b"0011_0011_1";
			Address_Bus <= b"00";
			Data_Bus <= '1';
			ALU <= b"10000_00_00_000";
			ADD <= b"011";
			AC <= b"000";
			XY <= b"00_00";
			ResetAD <= b"00_000";	
		
	 --Reset State:	
		elsif Timing =b"101111" and CLK_mask='0' then
			Input_Latch <= b"000";
			PCount <= b"0000_0011_1";
			Address_Bus <= b"11";
			Data_Bus <= '0';
			ALU <= b"10000_00_10_010";
			ADD <= b"011";
			AC <= b"000";
			XY <= b"00_00";
			ResetAD <= b"00_000";
			
			elsif Timing=b"101111" and CLK_mask='1' then
			Input_Latch <= b"000";
			PCount <= b"0011_0011_1";
			Address_Bus <= b"00";
			Data_Bus <= '0';
			ALU <= b"10000_00_10_010";
			ADD <= b"011";
			AC <= b"000";
			XY <= b"00_00";
			ResetAD <= b"00_000";
			
		end if;
	end process;
	
	DL_DB <= Input_Latch(2); 
	DL_ADL <= Input_Latch(1); 
	DL_ADH <= Input_Latch(0);
	PCL_PCL <= PCount(8); 
	PCH_PCH <= PCount(7); 
	ADL_PCL <= PCount(6); 
	ADH_PCH <= PCount(5); 
	PCL_DB <= PCount(4); 
	PCH_DB <= PCount(3); 
	PCL_ADL <= PCount(2); 
	PCH_ADH <= PCount(1); 
	I_PC <= PCount(0);
   	ADH_ABH <= Address_Bus(1); 
   	ADL_ABL <= Address_Bus(0);
	SB_DB <= Data_Bus;
	SUMS <= ALU(11); 
	ANDS <= ALU(10); 
	EORS <= ALU(9); 
	ORS <= ALU(8); 
	SRS <= ALU(7); 
	DAA <= ALU(6); 
	I_ADDC <= ALU(5);
	SB_ADD <= ALU(4); 
	O_ADD <= ALU(3); 
	DB_BAR_ADD <= ALU(2); 
	DB_ADD <= ALU(1); 
	ADL_ADD <= ALU(0);
	ADD_ADL <= ADD(2); 
	ADD_SB06 <= ADD(1); 
	ADD_SB7 <= ADD(0);
   	AC_DB <= AC(2); 
   	AC_SB <= AC(1); 
   	SB_AC <= AC(0);
   	SB_X <= XY(3); 
   	X_SB <= XY(2); 
   	SB_Y <= XY(1); 
   	Y_SB <= XY(0);
	O_ADH0 <= ResetAD(4); 
	O_ADH17 <= ResetAD(3); 
	O_ADL0 <= ResetAD(2); 
	O_ADL1 <= ResetAD(1); 
	O_ADL2 <= ResetAD(0);
	
end rtl;	
	
			