library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use IEEE.std_logic_1164.all;

package components is

	constant Flag_C 	: integer := 0;
	constant Flag_Z 	: integer := 1;
	constant Flag_I 	: integer := 2;
	constant Flag_D 	: integer := 3;
	constant Flag_B 	: integer := 4;
	constant Flag_1 	: integer := 5;
	constant Flag_V 	: integer := 6;
	constant Flag_N 	: integer := 7;
	
	component mos_6502 is
		-- 32 bits are used
		port(
			-- Data and address for data
			A			: out std_logic_vector(15 downto 0);
			DI		: in std_logic_vector(7 downto 0);
			DO		: out std_logic_vector(7 downto 0);

			reset	: in std_logic;
			clk		: in std_logic;
			ready	: in std_logic;
			IRQ_n	: in std_logic;
			NMI_n	: in std_logic;
			SO_n	: in std_logic;
			R_W_n	: out std_logic;
			Sync	: out std_logic;
			L_Cycle_out : out std_logic_vector(2 downto 0);
			M_Cycle_out : out std_logic_vector(2 downto 0)
		);
	end component;

	component rom is
	port(
		addr: in std_logic_vector(15 downto 0);
		data: out std_logic_vector(7 downto 0)
	);
	end component;
	
	component SRAMCtrl is
	port (
		reset, clk, W_R : in  std_logic;
		ROM_data, DOR  : in std_logic_vector(7 downto 0);
		databus    	: out std_logic_vector(7 downto 0);
		AddressBus 	: in std_logic_vector(15 downto 0);
		ROM_address : out std_logic_vector(15 downto 0);
		SRAM_DQ    	: inout unsigned(15 downto 0);
		SRAM_ADDR  	: out unsigned(17 downto 0);
		SRAM_UB_N,            -- High-byte Data Mask
		SRAM_LB_N,            -- Low-byte Data Mask
		SRAM_WE_N,            -- Write Enable
		SRAM_CE_N,            -- Chip Enable
		SRAM_OE_N : out std_logic  -- Output Enable
	);
	end component;
	
	component debounce --JB0513
		port (
			clk, resetsw : in std_logic;
			resetout  : out std_logic
		);
	end component debounce;

	component slowclk --JB0513
	port (
		clkin : in std_logic;
		clkout  : out std_logic
	);
	end component slowclk;

	component de2_vga_raster is 
  port (
		reset : in std_logic;
		clk   : in std_logic;                    -- Should be 25.125 MHz

		center: in std_logic_vector(15 downto 0) := X"f0f0"; -- circle center
		 
		VGA_CLK,                         -- Clock
		VGA_HS,                          -- H_SYNC
		VGA_VS,                          -- V_SYNC
		VGA_BLANK,                       -- BLANK
		VGA_SYNC : out std_logic;        -- SYNC
		VGA_R,                           -- Red[9:0]
		VGA_G,                           -- Green[9:0]
		VGA_B : out unsigned(9 downto 0) -- Blue[9:0]
	);
	end component;
	
	component Control
	port(
		IR				: in std_logic_vector(7 downto 0);
		MCycle			: in std_logic_vector(2 downto 0);
		P				: in std_logic_vector(7 downto 0);
		LCycle			: out std_logic_vector(2 downto 0);	   -- Resulting cycle
		ALU_Op			: out std_logic_vector(3 downto 0);	   -- Opcode for the ALU
		Set_BusA_To		: out std_logic_vector(2 downto 0);    -- DI, A, X, Y, S, P
		Set_Addr_To		: out std_logic_vector(1 downto 0);    -- PC Adder, S, ADD, BA
		Write_Data		: out std_logic_vector(2 downto 0);    -- DL, A, X, Y, S, P, PCL, PCH
		Jump			: out std_logic_vector(1 downto 0);    -- PC, +1, DIDL, Rel
		BAAdd			: out std_logic_vector(1 downto 0);	   -- None, DB Inc, BA Add, BA Adj
		BreakAtNA		: out std_logic;	-- Break at ??
		ADDAdd			: out std_logic;	-- ???
		PCAdd			: out std_logic;	-- Program counter add
		Inc_S			: out std_logic;	-- Increment Stack
		Dec_S			: out std_logic;	-- Decrement Stack
		LDA				: out std_logic;	-- Load Accumulator
		LDP				: out std_logic;	-- Load Processor status register
		LDX				: out std_logic;	-- Load X Register
		LDY				: out std_logic;	-- Load Y Register
		LDS				: out std_logic;	-- Load Stack Register
		LDDI			: out std_logic;	-- Load (I_ADDDC?)
		LDALU			: out std_logic;	-- Load ALU
		LDADD			: out std_logic;	-- Load ADDD register
		LDABL			: out std_logic;	-- Load Address Bus Low
		LDABH			: out std_logic;	-- Load Address Bus High
		SaveP			: out std_logic;	-- Save processor status
		Write			: out std_logic
	);
	end component;

	
	component ALU
	port(
		Op		: in std_logic_vector(3 downto 0);
		BusA	: in std_logic_vector(7 downto 0);
		BusB	: in std_logic_vector(7 downto 0);
		P_In	: in std_logic_vector(7 downto 0);
		P_Out	: out std_logic_vector(7 downto 0);
		Q		: out std_logic_vector(7 downto 0)
	);
	end component;
	
	component hex7seg is 
	port
		( input : in std_logic_vector(3 downto 0); -- A number 
       output : out std_logic_vector(6 downto 0)); -- Just bits
	end component;

end package;