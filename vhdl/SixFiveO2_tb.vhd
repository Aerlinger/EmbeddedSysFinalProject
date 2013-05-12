library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


--------------------------------------------------------------------------
--- SixFiveO2  Test Bench ------------------------------------------------
--------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SixFiveO2_tb is
end SixFiveO2_tb;

architecture tb of SixFiveO2_tb is

  component SixFiveO2 is
    port(
      Databus : in std_logic_vector(7 downto 0);
      Addrbus : out std_logic_vector(15 downto 0);
      DOR     : out std_logic_vector(7 downto 0);
      reset, clk: in std_logic;

      XL, XH, YL, YH, ACCL, ACCH : out std_logic_vector(6 downto 0)
    );
  end component;

  --component memory_asynchronous
  --end memory_asyncronous;

	signal Databus : std_logic_vector(7 downto 0) := x"A9";
  signal Addrbus : std_logic_vector(15 downto 0);
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
