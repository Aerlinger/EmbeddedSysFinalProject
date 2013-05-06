library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- TOP LEVEL LDA ENTITY
entity LDA is
port(
		Databus : in std_logic_vector(7 downto 0);
		Addrbus : out std_logic_vector(15 downto 0);
    clk     : in std_logic);
end LDA;

architecture imp of LDA is
  signal DB, SB, ADL, ADH : std_logic_vector(7 downto 0);
  signal Pre_decoder_in, Pre_decoder_out : std_logic_vector(7 downto 0);
  signal Cycle_num : std_logic_vector(3 downto 0);
  signal Clk_mask, Clk_mask_bar : std_logic;
  signal tcstate  : std_logic_vector(5 downto 0) :=b"011111";
  signal opcode   : std_logic_vector(7 downto 0);
  signal PCL, PCH, PCLS, PCHS, PCL_Inc, PCH_Inc	: std_logic_vector(7 downto 0);
  signal AI, BI, SUM_OUT, DB_BAR  : std_logic_vector(7 downto 0);
  signal PCLC, DL_DB, DL_ADL, DL_ADH, PCL_PCL, ADL_PCL,I_PC, PCL_DB, PCL_ADL  : std_logic;
  signal PCH_PCH, ADH_PCH, PCH_DB, PCH_ADH, PCH_BH, DB_BAR_ADD, DB_ADD, ADL_ADD  :  std_logic;
  signal O_ADD, SB_ADD, I_ADDC, SUMS, ACR, ADD_ADL, ADD_SB06, ADD_SB7  : std_logic;
  signal SB_X, X_SB, SB_Y, Y_SB, SB_AC, AC_DB, AC_SB, S_SB : std_logic;
  signal ADH_ABH, ADL_ABL, SB_ADH, SB_DB, ANDS, EORS, ORS, SRS, DAA, NewOpcode : std_logic;
  signal O_ADH0, O_ADH17, O_ADL0, O_ADL1, O_ADL2  : std_logic;
  signal PC_Co, T1_flag : std_logic;
  signal AC_Reg, DL_Reg : std_logic_vector(7 downto 0);
  signal PC_Reg  : std_logic_vector(15 downto 0);

  component SI_Latch
  port (
      Din  : in  std_logic_vector(7 downto 0);
      Dout : out std_logic_vector(7 downto 0);
      Load : in  std_logic;
      clk  : in  std_logic);
  end component;

  component SISO_Latch
  port (
      Din  : in  std_logic_vector(7 downto 0);
      Dbus : out std_logic_vector(7 downto 0);
      Load : in std_logic;
      Bus_Enable : in std_logic;
      clk  : in std_logic);
  end component;

  component SITO_Latch
  port (
      Din  : in  std_logic_vector(7 downto 0);
      Dout : out std_logic_vector(7 downto 0);
      Dbus_A : out std_logic_vector(7 downto 0);
      Dbus_B : out std_logic_vector(7 downto 0);
      Load : in std_logic;
      Bus_Enable_A : in std_logic;
      Bus_Enable_B : in std_logic;
      clk  : in std_logic);
  end component;

  component TI_Latch
  port (
      Din_A  : in  std_logic_vector(7 downto 0);
      Din_B  : in  std_logic_vector(7 downto 0);
      Dout : out std_logic_vector(7 downto 0);
      Load_A : in std_logic;
      Load_B : in std_logic;
      clk  : in std_logic);
  end component;

  component ThreeI_Latch
  port (
      Din_A  : in  std_logic_vector(7 downto 0);
      Din_B  : in  std_logic_vector(7 downto 0);
      Din_C  : in  std_logic_vector(7 downto 0);
      Dout : out std_logic_vector(7 downto 0);
      Load_A : in std_logic;
      Load_B : in std_logic;
      Load_C : in std_logic;
      clk  : in std_logic);
  end component;

  component SITO_Latch_ADD
  port (
      Din  : in  std_logic_vector(7 downto 0);
      Dbus_A : out std_logic_vector(7 downto 0);
      Dbus_B : out std_logic_vector(7 downto 0);
      Load : in std_logic;
      Bus_Enable_A : in std_logic;
      Bus_Enable_B_06 : in std_logic;
      Bus_Enable_B_7  : in std_logic;
      clk  : in std_logic);
  end component;

  component SIThreeO_Latch
  port (
      Din  : in  std_logic_vector(7 downto 0);
      Dout : out std_logic_vector(7 downto 0);
      Dbus_A : out std_logic_vector(7 downto 0);
      Dbus_B : out std_logic_vector(7 downto 0);
      Dbus_C : out std_logic_vector(7 downto 0);
      Load : in std_logic;
      Bus_Enable_A : in std_logic;
      Bus_Enable_B : in std_logic;
      Bus_Enable_C : in std_logic;
      clk  : in std_logic);
  end component;

  component Increase_Logic
  port(
      Din  :in  std_logic_vector(7 downto 0);
      Dout :out std_logic_vector(7 downto 0);
      Carry_in :in std_logic;
      Carry_out : out std_logic);
  end component;

  component ALU
  port(
      Din_A  : in std_logic_vector(7 downto 0);
      Din_B  : in std_logic_vector(7 downto 0);
      Dout    : out std_logic_vector(7 downto 0);
      Sum_En : in std_logic;
      I_ADDC : in std_logic; --carry in of ALU
      Carry_out : out std_logic);
  end component;

  component Timing_Generator
  port(
      clk  :in  std_logic;
      clk_mask : in std_logic;
      Cycle_num :in  std_logic_vector(3 downto 0);
      tcstate   :out  std_logic_vector(5 downto 0));
  end component;

  component Control_Logic
  port(
       Opcode  : in std_logic_vector(7 downto 0);
       Timing  : in std_logic_vector(5 downto 0);
       CLK_mask    : in std_logic;
       DL_DB, DL_ADL, DL_ADH, ADH_ABH, ADL_ABL, PCL_PCL,ADL_PCL,I_PC,PCL_DB,
       PCL_ADL,PCH_PCH,ADH_PCH, PCH_DB, PCH_ADH, SB_ADH, SB_DB, DB_ADD, DB_BAR_ADD, 
       ADL_ADD, SUMS, ANDS, EORS, ORS, SRS, DAA, I_ADDC, ADD_ADL, ADD_SB06, ADD_SB7, O_ADD, 
       SB_ADD, SB_AC, AC_DB, AC_SB, SB_X, X_SB, SB_Y, Y_SB,
       O_ADH0, O_ADH17, O_ADL0, O_ADL1, O_ADL2    : out std_logic);
  end component;

  component Predecode
  port(
      Din  : in std_logic_vector(7 downto 0);
      Dout : out std_logic_vector(7 downto 0);
      Cycle_number : out std_logic_vector(3 downto 0));
  end component;

  component Two_Phase_CLK
  port(
      Clk  : in std_logic;
      Clk_mask : out std_logic );
  end component;

  component Inverter8b
  port(
      Din  : in  std_logic_vector(7 downto 0);
      Dout : out std_logic_vector(7 downto 0));
  end component;

  component ANDGate
  port(
      InA : in  std_logic;
      InB : in  std_logic;
      Output : out std_logic);
  end component;

  component Inverter1b
  port(
      A  : in std_logic;
      A_bar : out std_logic);
  end component;

  component PASS_GATE_DBtoSB
  port(
      Din : in std_logic_vector(7 downto 0);
      Dout : out std_logic_vector(7 downto 0);
      SB_DB, DL_DB, PCL_DB, PCH_DB, AC_DB : in std_logic);
  end component;

  component PASS_GATE_SBtoDB
  port(
      Din : in std_logic_vector(7 downto 0);
      Dout : out std_logic_vector(7 downto 0);
      SB_DB, S_SB, ADD_SB06, ADD_SB7, X_SB, Y_SB, AC_SB	: in std_logic);
  end component; 

  component Open_Drain
  port(
      Dout : out std_logic_vector(7 downto 0);
      O_0  : in std_logic;
      O_17 : in std_logic);
  end component;

