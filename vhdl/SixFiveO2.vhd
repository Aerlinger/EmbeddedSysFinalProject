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
use ieee.numeric_std.all;

entity SixFiveO2 is
  port(

    ------------------------------------------------------------------------------
    -- Default external interface (37 active pins)
    --  Sync, sv are unused in this implementation
    ------------------------------------------------------------------------------
    Databus:  in std_logic_vector(7 downto 0);  -- TODO: This should probably be INOUT
    Addrbus:  out std_logic_vector(15 downto 0);
    clk:      in std_logic;
    rdy:      in std_logic;
    reset:    in std_logic;  -- Active low
    irq:      in std_logic;    -- Active low
    nmi:      in std_logic;    -- Active low

    W_R: out std_logic;   -- Write is Active low


    ------------------------------------------------------------------------------
    -- Internal variables exposed to parent module for debugging purposes:
    ------------------------------------------------------------------------------
    DOR :     out std_logic_vector(7 downto 0);
    tcstate_out: buffer std_logic_vector(5 downto 0);  -- 6 bit mask for timing state (taken as input to decode ROM)

    ABL_out:  out std_logic_vector(7 downto 0);
    ABH_out:  out std_logic_vector(7 downto 0);
    X_out:    out std_logic_vector(7 downto 0);
    Y_out:    out std_logic_vector(7 downto 0);
    ACC_out:  out std_logic_vector(7 downto 0);

    SD1_out:  buffer std_logic;
    SD2_out:  buffer std_logic;
    VEC1_out: buffer std_logic;
    ACR_out:  out std_logic
  );
end SixFiveO2;

architecture imp of SixFiveO2 is

  signal instruction, opcode : std_logic_vector(7 downto 0);

  signal tcstate: std_logic_vector(5 downto 0);
  signal cycle_number: unsigned(3 downto 0);
  signal BRC:   std_logic;
  signal ACR:   std_logic;
  signal RMW:   std_logic;
  signal SYNC:  std_logic;
  signal SD1:   std_logic;
  signal SD2:   std_logic;
  signal VEC1:  std_logic;
  signal W_R :  std_logic;

  -- Programmer visible registers
  signal X_Reg: std_logic_vector(7 downto 0);
  signal Y_Reg: std_logic_vector(7 downto 0);
  signal ACC_Reg: std_logic_vector(7 downto 0);

  component Predecode
    port (
      databus:      in  std_logic_vector(7 downto 0);
      reset:        in  std_logic;
      cycle_number: out	unsigned(3 downto 0);
      Instruction:  out std_logic_vector(7 downto 0);
      BRC, RMW:     out std_logic
    );
  end component;

  component DFlipFlop
    port(
      input  : in std_logic_vector(7 downto 0);
      enable : in  std_logic;
      clk    : in std_logic;
      reset  : in std_logic;
      output : out std_logic_vector(7 downto 0)
    );
  end component;

  component TG
    port(
      clk:      in	std_logic;
      cycle_number: in	unsigned(3 downto 0);
      RMW:      in std_logic;  --read-modify-write instruction
      ACR:        in std_logic;  --carry in from ALU
      BRC:        in std_logic;  --branch flag
      reset:      in	std_logic;
      tcstate:    out	std_logic_vector(5 downto 0);
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

  IR: DFlipFlop port map(
    input   => instruction,
    enable  => SYNC,
    clk     => clk,
    reset   => reset,
    output  => opcode
  );

  Timing: TG port map(
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