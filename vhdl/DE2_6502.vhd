--------------------------------------------------------------
--------------------------------------------------------------
--
--  COMS W480 Final Project
--    Sprint 2013
--    A 6502 CPU reconstructed in VHDL and synthesized on 
--		the Altera DE2
--
-- Team Double O Four is:
--     Yu Chen
--     Jaebin Choi
--     Anthony Erlinger
--     Arthy Padma Anandhi Sundaram
--
-- 		DE2 Test Interface:
-- 		 An interface testing the 6502 interactively on the 6502
-- 		  Adapted from Lab1 assignment
--		
-- 		 Button 1: Clock
-- 		 Button 2: Reset
--		
-- 		 Hex1-2: Opcode (leftmost)
-- 		 Hex3-4: PC (leftmost)
-- 		 Hex5-8: ADDR Bus (leftmost)
--		
-- 		 Switches 1-7: Opcode Input
---------------------------------------------------------------
---------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Define interface for lab1
entity DE2_6502 is

	-- external connections
	port (
		-- INPUT: 50 MHz QCO Clock
		-------------------------------------------------
		clk: in std_logic;

		-- INPUT: 4 Button and 18 switch inputs
		-------------------------------------------------
		key: in std_logic_vector(3 downto 0);
		sw : in std_logic_vector(17 downto 0);

		-- OUTPUT: Hex Displays & LEDS
		-------------------------------------------------
		hex0, 
		hex1, 
		hex2, 
		hex3, 
		hex4, 
		hex5, 
		hex6, 
		hex7 : out std_logic_vector(6 downto 0);	-- 7 SEG are Active Low
		ledg : out std_logic_vector(8 downto 0);	-- LEDS are Active High (Go figure)
		ledr : out std_logic_vector(17 downto 0);

		-- SRAM MEMORY
		-------------------------------------------------
		sram_dq 	<= (others => 'Z');
		sram_addr 	<= (others => '0');
		sram_ub_n 	<= '1';
		sram_lb_n 	<= '1';
		sram_ce_n 	<= '1';
		sram_we_n 	<= '1';
		sram_oe_n 	<= '1'
	);

end DE2_6502;

architecture rtl of DE2_6502 is

	signal Databus, DOR, ROM_data : std_logic_vector(7 downto 0);
	signal Addrbus, ROM_address  : std_logic_vector(15 downto 0);
	signal W_R : std_logic;

	component SixFiveO2 
		port(
			Databus:	inout std_logic_vector(7 downto 0);
			Addrbus:	out std_logic_vector(15 downto 0);
			DOR: 		inout std_logic_vector(7 downto 0);
	      	reset, clk: in std_logic;
			XL, 	-- X Register Low
			XH, 	-- Y Register High
			YL, 	
			YH, 	
			ACCL, 	
			ACCH : out std_logic_vector(6 downto 0);
			W_R: 		out std_logic
		);
	end component;

	component rom is
		port(
			addr  : in std_logic_vector(15 downto 0);
			data : out std_logic_vector(7 downto 0)
		);
	end component;

	component SRAMCtrl is
		port (
			reset, clk, W_R: in std_logic;
			ROM_data, DOR : in 	std_logic_vector(7 downto 0);
			Databus: 		out std_logic_vector(7 downto 0);
			Addrbus: 	in 	std_logic_vector(15 downto 0);
			ROM_address: 	out std_logic_vector(15 downto 0);
			sram_dq: 		inout unsigned(15 downto 0);
			sram_addr: 		out unsigned(17 downto 0);
			sram_ub_n,            -- high-byte data mask
			sram_lb_n,            -- low-byte data mask
			sram_we_n,            -- write enable
			sram_ce_n,            -- chip enable
			sram_oe_n : 	out std_logic  -- output enable
		);
	end component;
begin

	----------------------------------------------
	-- 6502 Module with components:
	----------------------------------------------

	CPUConnect: SixFiveO2 port map(
		clk 	=> CLOCK_50, 
		reset 	=> SW(17), 
		W_R		=> W_R, 
		XH		=> HEX7, 
		XL		=> HEX6, 
		YH		=> HEX5, 
		YL		=> HEX4, 
		ACCH	=> HEX3, 
		ACCL	=> HEX2,
		Databus => Databus, 
		DOR		=> DOR, 
		Addrbus => Addrbus
	);

	InstructionROM: Rom port map(
		addr 	=> ROM_address, 
		data 	=> ROM_data
	);

	MemorySRAM: SRAMCtrl port map(
		reset 		=> sw(17), 
		clk 		=> clk, 
		W_R 		=> W_R, 
		ROM_data 	=> ROM_data, 
		DOR 		=> DOR,
		Databus 	=> Databus, 
		AddrBus		=> Addrbus, 
		ROM_address	=> ROM_address, 
		sram_dq		=> sram_dq,    
		sram_addr	=> sram_addr,  
		sram_ub_n	=> sram_ub_n,
		sram_lb_n	=> sram_lb_n,            
		sram_we_n	=> sram_we_n,          
		sram_ce_n	=> sram_ce_n,    
		sram_oe_n	=> sram_oe_n
	);
	
	-- Switch is bound to LEDS (Used for programming)
	process(sw)
	begin
		ledr <= sw;
	end process;


	----------------------------------------------
	-- 7 Segment displays are used for debugging
	----------------------------------------------

	-- The ADDRESS BUS (X---)
	h7: entity hex7seg port map (
		input 	=> Addrbus(3 downto 0),
		output 	=> hex7
	);
	
	-- The ADDRESS BUS (-X--)
	h6: entity hex7seg port map (
		input 	=> Addrbus(7 downto 4),
		output 	=> hex6
	);
	
	-- The ADDRESS BUS 7Seg display  (--X-)
	h5: entity hex7seg port map (
		input 	=> Addrbus(11 downto 8),
		output 	=> hex5
	);
	
	-- The ADDRESS BUS 7Seg display  (---X)
	h4: entity hex7seg port map (
		input 	=>  Addrbus(15 downto 12),
		output 	=> hex4
	);
	
	-- The DATA BUS 7Seg display
	h3: entity hex7seg port map (
		input 	=> std_logic_vector(Databus(3 downto 0)),
		output 	=> hex3
	);
	
	-- The DATA BUS 7Seg display
	h2: entity hex7seg port map (
		input 	=> std_logic_vector(Databus(3 downto 0)),
		output 	=> hex2
	);
	
	-- The clock_cycles 7Seg display
	h1: entity hex7seg port map (
		input 	=> std_logic_vector(clock_cycles(3 downto 0)),
		output 	=> hex1
	);

	-- The clock_cycles 7Seg display
	h0: entity hex7seg port map (
		input 	=> std_logic_vector(clock_cycles(7 downto 4)),
		output 	=> hex0
	);

end rtl;