begin

  DBtoSB: PASS_GATE_DBtoSB port map( Din=>DB, 
                                     Dout=>SB, 
                                     SB_DB=>SB_DB, 
                                     DL_DB=>DL_DB, 
                                     PCL_DB=>PCL_DB, 
                                     PCH_DB=>PCH_DB, 
                                     AC_DB=>AC_DB );

  SBtoDB: PASS_GATE_SBtoDB port map( Din=>SB, 
                                     Dout=>DB, 
                                     SB_DB=>SB_DB, 
                                     S_SB=>S_SB, 
                                     ADD_SB06=>ADD_SB06, ADD_SB7=>ADD_SB7, X_SB=>X_SB, Y_SB=>Y_SB, AC_SB=>AC_SB);

  TwoPhaseClk: Two_Phase_CLK port map(clk=>clk, 
                                      clk_mask=>clk_mask);

  PD: SI_Latch port map(Din=> Databus, 
                         Dout=>Pre_decoder_in, 
                         Load=>Clk_mask_bar, 
                         clk=>clk);
      
  PreDe: Predecode port map(Din=>Pre_decoder_in, 
                            Dout=>Pre_decoder_out, 
                            Cycle_number=>Cycle_num);

  INV1bLogic: Inverter1b port map(A=>clk_mask, 
                                  A_bar=>clk_mask_bar);

  INV1bLogic2: Inverter1b port map(A=>tcstate(4), 
                                   A_bar=>T1_flag);

  ANDLogic: ANDGate port map(InA=>clk_mask, 
                             InB=>T1_flag, 
                             Output=>NewOpcode);

  IR: SI_Latch port map(Din=>Pre_decoder_out, 
                        Dout=>Opcode, 
                        Load=>NewOpcode, 
                        clk=>clk);

  TimeGen: Timing_Generator port map(Cycle_num=>Cycle_num, 
                                      clk_mask=>clk_mask, 
                                      tcstate=>tcstate, 
                                      clk=>clk);

  DL: SIThreeO_Latch port map(Din=>Databus, 
                              Dout=>DL_Reg, 
                              Dbus_A=>DB, 
                              Dbus_B=>ADL, 
                              Dbus_C=>ADH, 
                              Load=>clk_mask_bar, 
                              Bus_Enable_A=>DL_DB, 
                              Bus_Enable_B=>DL_ADL, 
                              Bus_Enable_C=>DL_ADH, 
                              clk=>clk);

  PCLSReg: TI_Latch port map(Din_A=>PCL, 
                              Din_B=>ADL, 
                              Dout=>PCLS, 
                              Load_A=>PCL_PCL, 
                              Load_B=>ADL_PCL, 
                              clk=>clk);

  IncLogic1: Increase_Logic port map(Din=>PCLS, 
                                      Dout=>PCL_Inc, 
                                      Carry_in=>I_PC, 
                                      Carry_out=>PCLC);

  PCLReg: SITO_Latch port map(Din=>PCL_Inc, 
                              Dout=>PC_Reg(7 downto 0), 
                              Dbus_A=>PCL, 
                              Dbus_B=>ADL, 
                              Load=>clk_mask_bar, 
                              Bus_Enable_A=>PCL_DB, 
                              Bus_Enable_B=>PCL_ADL, 
                              clk=>clk);

  PCHSReg: TI_Latch port map(Din_A=>PCH, 
                              Din_B=>ADH, 
                              Dout=>PCHS, 
                              Load_A=>PCH_PCH, 
                              load_B=>ADH_PCH, 
                              clk=>clk);

  IncLogic2: Increase_Logic port map(Din=>PCHS, 
                                      Dout=>PCH_Inc, 
                                      Carry_in=>PCLC, 
                                      Carry_out=>PC_Co);

  PCHReg: SITO_Latch port map(Din=>PCH_Inc, 
                              Dout=>PC_Reg(15 downto 8), 
                              Dbus_A=>PCH, 
                              Dbus_B=>ADH, 
                              Load=>clk_mask, 
                              Bus_Enable_A=>PCH_DB, 
                              Bus_Enable_B=>PCH_ADH, 
                              clk=>clk);

  ABLReg: SI_Latch port map(Din=>ADL, 
                            Dout=>Addrbus(7 downto 0), 
                            Load=>clk_mask, 
                            clk=>clk);

  ABHReg: SI_Latch port map(Din=>ADH, 
                            Dout=>Addrbus(15 downto 8), 
                            Load=>clk_mask, 
                            clk=>clk);

  ResetADH: Open_Drain port map ( Dout=>ADH, 
                                  O_0=>O_ADH0, 
                                  O_17=>O_ADH17);

  AIReg: TI_Latch port map( Din_A=>x"00", 
                            Din_B=>SB, 
                            Dout=>AI, 
                            Load_A=>O_ADD, 
                            Load_B=>SB_ADD, 
                            clk=>clk );

  BIReg: ThreeI_Latch port map( Din_A=>DB_BAR, 
                                Din_B=>DB, 
                                Din_C=>ADL, 
                                Dout=>BI, 
                                Load_A=>DB_bAR_ADD, 
                                Load_B=>DB_ADD, 
                                Load_C=>ADL_ADD, 
                                clk=>clk );

  INV8bLogic:  Inverter8b port map( Din=>DB, 
                                    Dout=>DB_BAR );

  ALULogic: ALU port map (Din_A=>AI, 
                          Din_B=>BI, 
                          Dout=>SUM_OUT, 
                          Sum_En=>SUMS, 
                          I_ADDC=>I_ADDC, 
                          Carry_out=>ACR);

  ADDReg: SITO_Latch_ADD port map (Din=>SUM_OUT, 
                                    Dbus_A=>ADL, 
                                    Dbus_B=>SB, 
                                    Load=>clk_mask, 
                                    Bus_Enable_A=>ADD_ADL, 
                                    Bus_Enable_B_06=>ADD_SB06, 
                                    Bus_Enable_B_7=>ADD_SB7, 
                                    clk=>clk);

  XReg: SISO_Latch port map (Din=>SB, 
                              Dbus=>SB, 
                              Load=>SB_X, 
                              Bus_Enable=>X_SB, 
                              clk=>clk);

  YReg: SISO_Latch port map (Din=>SB, 
                              Dbus=>SB, 
                              Load=>SB_Y, 
                              Bus_Enable=>Y_SB, 
                              clk=>clk);

  ACReg: SITO_Latch port map (Din=>SB, 
                              Dout=>AC_Reg, 
                              Dbus_A=>DB, 
                              Dbus_B=>SB, 
                              Load=>SB_AC, 
                              Bus_Enable_A=>AC_DB, 
                              Bus_Enable_B=>AC_SB, 
                              clk=>clk);

  CtrlLogic: Control_Logic port map (Opcode=>Opcode, 
                                      Timing=>tcstate, 
                                      CLK_mask=>clk_mask, 
                                      DL_DB=>DL_DB, 
                                      DL_ADL=>DL_ADL, 
                                      DL_ADH=>DL_ADH, 
                                      ADH_ABH=>ADH_ABH, 
                                      ADL_ABL=>ADL_ABL,
                                      PCL_PCL=>PCL_PCL, 
                                      ADL_PCL=>ADL_PCL, 
                                      I_PC=>I_PC, 
                                      PCL_DB=>PCL_DB, 
                                      PCL_ADL=>PCL_ADL, 
                                      PCH_PCH=>PCH_PCH, 
                                      ADH_PCH=>ADH_PCH, 
                                      PCH_DB=>PCH_DB,
                                      PCH_ADH=>PCH_ADH, 
                                      SB_ADH=>SB_ADH, 
                                      SB_DB=>SB_DB, 
                                      DB_ADD=>DB_ADD, 
                                      DB_BAR_ADD=>DB_BAR_ADD, 
                                      ADL_ADD=>ADL_ADD, 
                                      SUMS=>SUMS, 
                                      ANDS=>ANDS, 
                                      EORS=>EORS,
                                      ORS=>ORS, 
                                      SRS=>SRS, 
                                      DAA=>DAA, 
                                      I_ADDC=>I_ADDC, 
                                      ADD_ADL=>ADD_ADL, 
                                      ADD_SB06=>ADD_SB06, 
                                      ADD_SB7=>ADD_SB7, 
                                      O_ADD=>O_ADD, 
                                      SB_ADD=>SB_ADD, 
                                      SB_AC=>SB_AC,
                                      AC_DB=>AC_DB, 
                                      AC_SB=>AC_SB, 
                                      SB_X=>SB_X, 
                                      X_SB=>X_SB, 
                                      SB_Y=>SB_Y, 
                                      Y_SB=>Y_SB, 
                                      O_ADH0=>O_ADH0, 
                                      O_ADH17=>O_ADH17, 
                                      O_ADL0=>O_ADL0, 
                                      O_ADL1=>O_ADL1, 
                                      O_ADL2=>O_ADL2);
  
end imp;
