library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity QuasiTopLevel is
port(
		  CLOCK_50 : std_logic;
			HEX2, HEX3, HEX4, HEX5, HEX6, HEX7 -- 7-segment displays
					: out std_logic_vector(6 downto 0);         -- (active low)
			SW : in std_logic;         -- DPDT switches
			SRAM_DQ : inout unsigned(15 downto 0);         -- Data bus 16 Bits
			SRAM_ADDR : out unsigned(17 downto 0);         -- Address bus 18 Bits
			SRAM_UB_N,                                     -- High-byte Data Mask 
			SRAM_LB_N,                                     -- Low-byte Data Mask 
			SRAM_WE_N,                                     -- Write Enable
			SRAM_CE_N,                                     -- Chip Enable
			SRAM_OE_N : out std_logic                      -- Output Enable

);
end QuasiTopLevel;

architecture datapath of QuasiTopLevel is
signal Databus, DOR, ROM_data : std_logic_vector(7 downto 0);
signal Addrbus, ROM_address  : std_logic_vector(15 downto 0);
signal W_R : std_logic;

component SixFiveO2 
port(
		Databus :in std_logic_vector(7 downto 0);
		Addrbus :out std_logic_vector(15 downto 0);
		DOR     : out std_logic_vector(7 downto 0);
      reset, clk   :in std_logic;
		XL, XH, YL, YH, ACCL, ACCH : out std_logic_vector(6 downto 0);
		W_R     : out std_logic);
end component;

component rom is
port(addr  : in std_logic_vector(15 downto 0);
		data : out std_logic_vector(7 downto 0));
end component;

component SRAMCtrl is
port (
		reset, clk, W_R : in  std_logic;
		ROM_data, DOR  : in std_logic_vector(7 downto 0);
		databus    : out std_logic_vector(7 downto 0);
		AddressBus : in std_logic_vector(15 downto 0);
		ROM_address : out std_logic_vector(15 downto 0);
		SRAM_DQ    : inout unsigned(15 downto 0);
		SRAM_ADDR  : out unsigned(17 downto 0);
		SRAM_UB_N,            -- High-byte Data Mask
		SRAM_LB_N,            -- Low-byte Data Mask
		SRAM_WE_N,            -- Write Enable
		SRAM_CE_N,            -- Chip Enable
		SRAM_OE_N : out std_logic  -- Output Enable
);
end component;

begin
 
CPUConnect: SixFiveO2 port map(clk=>CLOCK_50, reset=>SW, W_R=>W_R, XH=>HEX7, XL=>HEX6, YH=>HEX5, YL=>HEX4, ACCH=>HEX3, ACCL=>HEX2,
											Databus=>Databus, DOR=>DOR, Addrbus=>Addrbus);

InstructionROM: Rom port map(addr=>ROM_address, data=>ROM_data);

MemorySRAM: SRAMCtrl port map(reset=>SW, clk=>CLOCK_50, W_R=>W_R, ROM_data=>ROM_data, DOR=>DOR,
										databus=>databus, AddressBus=>Addrbus, ROM_address=>ROM_address, 
										SRAM_DQ=>SRAM_DQ,    
										SRAM_ADDR=>SRAM_ADDR,  
										SRAM_UB_N=>SRAM_UB_N,
										SRAM_LB_N=>SRAM_LB_N,            
										SRAM_WE_N=>SRAM_WE_N,          
										SRAM_CE_N=>SRAM_CE_N,    
										SRAM_OE_N=>SRAM_OE_N);
end datapath;
