------------------------------------------------------------------------------
------------------------------------------------------------------------------
--
--  COMS W480 Final Project
--    Sprint 2013
--    A 6502 CPU reconstructed in VHDL and synthesized on the Altera DE2
--
--
-- Team Double O Four is:
--     Yu Chen
--     Jaebin Choi
--     Anthony Erlinger
--     Arthy Padma Anandhi Sundaram
--
--
-- TOP-LEVEL 6502
--
--
------------------------------------------------------------------------------
------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity SixFiveO2 is
  port(
    clk: in std_logic;

    Databus:      in std_logic_vector(7 downto 0);   -- TODO: This should probably be INOUT
    Databus_out:  out std_logic_vector(7 downto 0);  -- TODO: This should probably be INOUT
    Addrbus:  out std_logic_vector(15 downto 0);

    irq:      in std_logic;    -- Active low
    nmi:      in std_logic;    -- Active low
    rdy:      in std_logic;
    
    reset:    in std_logic;    -- Active low
    VEC1_out: buffer std_logic;
    W_R_out:  out std_logic;   -- Write is Active low

    ------------------------------------------------------------------------------
    -- Default external interface (37 active pins)
    --  Sync, sv are unused in this implementation
    --
    --  Internal variables exposed to parent module for debugging purposes:
    ------------------------------------------------------------------------------
    SD1_out:  buffer std_logic;
    SD2_out:  buffer std_logic;
    DOR :     out std_logic_vector(7 downto 0);
    tcstate_out: buffer std_logic_vector(5 downto 0);  -- 6 bit mask for timing state (taken as input to decode ROM)

    ABL_out:  out std_logic_vector(7 downto 0);
    ABH_out:  out std_logic_vector(7 downto 0);
    X_out:    out std_logic_vector(7 downto 0);
    Y_out:    out std_logic_vector(7 downto 0);
    ACC_out:  out std_logic_vector(7 downto 0);

    ACR_out:  out std_logic
  );
end SixFiveO2;

architecture imp of SixFiveO2 is

  -- Programmer visible registers
  signal X_Reg:   std_logic_vector(7 downto 0);
  signal Y_Reg:   std_logic_vector(7 downto 0);
  signal ACC_Reg: std_logic_vector(7 downto 0);
  signal D_reg:   std_logic_vector(7 downto 0);

  signal PC_low:  std_logic_vector(7 downto 0);
  signal PC_high: std_logic_vector(7 downto 0);

  -- Break taken?
  signal Break: std_logic;


  component Control_6502
    port(
      IR          => IR,
      MCycle      => MCycle,
      P           => P,
      LCycle      => LCycle,
      ALU_Op      => ALU_Op,
      Set_BusA_To => Set_BusA_To,
      Set_Addr_To => Set_Addr_To,
      Write_Data  => Write_Data,
      Jump        => Jump,
      BAAdd       => BAAdd,
      BreakAtNA   => BreakAtNA,
      ADAdd       => ADAdd,
      AddY        => AddY,
      PCAdd       => PCAdd,
      Inc_S       => Inc_S,
      Dec_S       => Dec_S,
      LDA         => LDA,
      LDP         => LDP,
      LDX         => LDX,
      LDY         => LDY,
      LDS         => LDS,
      LDDI        => LDDI,
      LDALU       => LDALU,
      LDAD        => LDAD,
      LDBAL       => LDBAL,
      LDBAH       => LDBAH,
      SaveP       => SaveP,
      Write       => Write
    );
  end component;

  component Predecode
    port (
      databus:      in  std_logic_vector(7 downto 0);
      reset:        in  std_logic;
      cycle_number: out	unsigned(3 downto 0);
      Instruction:  out std_logic_vector(7 downto 0);
      BRC, RMW:     out std_logic
    );
  end component;

  component TG
    port(
      clk:          in	std_logic;
      cycle_number: in	unsigned(3 downto 0);
      RMW:          in std_logic;  --read-modify-write instruction
      ACR:          in std_logic;  --carry in from ALU
      BRC:          in std_logic;  --branch flag
      reset:        in	std_logic;
      tcstate:      out	std_logic_vector(5 downto 0);
      SYNC, SD1, SD2: out std_logic;
      VEC1: out std_logic
    );
  end component;

  component CPU
    port(
      clk, SD1, SD2, reset, VEC1: in std_logic;
      opcode: in std_logic_vector(7 downto 0);
      tcstate: in std_logic_vector(5 downto 0);
      databus: in std_logic_vector(7 downto 0);
      ACR_out, W_R: out std_logic;
      ABL_out, 
      ABH_out, 
      DOR, 
      X_out, 
      Y_out, 
      ACC_out: out std_logic_vector(7 downto 0)
    );
  end component;

begin

  PredecodeLogic: Predecode port map(
    databus       => databus,
    reset         => reset,
    cycle_number  => cycle_number,
    Instruction   => Instruction,
    BRC           => BRC,
    RMW           => RMW
  );

  Timing: TG port map (
    clk           => clk,
    cycle_number  => cycle_number,
    RMW           => RMW,
    ACR           => ACR,
    BRC           => BRC,
    reset         => reset,
    tcstate       => tcstate,
    SYNC          => SYNC,
    SD1           => SD1,
    SD2           => SD2,
    VEC1          => VEC1
  );

  Core: CPU port map(
    clk       => clk,
    SD1       => SD1,
    SD2       => SD2,
    VEC1      => VEC1,
    reset     => reset,
    opcode    => opcode,
    tcstate   => tcstate,
    databus   => databus,
    ABL_out   => Addrbus(7 downto 0),
    ABH_out   => Addrbus(15 downto 8),
    DOR       => DOR,
    ACR_out   => ACR,
    W_R       => W_R,
    X_out     => X_Reg,
    Y_out     => Y_Reg,
    ACC_out   => ACC_Reg
  );

end imp;