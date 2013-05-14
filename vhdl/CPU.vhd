------------------------------------------------------------------------------
------------------------------------------------------------------------------
--
--  CPU.vhd: 6502 Core Architecture
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
-- 6502 Core
--
------------------------------------------------------------------------------
------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


------------------------------------------------------------------------------
--------------- 6502 CORE ARCHITECTURE ---------------------------------------
------------------------------------------------------------------------------
entity CPU is
  port(
    clk, 
    SD1,
    SD2,
    reset,
    VEC1: in std_logic;

    opcode: in std_logic_vector(7 downto 0);
    tcstate: in std_logic_vector(5 downto 0);
    databus: in std_logic_vector(7 downto 0);

    ACR_out,
    W_R,
    BRC: out std_logic; -- JB0510 added BRC as CPU output

    ABL_out,
    ABH_out,
    DOR,
    X_out,
    Y_out,
    ACC_out : out std_logic_vector(7 downto 0)
  );
end CPU;

architecture rtl of CPU is

  component ALU is
    -- Identical to entity declaration  - AE
    port(
      AI:     in unsigned(7 downto 0);
      BI:     in unsigned(7 downto 0);
      ADD:    out unsigned(7 downto 0);
      P:      in unsigned(7 downto 0);
      opcode: in unsigned(7 downto 9);

      ANDS:   in std_logic;
      SUMS:   in std_logic;
      ORS:    in std_logic;
      EORS:   in std_logic;
      SRS:    in std_logic;

      I_ADDC: in std_logic;
      Mask_shortcut: in std_logic;
      AVR:    out std_logic;
      ACR:    out std_logic
    );
  end component;

  signal ABL, ABH : std_logic_vector(7 downto 0);

  signal  X, 
          Y, 
          ACC, 
          S, 
          AI, 
          BI, 
          ADD, 
          P : unsigned(7 downto 0);

  signal PC: unsigned(15 downto 0) := (others=>'0');

  signal  SUMS, 
          I_ADDC, 
          ORS, 
          ANDS, 
          EORS, 
          SRS : std_logic;

  signal ACR: std_logic;
  signal Mask_shortcut: std_logic;

