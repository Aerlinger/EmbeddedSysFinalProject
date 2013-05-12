library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


package CPU_package is

  -- 1 / 50 MHz clock:
  constant CLOCK_PERIOD: TIME := 20 ns;

  --------------------------------------------------------------------------
  --- INTERNAL AND EXTERMAL VARIABLES  -------------------------------------
  --------------------------------------------------------------------------

  -- The 6502's external interface:
  signal Databus: std_logic_vector(7 downto 0);
  signal Addrbus: std_logic_vector(15 downto 0);
  signal clk: std_logic;
  signal reset: std_logic;
  signal W_R: std_logic;

  -- Exposed 'internals' of the 6402  used for debugging:
  signal tc_state: std_logic_vector(5 downto 0);
  signal DOR: std_logic_vector(7 downto 0);
  signal ACR_out:  std_logic;

  signal ABL_out: std_logic_vector(7 downto 0);
  signal ABH_out: std_logic_vector(7 downto 0);
  signal DOR: std_logic_vector(7 downto 0);
  signal X_out: std_logic_vector(7 downto 0);
  signal Y_out: std_logic_vector(7 downto 0);
  signal ACC_out: std_logic_vector(7 downto 0);

  --signal XL, XH, YL, YH, ACCL, ACCH, : std_logic_vector(6 downto 0);

  --------------------------------------------------------------------------
  --- PROCEDURES  ----------------------------------------------------------
  --------------------------------------------------------------------------

  -- Loads an opcode onto the databus:
  procedure load_opcode (
    signal opcode: out std_logic_vector(7 downto 0)
  );

  procedure validate_output (
    signal Databus: out std_logic_vector(7 downto 0)
  );

end CPU_package;

package body CPU_package is

  procedure load_opcode (
    signal opcode: out std_logic_vector(7 downto 0)
  ) is
  begin
    Databus <= opcode;
    reset <= 0;
  end load_opcode;

  procedure validate_output (
    signal Databus: out std_logic_vector(7 downto 0)
  ) is
  begin

  end validate_output;

end CPU_package;


--------------------------------------------------------------------------
--- Core test bench  -----------------------------------------------------
--------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity CPU_tb is
end CPU_tb;

architecture tb of CPU_tb is

  component SixFiveO2
    port(
      Databus : in std_logic_vector(7 downto 0);
      Addrbus : out std_logic_vector(15 downto 0);
      DOR     : out std_logic_vector(7 downto 0);
      reset, clk: in std_logic;

      XL, XH, YL, YH, ACCL, ACCH : out std_logic_vector(6 downto 0)
    );
  end component;

  --component memory_asynchronous
  --end component;

	signal Databus : std_logic_vector(7 downto 0) := x"A9";
  signal Addrbus : std_logic_vector(7 downto 0);
	signal DOR : std_logic_vector(7 downto 0);

	signal reset  : std_logic  := '1';
	signal clk    : std_logic  := '0';

begin

  U_SixFiveO2: SixFiveO2 port map(
    Databus => Databus,
    Addrbus => Addrbus,
    DOR => DOR,
    reset => reset,
    clk => clk
  );

  process
  begin
    loop
       clk <= '0'; wait for 20 ns;
       clk <= '1'; wait for 20 ns;
    end loop;
  end process;
  
  process
  begin
    wait for 101 ns;
    reset <= '0';
    wait;
  end process;
  
  process  --test the first section cc=01
  begin
    wait for 200 ns;
    
    -- process rising_edge(clk)
    databus<= x"11";  --(LDA) #=11

    wait for 40 ns;
    databus<= x"09";	--ORA #
    wait for 40 ns;
    databus<= x"22";	--#=22
    wait for 40 ns;
    databus<= x"29";  --AND #
    wait for 40 ns;
    databus<= x"77";  --#=77
    wait for 40 ns;
    databus<= x"49";  --EOR #
    wait for 40 ns;
    databus<= x"77";  --#=77
    wait for 40 ns;
    databus<=x"69";	--ADC #
    wait for 40 ns;
    databus<=x"22";	--#=22
    wait for 40 ns;
    databus<=x"E9";		--SBC
    wait for 40 ns;
    databus<=x"22";  --#=22
    wait for 40 ns;
    databus<=x"8D";  --STA absolute
    wait for 40 ns;
    databus<=x"34";	--ADL
    wait for 40 ns;
    databus<=x"12";	--ADH
    wait for 40 ns;		
    databus<=x"05";	--content in ADH+ADL
    wait for 40 ns;
    databus<=x"C9";	--CMP #
    wait for 40 ns;
    databus<=x"43"; 	--# (Equal)
    wait for 40 ns;
    databus<=x"C9";	--CMP #
    wait for 40 ns;
    databus<=x"00"; 	--# (A>M)
    wait for 40 ns;
    databus<=x"54"; 	--# (A<M)
    wait;
  end process;

--SixFiveOTwo: 
--		entity work.SixFiveO2
--		port map (clk=> clk, reset=>reset, databus=>databus);
										
end tb;
