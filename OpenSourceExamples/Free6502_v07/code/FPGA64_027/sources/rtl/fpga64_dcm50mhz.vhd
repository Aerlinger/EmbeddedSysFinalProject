-- -----------------------------------------------------------------------
--
--                                 FPGA 64
--
--     A fully functional commodore 64 implementation in a single FPGA
--
-- -----------------------------------------------------------------------
-- Copyright 2005-2008 by Peter Wendrich (pwsoft@syntiac.com)
-- http://www.syntiac.com/fpga64.html
-- -----------------------------------------------------------------------
--
-- 50 Mhz clock divider for Xilinx FPGAs
-- 
-- -----------------------------------------------------------------------

library IEEE;
library UNISIM;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;
use UNISIM.VComponents.all;

-- -----------------------------------------------------------------------

entity clock50 is
	port (
		xtal50: in std_logic;
		clk50out: out std_logic;
		clk32out: out std_logic
	);
end clock50;

-- -----------------------------------------------------------------------

architecture rtl of clock50 is
	signal clk32: std_logic;
	signal clk50: std_logic;
	signal clk100: std_logic;
	signal clk32_dcm: std_logic;
	signal clk50_dcm: std_logic;
begin
	dcm_module : DCM
		generic map(
			CLKIN_PERIOD => 20.0,
			CLK_FEEDBACK => "1x",
--			CLKFX_MULTIPLY => 16,
--			CLKFX_DIVIDE => 25,
			CLKFX_MULTIPLY => 12,
			CLKFX_DIVIDE => 19,
			DFS_FREQUENCY_MODE => "LOW",
			DLL_FREQUENCY_MODE => "LOW",
			STARTUP_WAIT => FALSE,
			DUTY_CYCLE_CORRECTION => TRUE
		)
		port map(
			CLKIN => xtal50,
			CLK0 => clk50_dcm,
--			CLKFB => clk50,
			CLKFB => clk50_dcm,
			CLK2X => clk100,
			CLKFX => clk32_dcm
		);
	
	clk32buffer: BUFG
		port map(
			I => clk32_dcm,
			O => clk32
		);

	clk50buffer: BUFG
		port map(
			I => clk50_dcm,
			O => clk50
		);

	clk50out <= clk50;
	clk32out <= clk32;
end rtl;

