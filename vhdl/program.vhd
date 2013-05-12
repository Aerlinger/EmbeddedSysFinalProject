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
port(
  clk : in std_logic;
  read : in std_logic;
  address : in std_logic(7 downto 0);
  data_out : out std_logic(7 downto 0);
);
end ROM;

architecture tb of ROM is
  -- LOCAL SIGNALS

  type ROM_Array is array (0 to 31)
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
    14 => x"02"7
  );

  constant tax_test: ROM_Array := (
    0 => x"A9",  -- Load Accumulator Immediate
    1 => x"c0",  -- Immediate value

    2 => x"aa",  -- TAX 
    3 => x"e8",  -- INX

    4 => x"69",  -- ADC (Add teh vlue c4 to the Accumulator)
    5 => x"c4",  -- the value to be added

    6 => x"00",  -- BRK
  );

begin

  process(clk, reset, read, address)
  begin
    if (clk'event and clk='1') then
      if (read = '1') then
        data_out <= Load_test(conv_integer(address));
      else
        data_out <= "ZZZZZZZZ";
      end if;
    end if;
  end process;

end tb;


-- 6502 Module ----------------------------------------------------------

package SixFive02_package is

  constant CLOCK_PERIOD: TIME := 20 ns;

end SixFive02_package;


package body SixFive02_package is

end SixFive02_package;

------------------------------------------------------------------------------

entity program is
end program;

architecture tb of program is is
  component ROM is
  end component;

  component SixFive02 is
    Databus => Databus,
    Addrbus  => Addrbus,
    clk => clk,
    rdy => rdy,
    res => res,
    irq => irq,
    nmi => nmi,
    nmi => nmi,
    r_w => r_w
  end component;

  component ROM is
    clk => clk,
    data_out => Databus,
    address => Addrbus,
    read <= '1',
  end component;
  -- Signals for the ROM are shared by the 6502

  ---------------------------------------------------------------------------
  -- Signals for the 6502 itself:
  ---------------------------------------------------------------------------

  -- External 6502 signals
  signal Databus : std_logic_vector(7 downto 0);
  signal Addrbus : std_logic_vector(16 downto 0);

  signal clk: std_logic;
  signal rdy: std_logic;
  signal res: std_logic;   -- Active low
  signal irq: std_logic;   -- Active low
  signal nmi: std_logic;   -- Active low

  r_w: out std_logic;   -- Write is Active low

  -- Exposed internal signals:
  DOR     : out std_logic_vector(7 downto 0);
  tcstate : out std_logic_vector(5 downto 0);  -- 6 bit mask for timing state (taken as input to decode ROM)

  ABL_out: out std_logic_vector(7 downto 0);
  ABH_out: out std_logic_vector(7 downto 0);
  DOR: out std_logic_vector(7 downto 0);
  X_out: out std_logic_vector(7 downto 0);
  Y_out: out std_logic_vector(7 downto 0);
  ACC_out: out std_logic_vector(7 downto 0);

  SD1: out std_logic
  SD2: out std_logic;
  VEC1: out std_logic;
  ACR_out: out std_logic;

  -- Outputs for 7seg debugging
  XL, XH, YL, YH, ACCL, ACCH : out std_logic_vector(6 downto 0)
begin

  -- TODO: Make connections for test outputs
  U_SixFive02: SixFive02 port map(
    Databus => Databus,
    Addrbus => Addrbus,
    DOR => DOR,
    reset => reset,
    clk => clk
  );

  U_ROM: ROM port map
  (
    data_out => Databus,
    Address <= addr_bus;
    clk <= clk;
    enable <= '1';
  );

  process
  begin
    loop
      clk <= '0' wait for 20 ns;
      clk <= '1' wait for 20 ns;
    end loop;
  end process;

end

------------------------------------------------------------------------------
