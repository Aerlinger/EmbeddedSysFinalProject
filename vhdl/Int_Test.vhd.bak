library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Int_Test is
port(
		Databus :in std_logic_vector(7 downto 0);
		Addrbus :out std_logic_vector(15 downto 0);
      reset, clock   :in std_logic);
end Int_Test;

architecture imp of Int_Test is
signal Clk : std_logic;
signal SYNC, BRC, VEC1 : std_logic;
signal DB, SB, ADL, ADH : std_logic_vector(7 downto 0);
signal Pre_decoder_out, IR_In : std_logic_vector(7 downto 0);
signal Cycle_number : std_logic_vector(3 downto 0);
signal tcstate  : std_logic_vector(5 downto 0) :=b"011111";
signal opcode   : std_logic_vector(7 downto 0);
signal PCL, PCH, PCL_Inc, PCH_Inc, PCL_In, PCH_In, PCH_Pre_In	: std_logic_vector(7 downto 0);
signal AI, BI, AI_In, BI_In, ACC_In, X_In, Y_In, ADD, DB_BAR, ACC, X, Y, S, S_In  : std_logic_vector(7 downto 0);
signal PCLC, DL_DB, DL_ADL, DL_ADH, PCL_PCL, ADL_PCL,I_PC, PCL_DB, PCL_ADL  : std_logic;
signal PCH_PCH, ADH_PCH, PCH_DB, PCH_ADH, PCH_BH, DB_BAR_ADD, DB_ADD, ADL_ADD  :  std_logic;
signal O_ADD, SB_ADD, I_ADDC, SUMS, ACR, ADD_ADL, ADD_SB, SB_S  : std_logic;
signal SB_X, X_SB, SB_Y, Y_SB, SB_AC, AC_DB, AC_SB, S_SB, S_ADL : std_logic;
signal ADH_ABH, ADL_ABL, SB_ADH, SB_DB, ANDS, EORS, ORS, SRS, DAA, NewOpcode : std_logic;
signal O_ADH, O_ADL  : std_logic;
signal star_1, star_2, star_3, star_4 : std_logic;
--unuseful signals, just for completion
signal PC_Co : std_logic;

component reg
port(
		data_in: in std_logic_vector(7 downto 0);
		data_out: out std_logic_vector(7 downto 0);
		clk: in std_logic
	 );
end component;

component mux2
port(
		sel : in std_logic_vector(1 downto 0);
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		y	: out	std_logic_vector(7 downto 0)
	 );
end component;

component mux3
port(
		sel : in std_logic_vector(2 downto 0);
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		c 	: in	std_logic_vector(7 downto 0);
		y	: out	std_logic_vector(7 downto 0)
	);
end component;

component mux4
port(
		sel : in std_logic_vector(3 downto 0);
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		c 	: in	std_logic_vector(7 downto 0);
		d 	: in	std_logic_vector(7 downto 0);
		y	: out	std_logic_vector(7 downto 0)
	);
end component;

component mux5
port(
		sel : in std_logic_vector(4 downto 0);
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		c 	: in	std_logic_vector(7 downto 0);
		d 	: in	std_logic_vector(7 downto 0);
		e 	: in	std_logic_vector(7 downto 0);
		y	: out	std_logic_vector(7 downto 0)
	);
end component;

component mux7
port(
		sel : in std_logic_vector(6 downto 0);
		
		a 	: in	std_logic_vector(7 downto 0);
		b 	: in	std_logic_vector(7 downto 0);
		c 	: in	std_logic_vector(7 downto 0);
		d 	: in	std_logic_vector(7 downto 0);
		e 	: in	std_logic_vector(7 downto 0);
		f 	: in	std_logic_vector(7 downto 0);
		g 	: in	std_logic_vector(7 downto 0);

		y	: out	std_logic_vector(7 downto 0)
	);

end component;

component TG
port(
		clk		 : in	std_logic;
		cycle_number	 : in	std_logic_vector(3 downto 0);
		ACR	 : in std_logic;  --carry in from ALU
		BRC	 : in std_logic;  --branch flag
		reset	 : in	std_logic;
		tcstate	 : out	std_logic_vector(5 downto 0);
		SYNC	 : out std_logic;
		VEC1 	 : out std_logic
	);
