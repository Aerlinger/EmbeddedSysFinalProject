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
-- fpga64_cone_scancoverter.vhd
--
-- -----------------------------------------------------------------------
--
-- Convert 15Khz HSync picture to 31Khz VGA picture
--
-- This converter allows (slightly) different line lengths for incomming
-- and outgoing signals. This is necessary on the C-One to emulate
-- correct CPU/System speed by dividing in fractional parts.
--
-- VSync edge is used to resync VGA with the system.
--
-- -----------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.ALL;
use IEEE.numeric_std.all;

-- -----------------------------------------------------------------------

entity fpga64_cone_scanconverter is
	generic (
		videoWidth : integer := 1
	);
	port (
		clk : in std_logic;
		
		-- Following two values depend on many factors like CPU speed and video mode.
		-- Use provided "scanconverter.py" utility to (re)calculate these!
		cyclesPerLine : unsigned(11 downto 0);	-- Magic value to tune VGA speed.
		faster : std_logic;						-- Set to 1 if VGA runs faster as C64
		
		hSyncPolarity : in std_logic := '0';
		vSyncPolarity : in std_logic := '0';

		enable_in		: in std_logic;
		video_in		: in unsigned((videoWidth-1) downto 0);
		vsync_in		: in std_logic;
		hsync_in		: in std_logic;

		video_out		: out unsigned((videoWidth-1) downto 0);
		vsync_out		: out std_logic;
		hsync_out		: out std_logic
	);
end entity;

-- -----------------------------------------------------------------------

architecture rtl of fpga64_cone_scanconverter is
constant bufferWidthB : integer := 3;
constant bufferWidthL : integer := 9;
constant bufferWidth : integer := bufferWidthB + bufferWidthL;
constant hSyncLength : integer := 63;

signal cycleCnt : unsigned(11 downto 0);

signal readAddr : unsigned((bufferWidth-1) downto 0);
signal writeAddr : unsigned((bufferWidth-1) downto 0);

signal readIndex : unsigned((bufferWidthL-1) downto 0) := (others => '0');
signal readBlock : unsigned(bufferWidthB downto 0) := (others => '0');
signal writeIndex : unsigned((bufferWidthL-1) downto 0) := (others => '0');
signal writeBlock : unsigned((bufferWidthB-1) downto 0) := (others => '0');
signal oldHSync : std_logic := '0';
signal oldVSync : std_logic := '0';
signal hSyncCount : integer range 0 to hSyncLength;
signal vSyncCount : integer range 0 to 15;

signal ramD : unsigned((videoWidth-1) downto 0);
signal ramQ : unsigned((videoWidth-1) downto 0);
signal ramQReg : unsigned((videoWidth-1) downto 0);
begin
	lineRam: entity work.gen_rwram
		generic map (
			dWidth => videoWidth,
			aWidth => bufferWidth
		)
		port map (
			clk => clk,
			we => '1',
			rAddr => readAddr,
			wAddr => writeAddr,
			d => ramD,
			q => ramQ
		);

	readAddr <= readBlock(bufferWidthB downto 1) & readIndex;
	writeAddr <= writeBlock & writeIndex;
	ramD <= video_in;
	
	process(clk)
	begin
		if rising_edge(clk) then
			cycleCnt <= cycleCnt + 1;

			if enable_in = '1' then
				writeIndex <= writeIndex + 1;
			end if;

			if cycleCnt(0) = '1' then
				readIndex <= readIndex + 1;
			end if;

			if cycleCnt = cyclesPerLine then
				cycleCnt <= (others => '0');
				readBlock <= readBlock + 1;

				hSyncCount <= hSyncLength;
				if vSyncCount /= 0 then
					vSyncCount <= vSyncCount - 1;
				end if;
			end if;

			if hSyncCOunt /= 0 then
				hSyncCOunt <= hSyncCount - 1;
				readIndex <= (others => '0');
			end if;

			oldHSync <= hsync_in;
			if (oldHSync = '1') and (hsync_in = '0') then
				writeIndex <= (others => '0');
				writeBlock <= writeBlock + 1;

				oldVSync <= vsync_in;
				if (vsync_in = '1') and (oldVSync = '0') then
					vSyncCount <= 15;
					-- Sync clocks
					cycleCnt <= (others => '0');
					readIndex <= (others => '0');
					readBlock <= (others => '0');
					writeBlock <= (others => '1');
					if faster = '0' then
						writeBlock <= to_unsigned(1, bufferWidthB);
					end if;
					hSyncCount <= hSyncLength;
				end if;
			end if;
		end if;
	end process;

	-- Video out
	process(clk)
	begin
		if rising_edge(clk) then
			ramQReg <= ramQ;
			video_out <= ramQReg;
			if vSyncCount /= 0 then
				video_out <= "0000";
			end if;
		end if;
	end process;

	-- Horizontal sync
	process(clk)
	begin
		if rising_edge(clk) then
			hsync_out <= not hSyncPolarity;
			if hSyncCOunt /= 0 then
				hsync_out <= hSyncPolarity;
			end if;
		end if;
	end process;

	-- Vertical sync
	process(clk)
	begin
		if rising_edge(clk) then
			vsync_out <= not vSyncPolarity;
			if (vSyncCount = 9) or (vSyncCount = 10) then
				vsync_out <= vSyncPolarity;
			end if;
		end if;
	end process;
end architecture;
