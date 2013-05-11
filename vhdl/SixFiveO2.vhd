library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SixFiveO2 is
port(
		Databus :in std_logic_vector(7 downto 0);
		Addrbus :out std_logic_vector(15 downto 0);
		DOR     : out std_logic_vector(7 downto 0);
      reset, clk   :in std_logic;
		XL, XH, YL, YH, ACCL, ACCH : out std_logic_vector(6 downto 0));
end SixFiveO2;

architecture imp of SixFiveO2 is

  signal instruction, opcode : std_logic_vector(7 downto 0);
  signal tcstate : std_logic_vector(5 downto 0);
  signal cycle_number : unsigned(3 downto 0);
  signal BRC, ACR, RMW, SYNC, SD1, SD2, VEC1, W_R : std_logic;
  --signal DOR, databus  : std_logic_vector(7 downto 0);
  --signal Addrbus: std_logic_vector(15 downto 0);
  signal X_Reg, Y_Reg, ACC_Reg  : std_logic_vector(7 downto 0);

  component Predecode
  port (
      databus  : in     std_logic_vector(7 downto 0);
      reset    : in  std_logic;
      cycle_number : out	unsigned(3 downto 0);
      Instruction  : out 	std_logic_vector(7 downto 0);
      BRC, RMW 	 : out std_logic);
  end component;

  component DFlipFlop
  port(
      input  : in std_logic_vector(7 downto 0);
      enable : in  std_logic;
      clk    : in std_logic;
      reset  : in std_logic;
      output : out std_logic_vector(7 downto 0));
  end component;

  component TG
  port(
      clk		 : in	std_logic;
      cycle_number	 : in	unsigned(3 downto 0);
      RMW    : in std_logic;  --read-modify-write instruction
      ACR	 : in std_logic;  --carry in from ALU
      BRC	 : in std_logic;  --branch flag
      reset	 : in	std_logic;
      tcstate	 : out	std_logic_vector(5 downto 0);
      SYNC, SD1, SD2	 : out std_logic;
      VEC1 	 : out std_logic);
  end component;

  component CPU
  port(
      clk, SD1, SD2, reset, VEC1    : in std_logic;
      opcode : in std_logic_vector(7 downto 0);
      tcstate : in std_logic_vector(5 downto 0);
      databus : in std_logic_vector(7 downto 0);
      ACR_out, W_R     : out std_logic;
      ABL_out, ABH_out, DOR, X_out, Y_out, ACC_out : out std_logic_vector(7 downto 0)
      );
  end component;

  --component Memory
  --	port (
  --	clk, reset : in std_logic;
  --	we : in std_logic;
  --	address : in std_logic_vector(15 downto 0);
  --	di : in std_logic_vector(7 downto 0);
  --	do : out std_logic_vector(7 downto 0)
  --   );
  --end component;

  component hex7seg
  port
      ( input : in std_logic_vector(3 downto 0); -- A number 
         output : out std_logic_vector(6 downto 0)); -- Just bits
  end component;


begin
  PredecodeLogic: Predecode port map(databus=>databus, reset=>reset, cycle_number=>cycle_number, Instruction=>Instruction, BRC=>BRC, RMW=>RMW);

  IR: DFlipFlop port map(input=>instruction, enable=>SYNC, clk=>clk, reset=>reset, output=>opcode);

  Timing: TG port map(clk=>clk, cycle_number=>cycle_number, RMW=>RMW, ACR=>ACR, BRC=>BRC, reset=>reset, tcstate=>tcstate, SYNC=>SYNC, SD1=>SD1, SD2=>SD2, VEC1=>VEC1);

  Core: CPU port map(clk=>clk, SD1=>SD1, SD2=>SD2, VEC1=>VEC1, reset=>reset, opcode=>opcode, tcstate=>tcstate, databus=>databus, ABL_out=>Addrbus(7 downto 0), ABH_out=>Addrbus(15 downto 8), DOR=>DOR, ACR_out=>ACR, W_R=>W_R, X_out=>X_Reg, Y_out=>Y_Reg, ACC_out=>ACC_Reg);

  --Mem: Memory port map(clk=>clk, reset=>reset, we=>W_R, address=>Addrbus, di=>DOR, do=>databus);

  XHDis: hex7seg port map(input=>X_Reg(7 downto 4), output=>XH);
  XLDis: hex7seg port map(input=>X_Reg(3 downto 0), output=>XL);

  YHDis: hex7seg port map(input=>Y_Reg(7 downto 4), output=>YH);
  YLDis: hex7seg port map(input=>Y_Reg(3 downto 0), output=>YL);

  ACCHDis: hex7seg port map(input=>ACC_Reg(7 downto 4), output=>ACCH);
  ACCLDis: hex7seg port map(input=>ACC_Reg(3 downto 0), output=>ACCL);

end imp;