end component;

component PreDecode
port(
		Din  : in std_logic_vector(7 downto 0);
		Dout : out std_logic_vector(7 downto 0);
		Cycle_number : out std_logic_vector(3 downto 0));
end component;

component RCL
port(
		 Opcode  : in std_logic_vector(7 downto 0);
		 tcstate  : in std_logic_vector(5 downto 0);
--		 CLK     : in std_logic;
		 DL_DB, DL_ADL, DL_ADH, ADH_ABH, ADL_ABL, PCL_PCL,ADL_PCL,I_PC,PCL_DB,
		 PCL_ADL,PCH_PCH,ADH_PCH, PCH_DB, PCH_ADH, SB_ADH, SB_DB, DB_ADD, DB_BAR_ADD, 
		 ADL_ADD, SUMS, ANDS, EORS, ORS, SRS, DAA, I_ADDC, ADD_ADL, ADD_SB06, ADD_SB7, O_ADD, 
		 SB_ADD, SB_AC, AC_DB, AC_SB, SB_X, X_SB, SB_Y, Y_SB, 
		 O_ADH0, O_ADH17, O_ADL0, O_ADL1, O_ADL2    : out std_logic);
end component;

component Increase_Logic
port(
		Din  :in  std_logic_vector(7 downto 0);
		Dout :out std_logic_vector(7 downto 0);
		Carry_in :in std_logic;
		Carry_out : out std_logic);
end component;

component Inverter8b
port(
		Din  : in  std_logic_vector(7 downto 0);
		Dout : out std_logic_vector(7 downto 0));
end component;

component Star1
port(
		SB_DB, S_SB, ADD_SB, X_SB, Y_SB, AC_SB, SB_ADH, DL_ADH, O_ADH, PCH_ADH : in std_logic;
		y	: out	std_logic
	);
end component;

component Star2
port(
		SB_DB, DL_DB, PCL_DB, PCH_DB, AC_DB : in std_logic;
		y	: out	std_logic
	);
end component;

component Star3
port(
		SB_ADH, DL_ADH, O_ADH, PCH_ADH : in std_logic;
		y	: out	std_logic
	);
end component;

component Star4
port(
		SB_ADH, S_SB, ADD_SB, X_SB, Y_SB, AC_SB, SB_DB, DL_DB, PCL_DB, PCH_DB, AC_DB : in std_logic;
		y	: out	std_logic
	);
end component;

begin
--control path
PreDecodeLogic: PreDecode port map(Din=>Databus, Dout=>pre_decoder_out, cycle_number=>cycle_number);

IRInput: mux2 port map(sel(0)=>SYNC, sel(1)=>'1', a=>Pre_decoder_out, b=>opcode, y=>IR_In);

IR: reg port map(data_in=>IR_In, data_out=>opcode, clk=>clk);

Timing: TG port map(clk=>clk, cycle_number=>cycle_number, ACR=>ACR, BRC=>BRC, reset=>reset, tcstate=>tcstate, SYNC=>SYNC, VEC1=>VEC1);

--RandomCtrl: RCL port map();

--data path
PCLCarryin: Increase_Logic port map(Din=>ADL, Dout=>PCL_Inc, Carry_in=>'1', Carry_out=>PCLC);

PLHCarryin: Increase_Logic port map(Din=>ADH, Dout=>PCH_Inc, Carry_in=>'1', Carry_out=>PC_Co);

PCLInput: mux2 port map(sel(0)=>PCL_PCL, sel(1)=>ADL_PCL, a=>PCL, b=>PCL_Inc, y=>PCL_In);

PCHInput: mux2 port map(sel(0)=>PCLC, sel(1)=>'0', a=>PCH_Inc, b=>ADH, y=>ADL);

PCHInput2: mux2 port map(sel(0)=>PCH_PCH, sel(1)=>ADH_PCH, a=>PCH, b=>PCH_Pre_In, y=>PCH_in);

PCLReg: reg port map(data_in=>PCL_In, data_out=>PCL, clk=>clk);

PCHReg: reg port map(data_in=>PCH_In, data_out=>PCH, clk=>clk);