begin

  ACR_out <= ACR;

  -- ALU DEFINITION ----------------------------------------------------
  -----------------------------------------------------------------------------

  U_ALU: ALU port map(
    AI,
    BI,
    ADD,
    P,
    opcode,

    ANDS,
    SUMS,
    ORS,
    EORS,
    SRS,

    I_ADDC,
    Mask_shortcut,
    AVR,
    ACR
  );


  -- PROCESS DECLARATIONS -----------------------------------------------------
  -----------------------------------------------------------------------------

  process(ABH, ABL, ACC, X, Y)
  begin
      ABH_out <= ABH;
      ABL_out <= ABL;
      ACC_out <= std_logic_vector(ACC);
      X_out   <= std_logic_vector(X);
      Y_out   <= std_logic_vector(Y);
  end process;

  ----- CLOCK RISING EDGE: ---------------------------------------------------
  -----------------------------------------------------------------------------
  process(clk, reset)
  begin

    if reset = '1' then
      PC            <= x"0001";
      ABL           <= x"00";
      ABH           <= x"00";
      X             <= x"01";
      Y             <= x"01";
      ACC           <= x"00";
      AI            <= x"00";
      BI            <= x"00";
      S             <= x"00";
      DOR           <= x"00";
      SUMS          <= '0';
      ORS           <= '0';
      ANDS          <= '0';
      EORS          <= '0';
      SRS           <= '0';
      I_ADDC        <= '0';
      W_R           <= '1';
      SUMS          <= '1';
      Mask_shortcut <= '0';
      P             <= x"00";

    elsif reset = '0' then

      if rising_edge(clk) then

        --  this part will be taken care by "BRK" later.
        --  if (opcode=x"00" and tcstate(1)='0') then
        --    PC <= PC + 1;
        --    ABL <= std_logic_vector(PC(7 Downto 0));
        --    ABH <= std_logic_vector(PC(15 Downto 8));
        --  end if;

        ---------------------------Yu's code starts here----------------------------
        -----------------------= bbb is the only concern ------------------------=
        if not(opcode(1 downto 0)="00") then --exclude the cc=00 part to avoid overlapping
        --Address Mode: Absolute; aaa: don't care; cc: don't care.

          --Address Mode: Absolute;aaa: don't care;cc: don't care.
          --Timing: T2
          if (opcode(4 downto 2)="011" and tcstate(2)='0' ) then
            PC <= PC + 1;
            ABL <= std_logic_vector(PC(7 Downto 0));
            ABH <= std_logic_vector(PC(15 Downto 8));
            Sums <= '1';
            AI <= x"00";
            BI <= unsigned(Databus);
            I_ADDC <= '0';
          end if;

          --Timing: T3
          if (opcode(4 downto 2)="011" and tcstate(3)='0' ) then
            PC <= PC;
            ABL <= std_logic_vector(ADD);
            ABH <= databus;
            SUMS <= '0';
          end if;

          --Address Mode: Zero page, X;aaa: don't care;cc: don't care.
          --Timing T2
          if (opcode(4 downto 2)="101" and tcstate(2)='0' and (not((opcode(7 downto 5)="100" or 
              opcode(7 downto 5)="101") and opcode(1 downto 0)="10"))) then
            PC <= PC;
            ABL <= Databus;
            ABH <= x"00";
            AI <= unsigned(X);
            BI <= unsigned(Databus);
            Sums <= '1';
          end if;

          --Timing T3
          if (opcode(4 downto 2)="101" and tcstate(3)='0' ) then
            PC <= PC;
            ABL <= std_logic_vector(ADD);
            ABH <= x"00";
            SUMS<='0';
          end if;

          --Address Mode: Absolute X;aaa: don't care;cc: don't care.
          --Timing T2
          if (opcode(4 downto 2)="111" and tcstate(2)='0' and (not(opcode(7 downto 5)="101" and opcode(1 downto 0)="10"))) then
            PC <= PC + 1;
            ABL <= std_logic_vector(PC(7 Downto 0));
            ABH <= std_logic_vector(PC(15 Downto 8));
            AI <= unsigned(X);
            BI <= unsigned(Databus);
            Sums <= '1';

            if opcode(7 downto 5)="100" then
              Mask_shortcut <= '1';
            end if;
          end if;

          --Timing T3
          --no page crossing
          if (opcode(4 downto 2)="111" and tcstate(3)='0' and ACR='0' ) then
            PC <= PC;
            ABL <= std_logic_vector(ADD);
            ABH <= Databus;
            Mask_shortcut <= '0';
          end if;

          --page crossing
          if (opcode(4 downto 2)="111" and tcstate(3)='0' and ACR='1' ) then
            PC <= PC;
            ABL <= std_logic_vector(ADD);
            ABH <= x"00";
            AI <= x"00";
            BI <= unsigned(Databus);
            I_ADDC <= '1';
            Sums <= '1';
            Mask_shortcut <= '0';
          end if;

          --Timing T4
          if (opcode(4 downto 2)="111" and tcstate(4)='0' ) then
            PC <= PC;
            ABL <= ABL;
            ABH <= std_logic_vector(ADD);
            SUMS<='0';
          end if;

          --Address Mode: Zero Page;aaa: don't care;cc: don't care.
          --Timing T2
          if ( opcode(4 downto 2)="001" and tcstate(2)='0' ) then
            PC <= PC;
            ABL <= Databus;
            ABH <= x"00";
          end if;

        end if; --exclude the cc=00 part to avoid overlapping
        -----------------------=bbb is the only concern ends---------------------

        -----------------------=bbb and cc=01 are concerned------------------------------
        --Address Mode: Absolute Y;aaa: don't care;cc: 01
        --Timing T2
        if (opcode(4 downto 2)="110" and opcode(1 downto 0)="01" and tcstate(2)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          AI <= unsigned(Y);
          BI <= unsigned(Databus);
          Sums <= '1';

          if opcode(7 downto 5)="100" then
            Mask_shortcut <= '1';
          end if;
        end if;

        --Timing T3
          --no page crossing
        if (opcode(4 downto 2)="110" and opcode(1 downto 0)="01" and tcstate(3)='0' and ACR='0' ) then
          PC <= PC;
          ABL <= std_logic_vector(ADD);
          ABH <= Databus;
          Sums <= '0';
          Mask_shortcut <= '1';
        end if;

          --page crossing
        if (opcode(4 downto 2)="110" and opcode(1 downto 0)="01" and tcstate(3)='0' and ACR='1' ) then
          PC <= PC;
          ABL <= std_logic_vector(ADD);
          ABH <= x"00";
          AI <= x"00";
          BI <= unsigned(Databus);
          I_ADDC <= '1';
          Sums <= '1';
          Mask_shortcut <= '1';
        end if;

        --Timing T4
        if (opcode(4 downto 2)="110" and opcode(1 downto 0)="01" and tcstate(4)='0' ) then
          PC <= PC;
          ABL <= ABL;
          ABH <= std_logic_vector(ADD);
          Sums <= '0';
        end if;

        --Address Mode: (Zero page, X)/Indirect, X;aaa: don't care;cc: 01
        --T2
        if (opcode(4 downto 2)="000" and opcode(1 downto 0)="01" and tcstate(2)='0' ) then
          PC <= PC;
          ABH <= x"00";
          ABL <= Databus;
          AI <= X;
          BI <= unsigned(Databus);
          Sums <= '1';
        end if;

        --T3
        if (opcode(4 downto 2)="000" and opcode(1 downto 0)="01" and tcstate(3)='0' ) then
          PC <= PC;
          ABH <= x"00";
          ABL <= std_logic_vector(ADD);
          AI <= x"00";
          BI <= ADD;
          I_ADDC <= '1';
          Sums <= '1';
          Mask_shortcut <= '1';
        end if;

        --T4
        if (opcode(4 downto 2)="000" and opcode(1 downto 0)="01" and tcstate(4)='0' ) then
          PC <= PC;
          ABH <= x"00";
          ABL <= std_logic_vector(ADD);
          AI <= x"00";
          BI <= unsigned(Databus);
          Sums <= '1';
          I_ADDC <= '0';
          Mask_shortcut <= '0';
        end if;

        --T5
        if (opcode(4 downto 2)="000" and opcode(1 downto 0)="01" and tcstate(5)='0' ) then
          PC <= PC;
          ABH <= Databus;
          ABL <= std_logic_vector(ADD);
          Sums <= '0';
        end if;

        --Address Mode: (Zero page), Y/Indirect, Y;aaa: don't care;cc: 01
        --T2
        if (opcode(4 downto 2)="100" and opcode(1 downto 0)="01" and tcstate(2)='0' ) then
          PC <= PC;
          ABH <= x"00";
          ABL <= Databus;
          AI <= x"00";
          BI <= unsigned(Databus);
          Sums <= '1';
          I_ADDC <= '1';
        end if;

        --T3
        if (opcode(4 downto 2)="100" and opcode(1 downto 0)="01" and tcstate(3)='0' ) then
          PC <= PC;
          ABH <= x"00";
          ABL <= std_logic_vector(ADD);
          AI <= Y;
          BI <= unsigned(Databus);
          Sums <= '1';
          I_ADDC <= '0';

          if opcode(7 downto 5)="100" then
            Mask_shortcut <= '1';
          end if;
        end if;

        --T4
        --no page crossing
        if (opcode(4 downto 2)="100" and opcode(1 downto 0)="01" and tcstate(4)='0' and ACR='0') then
          PC <= PC;
          ABH <= Databus;
          ABL <= std_logic_vector(ADD);
          Mask_shortcut <= '0';
          Sums <= '0';
        end if;

        --page crossing
        if (opcode(4 downto 2)="100" and opcode(1 downto 0)="01" and tcstate(4)='0' and ACR='1') then
          PC <= PC;
          ABH <= Databus;
          ABL <= std_logic_vector(ADD);
          AI <= x"00";
          BI <= unsigned(Databus);
          Sums <= '1';
          I_ADDC <= '1';
          Mask_shortcut <= '0';
        end if;

        --T5
        if (opcode(4 downto 2)="100" and opcode(1 downto 0)="01" and tcstate(5)='0' ) then
          PC <= PC;
          ABH <= std_logic_vector(ADD);
          ABL <= ABL;
          I_ADDC <= '0';
          Sums <= '0';
        end if;
        -----------------------=bbb and cc=01 are concerned ends------------------------------

        -----------------------=aaa and cc=01 are concerned---------------------------------==
        --Instruction: LDA; aaa: 101; bbb: don't care; cc: 01
        --T0
        if (opcode(7 downto 5)="101" and opcode(1 downto 0)="01" and tcstate(0)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          ACC <= unsigned(Databus);
        end if;

        --T1
        if (opcode(7 downto 5)="101" and opcode(1 downto 0)="01" and tcstate(1)='0' ) then
          PC  <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          P(7)<=ACC(7);
          SUMS<='0';

          if ACC(7)='1' then
            P(7) <= '1';
          else
            P(7) <= '0';
          end if;

          if ACC=x"00" then
            P(1) <= '1';
          else
            P(1) <= '0';
          end if;
        end if;

          --Instruction: ORA;aaa: 000;bbb: don't care;cc: 01
        --T0
        if (opcode(7 downto 5)="000" and opcode(1 downto 0)="01" and tcstate(0)='0' ) then
          PC    <= PC + 1;
          ABL   <= std_logic_vector(PC(7 Downto 0));
          ABH   <= std_logic_vector(PC(15 Downto 8));
          AI    <= ACC;
          BI    <= unsigned(Databus);
          ORS   <= '1';
          SUMS  <= '0';
        end if;

        --T1
        if (opcode(7 downto 5)="000" and opcode(1 downto 0)="01" and tcstate(1)='0' ) then
          PC  <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          ACC <= ADD;
          ORS <= '0';

          if ADD(7)='1' then
            P(7) <= '1';
          else
            P(7) <= '0';
          end if;

          if ADD=x"00" then
            P(1) <= '1';
          else
            P(1) <= '0';
          end if;
        end if;

        --Instruction: AND; aaa: 001; bbb: don't care; cc: 01
        --T0
        if (opcode(7 downto 5)="001" and opcode(1 downto 0)="01" and tcstate(0)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          AI <= ACC;
          BI <= unsigned(Databus);
          ANDS <= '1';
          SUMS <= '0';
        end if;

        --T1
        if (opcode(7 downto 5)="001" and opcode(1 downto 0)="01" and tcstate(1)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          ACC <= ADD;
          ANDS <= '0';

          if ADD(7)='1' then
            P(7) <= '1';
          else
            P(7) <= '0';
          end if;

          if ADD=x"00" then
            P(1) <= '1';
          else
            P(1) <= '0';
          end if;
        end if;

        --Instruction: EOR;aaa: 010;bbb: don't care;cc: 01
        --T0
        if (opcode(7 downto 5)="010" and opcode(1 downto 0)="01" and tcstate(0)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          AI <= ACC;
          BI <= unsigned(Databus);
          EORS <= '1';
          SUMS <= '0';
        end if;

        if (opcode(7 downto 5)="010" and opcode(1 downto 0)="01" and tcstate(1)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          ACC <= ADD;
          EORS <= '0';

          if ADD(7)='1' then
            P(7) <= '1';
          else
            P(7) <= '0';
          end if;

          if ADD=x"00" then
            P(1) <= '1';
          else
            P(1) <= '0';
          end if;
        end if;

        --Instruction: ADC;aaa: 011;bbb: don't care;cc: 01
        --T0
        if (opcode(7 downto 5)="011" and opcode(1 downto 0)="01" and tcstate(0)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          AI <= ACC;
          BI <= unsigned(Databus);
          SUMS <= '1';
          I_ADDC <= P(0);
        end if;

        --T1
        if (opcode(7 downto 5)="011" and opcode(1 downto 0)="01" and tcstate(1)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          ACC <= ADD;
          SUMS <= '0';
          I_ADDC <= '0';

          if ADD(7)='1' then
            P(7) <= '1';
          else
            P(7) <= '0';

          end if;

          if ADD=x"00" then
            P(1) <= '1';
          else
            P(1) <= '0';
          end if;

          if ACR='1' then
            P(0) <= '1';
          else
            P(0) <= '0';
          end if;
        end if;


        --Instruction: CMP;aaa: 110;bbb: don't care;cc: 01
        --T0
        if (opcode(7 downto 5)="110" and opcode(1 downto 0)="01" and tcstate(0)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          AI <= ACC;
          BI <= unsigned(Databus);
          I_ADDC <= '1';
          SUMS <= '1';
        end if;

        --T1
        if (opcode(7 downto 5)="110" and opcode(1 downto 0)="01" and tcstate(1)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          ACC <= ADD;
          I_ADDC <= '0';
          SUMS <= '0';

          if ADD(7)='1' then
            P(7) <= '1';
          else P(7) <= '0';
          end if;

          if ADD=x"00" then
            P(1) <= '1';
          else
            P(1) <= '0';
          end if;

          if signed(std_logic_vector(AI)) < signed(std_logic_vector(BI)) then
            P(0) <= '1';
          else
            P(0) <= '0';
          end if;
        end if;

        --Instruction: SBC;aaa: 111;bbb: don't care;cc: 01
        --T0
        if (opcode(7 downto 5)="111" and opcode(1 downto 0)="01" and tcstate(0)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          AI <= ACC;
          BI <= unsigned(not(Databus));
          I_ADDC <= P(0);
          SUMS <= '1';
        end if;

        --T1
        if (opcode(7 downto 5)="111" and opcode(1 downto 0)="01" and tcstate(1)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          ACC <= ADD;
          SUMS <= '0';
          I_ADDC <= '0';

          if ADD(7)='1' then
            P(7) <= '1';
          else
            P(7) <= '0';
          end if;

          if ADD=x"00" then
            P(1) <= '1';
          else
            P(1) <= '0';
          end if;

          if ACR='0' then
            P(0) <= '1';
          else
            P(0) <= '0';
          end if;
        end if;


        --Instruction: STA;aaa: 100;bbb: don't care;cc: 01
        --T0
        if (opcode(7 downto 5)="100" and opcode(1 downto 0)="01" and tcstate(0)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
          W_R <= '1';
        end if;

        --T1
        if (opcode(7 downto 5)="100" and opcode(1 downto 0)="01" and tcstate(1)='0' ) then
          PC <= PC + 1;
          ABL <= std_logic_vector(PC(7 Downto 0));
          ABH <= std_logic_vector(PC(15 Downto 8));
        end if;

        --Last cycle, write value to memory
        if (opcode(7 downto 5)="100" and opcode(1 downto 0)="01") then
          if ((opcode(4 downto 2)="000" and tcstate(5)='0') --(zero page, X)
            or(opcode(4 downto 2)="001" and tcstate(2)='0') --zero page
            or(opcode(4 downto 2)="011" and tcstate(3)='0') --absolute
            or(opcode(4 downto 2)="100" and ((tcstate(4)='0') or (tcstate(5)='0'))) --(zero page), Y
            or(opcode(4 downto 2)="101" and tcstate(3)='0') --zero page, X
            or(opcode(4 downto 2)="110" and ((tcstate(3)='0') or (tcstate(4)='0'))) --absolute, Y
            or(opcode(4 downto 2)="111" and ((tcstate(3)='0') or (tcstate(4)='0')))) --absolute, X
          then
            DOR <= std_logic_vector(ACC);W_R <= '0';
          end if;
        end if;
        -----------------------=aaa and cc=01 are concerned ends------------------------------=

        -----------------------=cc=10 are concerned ------------------------------------------=
        --STX and LDX address mode special cases
        --1) Address Mode: Zero page, X==> Zero page, Y;Instructions: STX and LDX
        --Timing T2
        if( opcode(4 downto 2)="101" and tcstate(2)='0' and (((opcode(7 downto 5)="100" or
            opcode(7 downto 5)="101") and opcode(1 downto 0)="10"))) then
          PC <= PC;
          ABL <= Databus;
          ABH <= x"00";
          AI <= unsigned(Y);
          BI <= unsigned(Databus);
          Sums <= '1';
        end if;

        --2) Address Mode: absolute X==> absolute Y;Instruction: LDX
        --Timing T2
        if (opcode(4 downto 2)="111" and tcstate(2)='0' and 
          ((opcode(7 downto 5)="101" and opcode(1 downto 0)="10"))) then
          PC    <= PC + 1;
          ABL   <= std_logic_vector(PC(7 Downto 0));
          ABH   <= std_logic_vector(PC(15 Downto 8));
          AI    <= unsigned(Y);
          BI    <= unsigned(Databus);
          Sums  <= '1';
        end if;

        --JB0511 To avoid conflict with Arthy's, avoid hex1>=8 and hex2=A.
        if opcode(1 downto 0)="10" and not(opcode(7)='1' and opcode(3 downto 2)="10") then
          --For all the instructions in this section (cc=10), T0 and T1 has the same behaviors
          --T0
          if (opcode(1 downto 0)="10" and tcstate(0)='0') then
            PC    <= PC + 1;
            ABL   <= std_logic_vector(PC(7 Downto 0));
            ABH   <= std_logic_vector(PC(15 Downto 8));
            W_R   <= '1';

            --LDX needs one more operation
            if opcode(7 downto 5)="101" then
              X <= unsigned(Databus);
            end if;
          end if;

          --T1
          if (opcode(1 downto 0)="10" and tcstate(1)='0') then
            PC <= PC + 1;
            ABL <= std_logic_vector(PC(7 Downto 0));
            ABH <= std_logic_vector(PC(15 Downto 8));

            --LDX affects the flags
            if opcode(7 downto 5)="101" then
              if X(7)='1' then
                P(7) <= '1';
              else
                P(7) <= '0';
              end if;

              if X=x"00" then
                P(1) <= '1';
              else
                P(1) <= '0';
              end if;
            end if;
          end if;

          --Instruction: ASL; aaa: 000; bbb: don't care; cc: 10
          --SD1
          if (opcode(7 downto 5)="000" and SD1='1') then
            PC      <= PC;
            ABH     <= ABH;
            ABL     <= ABL;
            AI      <= unsigned(Databus); --JB0511 correct? Why is W_R '0' while Databus=>DOR?
            BI      <= unsigned(Databus);
            DOR     <= Databus;
            SUMS    <= '1';
            W_R     <= '0';
            I_ADDC  <= '0';
          end if;

          --Instruction: ROL; aaa: 001; bbb: don't care; cc: 10
          --SD1
          if (opcode(7 downto 5)="001" and SD1='1') then
            PC      <= PC;
            ABH     <= ABH;
            ABL     <= ABL;
            AI      <= unsigned(Databus);
            BI      <= unsigned(Databus);
            Sums    <= '1';
            I_ADDC  <= P(0);
            DOR     <= Databus;
            W_R     <= '0';
          end if;

          --Instruction: LSR; aaa: 010; bbb: don't care; cc: 10
          --SD1
          if (opcode(7 downto 5)="010" and SD1='1') then
            PC <= PC;
            ABH <= ABH;
            ABL <= ABL;
            BI <= unsigned(Databus);
            AI <= x"00";
            DOR <= std_logic_vector(ADD);
            SUMS <= '0';
            SRS <= '1';
            W_R <= '0';
            --ADD(7) <= '0';
          end if;

          --SD2
          if (opcode(7 downto 5)="010" and SD2='1') then
            PC <= PC;
            ABH <= ABH;
            ABL <= ABL;
            DOR <= std_logic_vector(ADD);
            W_R <= '0';
            SRS <= '0';

            if ADD=x"00" then
              P(1) <= '1';
            else
              P(1) <= '0';
            end if;

            if ACR='1' then
              P(0) <= '1';
            else
              P(0) <= '0';
            end if;
          end if;

          --Instruction: ROR;aaa: 011;bbb: don't care;cc: 10
          --SD1
          if (opcode(7 downto 5)="011" and SD1='1') then
            PC <= PC;
            ABH <= ABH;
            ABL <= ABL;
            BI <= unsigned(Databus);
            AI <= x"00";
            DOR <= Databus;
            SRS <= '1';
            W_R <= '0';
            SUMS <= '0';
            --ADD(7) <= P(0);
          end if;

          --Instruction ASL or ROL or ROR
          --SD2
          if ((opcode(7 downto 5)="011" or opcode(7 downto 5)="000" or opcode(7 downto 5)="001") and SD2='1') then
            PC <= PC;
            ABH <= ABH;
            ABL <= ABL;
            DOR <= std_logic_vector(ADD);
            W_R <= '0';
            SRS <= '0';
            SUMS <= '0';

            if ADD(7)='1' then
              P(7) <= '1';
            else
              P(7) <= '0';
            end if;

            if ADD=x"00" then
              P(1) <= '1';
            else
              P(1) <= '0';
            end if;

            if ACR='1' then
              P(0) <= '1';
            else
              P(0) <= '0';
            end if;
          end if;

          --Instruction: INC;aaa: 111;bbb: don't care;cc: 10
          --SD1
          if (opcode(7 downto 5)="111" and SD1='1') then
            PC <= PC;
            ABH <= ABH;
            ABL <= ABL;
            BI <= unsigned(Databus);
            AI <= x"00";
            I_ADDC <= '1';
            SUMS <= '1';
            DOR <= Databus;
            W_R <= '0';
          end if;

          --SD2
          if (opcode(7 downto 5)="111" and SD2='1') then
            PC <= PC;
            ABH <= ABH;
            ABL <= ABL;
            DOR <= std_logic_vector(ADD);
            W_R <= '0';
            I_ADDC <= '0';
            SUMS <= '0';

            if ADD(7)='1' then
              P(7) <= '1';
            else
              P(7) <= '0';
            end if;

            if ADD=x"00" then
              P(1) <= '1';
            else
              P(1) <= '0';
            end if;
          end if;


          --Instruction: DEC;aaa: 110;bbb: don't care;cc: 10
          --SD1
          if (opcode(7 downto 5)="110" and SD1='1') then
            PC <= PC;
            ABH <= ABH;
            ABL <= ABL;
            BI <= unsigned(Databus);
            AI <= x"ff";
            I_ADDC <= '0';
            DOR <= Databus;
            W_R<='0'; --JB0510 W_R=0 signal should happen at the following cycle, not when DOR is loaded??
            SUMS <= '1';
          end if;

          --SD2
          if (opcode(7 downto 5)="110" and SD2='1') then
            PC <= PC;
            ABH <= ABH;
            ABL <= ABL;
            DOR <= std_logic_vector(ADD);
            W_R<='0'; --JB0510 W_R=0 signal should happen at the following cycle, not when DOR is loaded??
            I_ADDC <= '0';
            SUMS <= '0';

            if ADD(7)='1' then
              P(7) <= '1';
            else
              P(7) <= '0';
            end if;

            if ADD=x"00" then
              P(1) <= '1';
            else
              P(1) <= '0';
            end if;
          end if;

          --Instruction: STX;aaa: 100;bbb: don't care;cc: 10
          --Last cycle, write value to memory
          if (opcode(7 downto 5)="100") then
            if  ((opcode(4 downto 2)="001" and tcstate(2)='0')   -- Zero page
               or(opcode(4 downto 2)="011" and tcstate(3)='0')   -- Absolute
               or(opcode(4 downto 2)="101" and tcstate(3)='0')) -- Zero page, Y
            then
              DOR<=std_logic_vector(X);
              W_R<='0'; --JB0510 W_R=0 signal should happen at the following cycle, not when DOR is loaded??
            end if;
          end if;


          --Address mode: accumulator cc:10 --JB0511 this lies inside not(hex1>=8 and hex2=A) to distinguish from Arthy's.
          if opcode(4 downto 0)="01010" then

            --Instruction: ASL aaa=000
            --T2+T0
            if (opcode(7 downto 5)="000" and tcstate="111010") then
              PC <= PC;
              ABL <= ABL;
              ABH <= ABH;
              AI <= ACC;
              BI <= ACC;
              I_ADDC <= '0';
              SUMS <= '1';
            end if;

            --Instruction: ROL aaa=001
            --T2+T0
            if (opcode(7 downto 5)="001" and tcstate="111010") then
              PC <= PC;
              ABL <= ABL;
              ABH <= ABH;
              AI <= ACC;
              BI <= ACC;
              I_ADDC <= P(0);
              SUMS <= '1';
            end if;

            --Instruction: LSR or ROR aaa=010 or 011
            --T2+T0
            if ((opcode(7 downto 5)="010" or opcode(7 downto 5)="011") and tcstate="111010") then
              PC <= PC;
              ABL <= ABL;
              ABH <= ABH;
              BI <= ACC;
              AI <= x"00";
              SUMS <= '0';
              SRS <= '1';
            end if;

            --Instruction: ASL or ROL or LSR or ROR
            --T1
            if tcstate(1)='0' then
              PC <= PC + 1;
              ABL <= std_logic_vector(PC(7 Downto 0));
              ABH <= std_logic_vector(PC(15 Downto 8));
              ACC <= ADD;
              SUMS <= '0';
              SRS <= '0';

              if ADD(7)='1' then
                P(7) <= '1';
              else
                P(7) <= '0';
              end if;

              if ADD=x"00" then
                P(1) <= '1';
              else
                P(1) <= '0';
              end if;

              if ACR='1' then
                P(0) <= '1';
              else
                P(0) <= '0';
              end if;
            end if;
         end if; -- END JB0511 To avoid conflict with Arthy's, avoid hex1>=8 and hex2=A.

      -- INCONSISTENT END IF: - AE
      end if;  -- END rising_edge(clk)?

        -----------------------=cc=10 AND aaa=0xx are concerned ends------------------------------------------=

        ---------------------------------------------------------------------------------------------
        ---------------------------------- Yu's code ends here   ------------------------------------
        ---------------------------------------------------------------------------------------------


        ---------------------------------------------------------------------------------------------
        -------------------------------JAEBIN's code starts here-------------------------------------
        ---------------------------------------------------------------------------------------------

        --cc=00
        if (opcode(1 downto 0)="00") then

          --------------------------------branch: xxy10000-----------------------------------------------
          if (opcode(4 downto 2)="100") then  --bbb=100 does not overlab with anything else.
            --T2
            if (tcstate(2)='0') then
              PC  <= PC + 1;
              ABL <= std_logic_vector(PC(7 Downto 0));
              ABH <= std_logic_vector(PC(15 Downto 8));
              BI  <= unsigned(Databus);
              AI  <= PC(7 Downto 0);
              Sums <= '1';

              -- xx=00. N flag. P(7)
              if opcode(7 downto 6)="00" then
                if P(7)=opcode(5) then
                  BRC<='1';
                elsif not(P(7)=opcode(5)) then
                  BRC<='0';
                end if;
              end if;

              -- xx=01. V(O) flag. P(6)
              if opcode(7 downto 6)="00" then
                if P(6)=opcode(5) then
                  BRC<='1';
                elsif not(P(6)=opcode(5)) then
                  BRC<='0';
                end if;
              end if;

              -- xx=10. C flag. P(0)
              if opcode(7 downto 6)="00" then
                if P(0)=opcode(5) then
                  BRC<='1';
                elsif not(P(0)=opcode(5)) then
                  BRC<='0';
                end if;
              end if;

              -- xx=11. Z flag. P(1)
              if opcode(7 downto 6)="00" then
                if P(1)=opcode(5) then
                  BRC<='1';
                elsif not(P(1)=opcode(5)) then
                  BRC<='0';
                end if;
              end if;
            end if;

            --T3
            if (tcstate(3)='0') then
              ABL <= std_logic_vector(ADD);
              PC(7 downto 0) <= ADD+1;
              Sums<='0';
            end if;

            --T0
            if (tcstate(0)='0') then
              PC(15 downto 8) <= PC(15 downto 8)+1;
              ABH <= std_logic_vector(PC(15 downto 8)+1);
            end if;

            ---------------------------branch done-----------------------------------------


          -------------------------interrupts: 0xx00000---------------------------------------------
          --four total, JSR, RTS, BRK, RTI.
          elsif (opcode(4 downto 2)="000" and opcode(7)='0') then


            --1/4. JSR abs. hex:20
            if (opcode(6 downto 5)="01") then

              --T2
              if (tcstate(2)='0') then
                S    <= unsigned(Databus);
                ABL  <= std_logic_vector(S);
                ABH  <= x"01";
                BI   <= S;
                AI   <= x"00";
                Sums <= '1';
              end if;

              --T3
              if (tcstate(3)='0') then
                ABL  <= std_logic_vector(ADD);
                ABH  <= x"01";
                DOR  <= std_logic_vector(PC(15 Downto 8));
                BI   <= ADD;
                AI   <= x"ff";
                Sums <= '1';
              end if;

              --T4
              if (tcstate(4)='0') then
                --Databus <= DOR;
                W_R  <= '0';
                ABL  <= std_logic_vector(ADD);
                ABH  <= x"01";
                DOR  <= std_logic_vector(PC(7 Downto 0));
                BI   <= ADD;
                AI   <= x"ff";
                Sums <= '1';
              end if;

              --T5
              if (tcstate(5)='0') then
                --Databus <= DOR;
                W_R  <= '0';
                PC   <= PC + 1;
                ABL  <= std_logic_vector(PC(7 Downto 0));
                ABH  <= std_logic_vector(PC(15 Downto 8));
                BI   <= ADD;
                AI   <= x"00";
                Sums <= '1';
              end if;

              --T0
              if (tcstate(0)='0') then
                W_R  <='1';
                ABL  <= std_logic_vector(S);
                ABH  <= Databus;
                PC   <= (unsigned(Databus) & S) + 1;  ----------------JB (+1 correct?????)
                S    <= ADD;
                SUMS <='0';
              end if;

              --T1
              if (tcstate(1)='0') then
                PC   <= PC + 1;
                ABL  <= std_logic_vector(PC(7 Downto 0));
                ABH  <= std_logic_vector(PC(15 Downto 8));
                SUMS <='0';
              end if;
            end if;

            ----2/4. RTS. hex:60
            if (opcode(6 downto 5)="11") then

              --T2
              if (tcstate(2)='0') then
                ABL <= std_logic_vector(S);
                ABH <= x"01";
                BI <= S;
                AI <= x"00";
                I_ADDC <= '1';
                Sums <= '1';
              end if;

              --T3
              if (tcstate(3)='0') then
                ABL <= std_logic_vector(ADD);
                ABH <= x"01";
                BI <= ADD;
                AI <= x"00";
                I_ADDC <= '1';
                Sums <= '1';
              end if;

              --T4
              if (tcstate(4)='0') then
                ABL <= std_logic_vector(ADD);
                ABH <= x"01";
                S <= ADD;
              Sums<='0';
              end if;

              --T5
              if (tcstate(5)='0') then
                ABL <= std_logic_vector(PC(7 downto 0));
                ABH <= Databus;
                PC  <= (unsigned(Databus) & PC(7 downto 0))+1; ----------------JB (+1 correct?????)
              end if;

              --T0
              if (tcstate(0)='0') then
                PC  <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;

              --T1
              if (tcstate(1)='0') then
                PC    <= PC + 1;
                ABL   <= std_logic_vector(PC(7 Downto 0));
                ABH   <= std_logic_vector(PC(15 Downto 8));
                Sums  <='0';
              end if;
            end if;


            ----3/4. BRK. hex:00
            if (opcode(6 downto 5)="00") then

              --T2
              if (tcstate(2)='0') then
                DOR   <= std_logic_vector(PC(15 downto 8));
                ABL   <= std_logic_vector(S);
                ABH   <= x"01";
                BI    <= S;
                AI    <= x"ff";
                Sums  <= '1';
              end if;

              --T3
              if (tcstate(3)='0') then
                --Databus <= DOR;
                W_R   <= '0';
                DOR   <= std_logic_vector(PC(7 Downto 0));
                ABL   <= std_logic_vector(ADD);
                ABH   <= x"01";
                BI    <= ADD;
                AI    <= x"ff";
                Sums  <= '1';
              end if;

              --T4
              if (tcstate(4)='0') then
                --Databus <= DOR;
                W_R <= '0';
                DOR <= std_logic_vector(P);
                ABL <= std_logic_vector(ADD);
                ABH <= x"01";
                BI <= ADD;
                AI <= x"ff";
                Sums <= '1';
              end if;

              --T5
              if (tcstate(5)='0') then
                --Databus <= DOR;
                W_R <= '0';
                PC <= PC + 1;
                ABL <= x"fe";
                ABH <= x"ff";
                S <= ADD;
                Sums<='0';
              end if;

              -- EMPTY CYCLE!!!!!!!!! JB ('T6') ***********
              if (VEC1='1') then
                W_R<='1';
                PC(7 downto 0) <= unsigned(Databus);
                ABL <= x"ff";
                ABH <= x"ff";
                Sums<='0';
              end if;

              --T0
              if (tcstate(0)='0') then
                ABL <= std_logic_vector(PC(7 downto 0));
                ABH <= Databus;
                PC <= (unsigned(Databus) & PC(7 downto 0))+1; ----- JB (+1 correct?????)
              end if;

              --T1
              if (tcstate(1)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;
            end if;


            ----4/4. RTI. hex:40
            if (opcode(6 downto 5)="10") then

              --T2
              if (tcstate(2)='0') then
                ABL <= std_logic_vector(S);
                ABH <= x"01";
                BI <= S;
                AI <= x"00";
                I_ADDC <= '1';
                Sums <= '1';
              end if;

              --T3
              if (tcstate(3)='0') then
                ABL <= std_logic_vector(ADD);
                ABH <= x"01";
                BI <= ADD;
                AI <= x"00";
                I_ADDC <= '1';
                Sums <= '1';
              end if;

              --T4
              if (tcstate(4)='0') then
                P <= unsigned(Databus);
                ABL <= std_logic_vector(ADD);
                ABH <= x"01";
                BI <= ADD;
                AI <= x"00";
                I_ADDC <= '1';
                Sums <= '1';
              end if;

              --T5
              if (tcstate(5)='0') then
                PC(7 downto 0) <= unsigned(Databus);
                ABL <= std_logic_vector(ADD);
                ABH <= x"01";
                S <= ADD;
              Sums<='0';
              end if;

              --T0
              if (tcstate(0)='0') then
                ABL <= std_logic_vector(PC(7 downto 0));
                ABH <= Databus;
                PC <= (unsigned(Databus) & PC(7 downto 0))+1; ----------------JB (+1 correct?????)
              end if;

              --T1
              if (tcstate(1)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;
            end if;


          ------------------------the rest of cc=00, excluding branch and interrupt--------------------
          --no overlap with Arthy's, because Arthy's only have bbb=010 and bbb=110.
          else

            --1.bbb=000 AND aaa=1xx. immediate.
            if (opcode(4 downto 2)="000") then
              --T1
              if (tcstate(1)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;
            end if;

            --2.bbb=001. zeropage. common to all aaa within cc=00
            if (opcode(4 downto 2)="001") then
              --T2
              if (tcstate(2)='0') then
                ABL <= Databus;
                ABH <= x"00";
                Sums<='0';
              end if;

              --both T0 and T1
              if (tcstate(0)='0'or tcstate(1)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;
            end if;

            ---3.bbb=011. absolute. exceptions to JMP ABS(aaa=010) and JMP IND(aaa=011)
            ---exception 1/2: JMP ABS. bbb=011, aaa=010
            if (opcode(4 downto 2)="011" and opcode(7 downto 5)="010") then

              --T2
              if (tcstate(2)='0') then
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                PC(7 Downto 0) <= unsigned(Databus);
                Sums<='0';
              end if;

              --T0
              if (tcstate(0)='0') then
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= Databus;
                PC <= (unsigned(Databus) & PC(7 downto 0))+1; --  JB (+1 correct?????)
              end if;

              --T1
              if (tcstate(1)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;
            end if;

            ---exception 2/2: JMP IND. bbb=011, aaa=011
            if (opcode(4 downto 2)="011" and opcode(7 downto 5)="011") then
              --both T2 and T4
              if (tcstate(2)='0' or tcstate(4)='0') then
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                PC(7 Downto 0) <= unsigned(Databus);
                Sums<='0';
              end if;

              --both T3 and T0
              if (tcstate(3)='0' and tcstate(0)='0') then
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= Databus;
                PC <= (unsigned(Databus) & PC(7 downto 0))+1; --  JB (+1 correct?????)
              end if;

              --T1
              if (tcstate(1)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
              end if;
            end if;

            ---the rest of bbb=011 absolute.
            if (opcode(4 downto 2)="011" and not(opcode(7 downto 5)="010") and not(opcode(7 downto 5)="011")) then

              --T2
              if (tcstate(2)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                BI <= unsigned(Databus);
                AI <= x"00";
                Sums <= '1';
              end if;

              --T3
              if (tcstate(3)='0') then
                ABH <= Databus;
                ABL <= std_logic_vector(ADD);
                Sums<='0';
              end if;

              --T0
              if (tcstate(0)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;

              --T1
              if (tcstate(1)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;
            end if;


            --- 4.bbb=101. zeropage,X. common to all aaa within cc=00
            if (opcode(4 downto 2)="101") then

              --T2
              if (tcstate(2)='0') then
                BI <= unsigned(Databus);
                AI <= unsigned(X);
                Sums <= '1';
              end if;

              --T3
              if (tcstate(3)='0') then
                ABL <= std_logic_vector(ADD);
                ABH <= x"00";
              Sums<='0';
              end if;

              --T0
              if (tcstate(0)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;

              --T1
              if (tcstate(1)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;
            end if;


            --- 5.bbb=111. absolute,X. common to all aaa within cc=00
            if (opcode(4 downto 2)="111") then

              --T2
              if (tcstate(2)='0') then
                PC   <= PC + 1;
                ABL  <= std_logic_vector(PC(7 Downto 0));
                ABH  <= std_logic_vector(PC(15 Downto 8));
                BI   <= unsigned(Databus);
                AI   <= unsigned(X);
                Sums <= '1';

                if opcode(7 downto 5)="100" then
                  Mask_shortcut <= '1'; --Yuchen
                end if;
              end if;

              --T3
              if (tcstate(3)='0') then
                ABH <= Databus;
                ABL <= std_logic_vector(ADD);
                BI <= unsigned(Databus);
                I_ADDC <= ACR;
                Mask_shortcut <= '0'; --Yuchen
                --transfer carry out result to carry in, for page crossing
                --**********(JB) increase timing signal from 4 cycles to 5 cycles (add cycle T4)
              end if;

              --T4
              if (tcstate(4)='0') then
                ABH <= std_logic_vector(ADD);
                Sums<='0';
              end if;

              --T0
              if (tcstate(0)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
                Sums<='0';
              end if;

              --T1
              if (tcstate(1)='0') then
                PC <= PC + 1;
                ABL <= std_logic_vector(PC(7 Downto 0));
                ABH <= std_logic_vector(PC(15 Downto 8));
              end if;
            end if;

            ----------------------------bbb taken care of. now aaa.---------------------------------

            ---1.aaa=101. LDY. common to all bbb within cc=00
            if (opcode(7 downto 5)="101") then

              --T0
              if (tcstate(0)='0') then
                Y <= unsigned(Databus);
                BI <= unsigned(Databus);
                AI <= x"00";
                Sums <= '1';
              end if;

              --T1
              if (tcstate(1)='0') then
                P(7) <= ADD(7); --JB set N. P is the processor status register (1 byte)

                if ADD=x"00" then
                  P(1) <= '1';
                else
                  P(1) <= '0';
                end if;
              end if;
            end if;


            ---2.aaa=111. CPX. common to all bbb within cc=00
            if (opcode(7 downto 5)="111") then

              --T0
              if (tcstate(0)='0') then
                BI<=unsigned(not(Databus)); --JB0511 need to invert!!!!!!!!!!!!
                AI <= unsigned(X);
                Sums <= '1';
              end if;

              --T1
              if (tcstate(1)='0') then
                P(7) <= ADD(7); --JB set N. P is the processor status register (1 byte)

                if ADD=x"00" then
                  P(1) <= '1';
                else
                  P(1) <= '0';
                end if;
                P(0) <= ACR;
                Sums<='0';
              end if;

            end if;


            ---3.aaa=110. CPY. common to all bbb within cc=00
            if (opcode(7 downto 5)="110") then

              --T0
              if (tcstate(0)='0') then
                BI <=unsigned(not(Databus)); --JB0511 need to invert!!!!!!!!!!!!
                AI <= unsigned(Y);
                Sums <= '1';
              end if;

              --T1
              if (tcstate(1)='0') then
                P(7) <= ADD(7); --JB set N. P is the processor status register (1 byte)

                if ADD=x"00" then
                  P(1) <= '1';
                else
                  P(1) <= '0';
                end if;
                P(0) <= ACR;
                Sums<='0';
              end if;
            end if;

            ---4.aaa=001. BIT. common to all bbb within cc=00
            if (opcode(7 downto 5)="001") then

              --T0
              if (tcstate(0)='0') then
                BI <= unsigned(Databus);
                AI <= ACC;
                Sums <= '1';
              end if;

              --T1
              if (tcstate(1)='0') then
                P(7) <= ADD(7); --JB set N. P is the processor status register (1 byte)

                if ADD=x"00" then
                  P(1) <= '1';
                else
                  P(1) <= '0';
                end if;
                P(0) <= ACR;
                Sums<='0';
              end if;
            end if;

            ---5.aaa=100. STY. common to all bbb within cc=00
            if (opcode(7 downto 5)="100") then

              --both T2 and T3
              if (tcstate(2)='0' or tcstate(3)='0') then    --JB Y->DOR happenes at T2 in zeropage, and at T3 in the rest.
                DOR <= std_logic_vector(Y);
              end if;

              --T0
              if (tcstate(0)='0') then
                --Databus <= DOR;
                W_R <= '0';
              end if;

              --T1
              if (tcstate(0)='0') then
                Sums<='0';
                W_R<='1';
              end if;
            end if;

          ----------------------------aaa taken care of. now exceptions.---------------------------------
          end if; -- END ELSE (--bbb=100 does not overlab with anything else.)

        end if; -- END IF (opcode(1 downto 0)="00") then (Necessary?)

        ----------------------------------------------------------------------------------
        -----------------------------JAEBIN's code ends here------------------------------
        ----------------------------------------------------------------------------------



        -----------------------------------------------------------------------------------
        -----------------------------ARTHY's code starts here------------------------------
        -----------------------------------------------------------------------------------

        -------------------------- BEGIN SINGLE BYTE INSTRUCTIONS --------------------------
        --NOP
        if(opcode(7 downto 0) = x"EA") then

          --if(tcstate(2) = '0') then --JB0511 deleted "and tcstate(0) = '0'"
            --PC <= PC; -- this also not required
          --end if;

          if (tcstate(1) = '0') then
            PC  <= PC + 1;
            ABL <= std_logic_vector(PC(7 Downto 0));
            ABH <= std_logic_vector(PC(15 Downto 8));
          end if;
        end if; --NOP ends.

        --PHA/PLA/PHP/PLP
        if( (opcode(7 downto 0) = x"48") or (opcode(7 downto 0) = x"68") or
          (opcode(7 downto 0) = x"08") or (opcode(7 downto 0) = x"28")) then --PHA/PLA/PHP/PLP

          --T2
          if(tcstate(2)='0') then
            PC  <= PC - 1; --JB0511 PC-1?????
            ABL <=std_logic_vector(S(7 downto 0) );
            ABH <= x"01";
            BI  <= S;
            SUMS <='1';

            -- Push PHA / PHP
            if(opcode(5) = '0') then --subtract.
              AI  <= x"FF";
              W_R <= '0';
              if(opcode(6) = '1') then
                -- PHA put the acc onto databus
                DOR <= std_logic_vector(ACC);
              else
                -- (opcode(6) == '0') then
                -- PHP put the status reg unto db
                DOR <= std_logic_vector(P);
              end if;

            -- Pull PLA / PLP
            else --sum.
              AI <= x"01";
            end if;
          end if;

          --T3
          if(tcstate(3) = '0') then -- assume only PLA and PLP get here
            W_R <= '1'; -- back to read
            PC<=PC;
            S<=ADD;
            SUMS <= '0';
            ABL<=std_logic_vector(ADD);
            ABH<=x"01";
          end if;

          --T0
          if (tcstate(0)= '0') then
            ABL <= std_logic_vector(PC(7 Downto 0));
            ABH <= std_logic_vector(PC(15 Downto 8));
            PC <= PC + 1;

            --PLA/PLP
            if(opcode(5) = '1') then

              --PLA
              if(opcode(6) = '1') then
                ACC <= unsigned(Databus);

                if (ACC = 0) then
                  P(1) <= '1'; --set zero flag
                end if;
                P(7) <= ACC(7); -- set negative flag
               --PLP
              elsif(opcode(6) = '0') then
                P <= unsigned(Databus);
              end if;

            --PHA/PHP
            elsif(opcode(5) = '0') then
              --SUBS <= '1'; --JB0511 Subtracts WHAT? Nothing goes in to AI or BI.
              S <=  ADD;
              W_R <= '1'; -- read
            end if;
          end if;


          --T1
          if (tcstate(1)= '0') then -- PHA/PHP/PLA/PLP
            ABL<=std_logic_vector(PC(7 Downto 0));
            ABH<=std_logic_vector(PC(15 Downto 8));
            PC <= PC + 1;
          end if;

        end if; --PHA/PLA/PHP/PLP end.


        -- INX, INY, DEX, DEY
        --1/4 DEX: CA
        if opcode (7 downto 0) = x"CA" then

          --T2+T0
          if (tcstate(2) = '0') then
            SUMS <= '1';
            BI <= X; AI <= x"ff";
          end if;

          --T1
          if (tcstate(1) = '0') then
            ABL<=std_logic_vector(PC(7 Downto 0));
            ABH<=std_logic_vector(PC(15 Downto 8));
            PC <= PC + 1;

            if (ADD = 0) then
              P(1) <= '1'; --Z flag
            end if;

            P(7) <= ADD(7); --N flag
            X <= ADD;
            SUMS <= '0';
          end if;
        end if;


        --2/4 INX: E8
        if opcode (7 downto 0) = x"E8" then

          --T2+T0
          if (tcstate(2) = '0') then
            SUMS <= '1';
            BI <= X; AI <= x"01";
          end if;

          --T1
          if (tcstate(1) = '0') then
            ABL   <= std_logic_vector(PC(7 Downto 0));
            ABH   <= std_logic_vector(PC(15 Downto 8));
            PC    <= PC + 1;

            if (ADD = 0) then
              P(1) <= '1'; --Z flag
            end if;

            P(7)  <= ADD(7); --N flag
            X     <= ADD;
            SUMS  <= '0';
          end if;
        end if;


        --3/4 DEY: 88
        if opcode (7 downto 0) = x"88" then

          --T2+T0
          if (tcstate(2) = '0') then
            SUMS  <= '1';
            BI    <= Y; 
            AI    <= x"ff";
          end if;

          --T1
          if (tcstate(1) = '0') then
            ABL <= std_logic_vector(PC(7 Downto 0));
            ABH <= std_logic_vector(PC(15 Downto 8));
            PC  <= PC + 1;

            if (ADD = 0) then
              P(1) <= '1';   --Z flag
            end if;

            P(7) <= ADD(7);   --N flag
            Y <= ADD;
            SUMS <= '0';
          end if;
        end if;


        --4/4 INY: C8
        if opcode (7 downto 0) = x"88" then
          --T2+T0

          if (tcstate(2) = '0') then
            SUMS <= '1';
            BI <= Y; AI <= x"01";
          end if;

          --T1
          if (tcstate(1) = '0') then
            ABL<=std_logic_vector(PC(7 Downto 0));
            ABH<=std_logic_vector(PC(15 Downto 8));
            PC <= PC + 1;

            if (ADD = 0) then
              P(1) <= '1'; --Z flag
            end if;

            P(7) <= ADD(7); --N flag
            Y <= ADD;
            SUMS <= '0';
          end if;
        end if;

        -- INX, INY, DEX, DEY ends.

        --These four opcodes implemented more efficiently above.
        --    -- INX, INY, DEX, DEY
        --    if ((opcode (7 downto 0) = x"CA") or (opcode (7 downto 0) = x"E8") or
        --        (opcode (7 downto 0) = x"88") or(opcode (7 downto 0) = x"C8")) then
        --
        --      --T2 + T0
        --      if (tcstate(2) = '0') then --JB0511 deleted "and tcstate(0) = '0'"
        --
        --        --PC <= PC; -- NOT REQD, PC will stay PC
        --        --BI <= x"01";
        --        SUMS <= '1';
        --
        --        CASE (opcode (7 downto 0)) is
        --          when x"ca" => BI <= X; AI <= x"ff";
        --          when x"e8" => BI <= X; AI <= x"01";
        --          when x"88" => BI <= Y; AI <= x"ff";
        --          when x"c8" => BI <= Y; AI <= x"01";
        --          when others => null;-- donothing
        --        END CASE;
        --
        --      elsif (tcstate(1) = '0') then -- T1
        --        ABL<=std_logic_vector(PC(7 Downto 0));
        --        ABH<=std_logic_vector(PC(15 Downto 8));
        --        PC <= PC + 1;
        --        if (ADD = 0) then
        --          P(1) <= '1'; --Z flag
        --        end if;
        --        P(7) <= ADD(7); --N flag
        --
        --        case(opcode(7 downto 0)) is
        --          when x"ca" => X <= ADD;
        --          when x"e8" => X <= ADD;
        --          when x"88" => Y <= ADD;
        --          when x"c8" => Y <= ADD;
        --          when others => null;
        --        end case;
        --        --SUBS <= '0';
        --        SUMS <= '0';
        --      end if;
        --    end if; -- INX, INY, DEX, DEY end.


        --  Register instructions
        if opcode(4 downto 2) = "110" and opcode(0) = '0' then

          --T2 + T0
          if tcstate(2) = '0' then --JB0511 deleted "and tcstate(0) = '0'"
            --PC <= PC;
            CASE opcode(7 downto 5)IS
              when "000" => P(0) <= '0'; -- CLC
              when "001" => P(0) <= '1'; -- SEC
              when "010" => P(2) <= '0'; ---CLI
              when "011" => P(2) <= '1'; -- SEI
              when "101" => P(6) <= '0'; -- CLV
              when "110" => P(3) <= '0'; -- CLD
              when "111" => P(3) <= '1'; -- SED
              when others => null;
            END CASE;
          end if;

          --T1
          if (tcstate(1) = '0') then
            ABL <= std_logic_vector(PC(7 Downto 0));
            ABH <= std_logic_vector(PC(15 Downto 8));
            PC  <= PC + 1;
          end if;

        end if; --Register instructions end.

        --  These seven opcodes implemented more efficiently above.
        --    if ((opcode(3 downto 0) = "1000") or (opcode(3 downto 0) = "1010") ) then
        --      if ((opcode(7 downto 4) = "0001") or (opcode(7 downto 4) = "0011") or
        --        (opcode(7 downto 4) = "0101") or (opcode(7 downto 4) = "0111")  or
        --        (opcode(7 downto 4) = "1101") or (opcode(7 downto 4) = "1111") or
        --        (opcode(7 downto 4) = "1011")) then
        --
        --        --T2 + T0
        --        if tcstate(2) = '0' then --JB0511 deleted "and tcstate(0) = '0'"
        --          --PC <= PC;
        --          CASE opcode(7 downto 5)IS
        --            when "000" => P(0) <= '0'; --CLC
        --            when "001" => P(0) <= '1'; -- SEC
        --            when "010" => P(2) <= '0'; ---CLI
        --            when "011" => P(2) <= '1'; -- SEI
        --            when "101" => P(6) <= '0'; -- CLV
        --            when "110" => P(3) <= '0'; -- CLD
        --            when "111" => P(3) <= '1'; --SED
        --            when others => null;
        --          END CASE;
        --        -- T1
        --        elsif (tcstate(1) = '0') then
        --          ABL<=std_logic_vector(PC(7 Downto 0));
        --          ABH<=std_logic_vector(PC(15 Downto 8));
        --          PC <= PC + 1;
        --        end if;
        --      end if;
        --    end if;

        -- Transfer instructions
        if ((opcode (7 downto 0) = x"8A") or (opcode (7 downto 0) = x"9A") or
            (opcode (7 downto 0) = x"AA") or (opcode (7 downto 0) = x"BA") or
            (opcode (7 downto 0) = x"98") or (opcode (7 downto 0) = x"A8")) then

          --T2 + T0
          if(tcstate(2) = '0') then --JB0511 removed "and tcstate(0)='0'"

            --PC <= PC;
            if((opcode (7 downto 0)) = x"8A") then -- TXA
              ACC <= X;

              if (X = 0) then
                P(1) <= '1';
              end if;
              P(7) <= X(7);
            end if;

            if ((opcode (7 downto 0)) = x"9A") then --TXS
              S <= X;
            end if;

            if ((opcode (7 downto 0)) = x"AA" ) then -- TAX
              X <= ACC;

              if (ACC = 0) then
                P(1) <= '1';
              end if;
              P(7) <= ACC(7);
            end if;

            if ((opcode (7 downto 0)) = x"BA") then -- TSX
              X <= S;

              if (S = 0) then
                P(1) <= '1';
              end if;
              P(7) <= S(7);
            end if;

            if ((opcode (7 downto 0)) = x"98") then --TYA
              ACC <= Y;

              if (Y = 0) then
                P(1) <= '1';
              end if;
              P(7) <= Y(7);
            end if;

            if ((opcode (7 downto 0)) = x"A8") then -- TAY
              Y <= ACC; --TAY

              if (ACC = 0) then
                P(1) <= '1';
              end if;
              P(7) <= ACC(7);
            end if;
          end if;

          --T1
          if (tcstate(1) = '0') then
            ABL<=std_logic_vector(PC(7 Downto 0));
            ABH<=std_logic_vector(PC(15 Downto 8));
            PC <= PC + 1;
          end if;
        end if; -- Transfer instructions end.

      ---------------------------------------------------------------------------------------
      -----------------------------Arthy's code ends here------------------------------------
      ---------------------------------------------------------------------------------------

      end if;  --  clk rising edge
    end if;    --  reset
  end process; -- CLOCK

end rtl;