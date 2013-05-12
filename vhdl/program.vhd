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
--
--  PROGRAM MODULE:
--  A simple integration test program inpired by Skilldrick's 6502 tutorial:
--      http://skilldrick.github.io/easy6502/
--    Just loads a few values into the accumulator
--
--
--
------------------------------------------------------------------------------
------------------------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- ROM -------------------------------------------------------------------------

entity ROM is
  generic (
    ADDR_WIDTH :integer := 16
  );

  port(
    Databus : out std_logic_vector(7 downto 0);
    Addrbus : in std_logic_vector(15 downto 0);
    clk : in std_logic;
    read_en : in std_logic
  );
end ROM;

architecture rtl of ROM is
  -- LOCAL SIGNALS

  constant ADDR_SPACE :integer := 2**ADDR_WIDTH;

  type ROM_Array is array (0 to ADDR_SPACE-1)
    of std_logic_vector(7 downto 0);

  -- Rom of the basic program 
  -- Used from: http://skilldrick.github.io/easy6502/
  constant Load_test: ROM_Array := (
    0 => x"A9",  -- Load Accumulator Immediate
    1 => x"01",  -- Immediate value

    2 => x"8D",  -- STA Absolute
    3 => x"00",  -- Last Byte of absolute memory location (Little Endian)
    4 => x"02",  -- First Byte of absolute mem location 

    5 => x"A9",  -- LDA Immediate
    6 => x"05",  -- Immediate value

    7 => x"8D",  -- STA Absolute
    8 => x"01",
    9 => x"02",

    10 => x"A9", -- LDA Immediate
    11 => x"08", -- Immediate Value

    12 => x"8D", -- STA Absolute
    13 => x"02",
    14 => x"02",
    others => x"FF"
  );

  constant tax_test: ROM_Array := (
    0 => x"A9",  -- Load Accumulator Immediate
    1 => x"c0",  -- Immediate value

    2 => x"aa",  -- TAX 
    3 => x"e8",  -- INX

    4 => x"69",  -- ADC (Add teh vlue c4 to the Accumulator)
    5 => x"c4",  -- the value to be added

    6 => x"00",  -- BRK
    others => x"FF"
  );

begin

  process(clk, read_en, Addrbus)
  begin
    if (clk'event and clk='1') then
      if (read_en = '1') then
        Databus <= Load_test(conv_integer(Addrbus));
      else
        Databus <= "ZZZZZZZZ";
      end if;
    end if;
  end process;

end rtl;


-- 6502 Module ----------------------------------------------------------

package SixFiveO2_package is

  constant CLOCK_PERIOD: TIME := 20 ns;

end SixFiveO2_package;


--package body SixFiveO2_package is

--end SixFiveO2_package;

------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity program is
end program;

architecture tb of program is

  component SixFiveO2
  port (
    Databus: in std_logic_vector(7 downto 0);
    Addrbus: out std_logic_vector(15 downto 0);
    clk: in std_logic;
    rdy: in std_logic;
    res: in std_logic;
    irq: in std_logic;
    nmi: in std_logic;
    r_w: out std_logic
  );
  end component;

  component ROM
  port (
    Databus: out std_logic_vector(7 downto 0);
    Addrbus: in std_logic_vector(15 downto 0);
    clk: in std_logic;
    read_en: in std_logic
  );
  end component;
  -- Signals for the ROM are shared by the 6502

  ---------------------------------------------------------------------------
  -- Signals for the 6502 itself:
  ---------------------------------------------------------------------------

  -- External 6502 signals
  signal Databus : std_logic_vector(7 downto 0);
  signal Addrbus : std_logic_vector(15 downto 0) := x"0000";

  signal clk: std_logic;
  signal rdy: std_logic;
  signal res: std_logic;   -- Active low
  signal irq: std_logic;   -- Active low
  signal nmi: std_logic;   -- Active low

  signal r_w: std_logic;   -- Write is Active low

  -- Exposed internal signals:
  signal DOR     : std_logic_vector(7 downto 0);
  signal tcstate : std_logic_vector(5 downto 0);  -- 6 bit mask for timing state (taken as input to decode ROM)

  signal ABL_out: std_logic_vector(7 downto 0);
  signal ABH_out: std_logic_vector(7 downto 0);
  signal X_out: std_logic_vector(7 downto 0);
  signal Y_out: std_logic_vector(7 downto 0);
  signal ACC_out: std_logic_vector(7 downto 0);

  signal SD1: std_logic;
  signal SD2: std_logic;
  signal VEC1: std_logic;
  signal ACR_out: std_logic;

  -- Outputs for 7seg debugging
  signal XL, XH, YL, YH, ACCL, ACCH : std_logic_vector(6 downto 0);

begin

  -- TODO: Make connections for test outputs
  --U_SIXFIVEO2: SixFiveO2 port map
  --(
  --  Databus,
  --  Addrbus,
  --  clk,
  --  rdy,
  --  res,
  --  irq,
  --  nmi,
  --  r_w
  --);

  U_ROM: ROM port map
  (
    Databus,
    Addrbus,
    clk,
    '1'
  );

  process
  begin
    loop
      clk <= '0'; wait for 20 ns;
      clk <= '1'; wait for 20 ns;
    end loop;
  end process;

end tb;

------------------------------------------------------------------------------