AIInput: mux2 port map(sel(0)=>SB_ADD, sel(1)=>O_ADD, a=>SB, b=>x"00", y=>AI_In);

DBBar: Inverter8b port map(Din=>DB, Dout=>DB_BAR);

BIInput: mux3 port map(sel(0)=>DB_ADD, sel(1)=>DB_BAR_ADD, sel(2)=>ADL_ADD, a=>DB, b=>DB_BAR, c=>ADL, y=>BI_In);

AIReg: reg port map(data_in=>AI_In, data_out=>AI, clk=>clk);

BIReg: reg port map(data_in=>BI_In, data_out=>BI, clk=>clk);

--ALU: ALU port map();

SInput: mux2 port map(sel(0)=>SB_S, sel(1)=>'0', a=>SB, b=>S, y=>S_In);

SIReg: reg port map(data_in=>S_in, data_out=>S, clk=>clk);

ACCIn: mux2 port map(sel(0)=>SB_AC, sel(1)=>'0', a=>SB, b=>ACC, y=>ACC_In);

ACCReg: reg port map(data_in=>ACC_In, data_out=>ACC, clk=>clk);

XIn: mux2 port map(sel(0)=>SB_X, sel(1)=>'0', a=>SB, b=>X, y=>X_In);

XReg: reg port map(data_in=>X_In, data_out=>X, clk=>clk);

YIn: mux2 port map(sel(0)=>SB_Y, sel(1)=>'0', a=>SB, b=>Y, y=>Y_In);

YReg: reg port map(data_in=>Y_In, data_Out=>Y, clk=>clk);

Star1Logic: star1 port map(SB_DB=>SB_DB, S_SB=>S_SB, ADD_SB=>ADD_SB, X_SB=>X_SB, Y_SB=>Y_SB, AC_SB=>AC_SB, 
							 SB_ADH=>SB_ADH, DL_ADH=>DL_ADH, O_ADH=>O_ADH, PCH_ADH=>PCH_ADH, y=>star_1);

DBBus: mux5 port map(sel(0)=>DL_DB, sel(1)=>PCL_DB, sel(2)=>PCH_DB, sel(3)=>star_1, sel(4)=>AC_DB,
							a=>Databus, b=>PCL, c=>PCH, d=>SB, e=>ACC);

Star2Logic: star2 port map(SB_DB=>SB_DB, DL_DB=>DL_DB, PCL_DB=>PCL_DB, PCH_DB=>PCH_DB, AC_DB=>AC_DB, y=>star_2);

Star3Logic: star3 port map(SB_ADH=>SB_ADH, DL_ADH=>DL_ADH, O_ADH=>O_ADH, PCH_ADH=>PCH_ADH, y=>star_3);

SBBus: mux7 port map(sel(0)=>star_2, sel(1)=>star_3, sel(2)=>S_SB, sel(3)=>ADD_SB, sel(4)=>X_SB, sel(5)=>Y_SB, sel(6)=>AC_SB,
							a=>DB, b=>ADH, c=>S, d=>ADD, e=>X, f=>Y, g=>ACC, y=>SB);	

ADLBus: mux5 port map(sel(0)=>DL_ADL, sel(1)=>PCL_ADL, sel(2)=>O_ADL, sel(3)=>S_ADL, sel(4)=>ADD_ADL, 
							a=>Databus, b=>PCL, c=>x"00", d=>S, e=>ADD, y=>ADL);

Star4Logic: star4 port map(SB_ADH=>SB_ADH, S_SB=>S_SB, ADD_SB=>ADD_SB, X_SB=>X_SB, Y_SB=>Y_SB, AC_SB=>AC_SB, 
							SB_DB=>SB_DB, DL_DB=>DL_DB, PCL_DB=>PCL_DB, PCH_DB=>PCH_DB, AC_DB=>AC_DB, y=>star_4);

ADHBus: mux4 port map(sel(0)=>DL_ADH, sel(1)=>O_ADH, sel(2)=>PCH_ADH, sel(3)=>star_4,
							a=>Databus, b=>x"00", c=>PCH, d=>SB);

	

	
	--Addrbus<=(others => '0');
end imp;