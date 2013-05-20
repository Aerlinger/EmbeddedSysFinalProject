-- -----------------------------------------------------------------------
--
-- Syntiac's generic VHDL support files.
--
-- -----------------------------------------------------------------------
-- Copyright 2005-2008 by Peter Wendrich (pwsoft@syntiac.com)
-- http://www.syntiac.com/fpga64.html
-- -----------------------------------------------------------------------
--
-- gen_rwram.vhd
--
-- -----------------------------------------------------------------------
--
-- Simple dual port ram: One read and one write port
--
-- -----------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;

-- -----------------------------------------------------------------------

entity gen_rwram is
	generic (
		dWidth : integer := 8;
		aWidth : integer := 10
	);
	port (
		clk : in std_logic;
		we : in std_logic;
		wAddr : in unsigned((aWidth-1) downto 0);
		rAddr : in unsigned((aWidth-1) downto 0);
		d : in unsigned((dWidth-1) downto 0);
		q : out unsigned((dWidth-1) downto 0)
	);
end entity;

-- -----------------------------------------------------------------------

architecture rtl of gen_rwram is
	subtype addressRange is integer range 0 to ((2**aWidth)-1);
	type ramDef is array(addressRange) of unsigned((dWidth-1) downto 0);
	signal ram: ramDef;

	signal rAddrReg : unsigned((aWidth-1) downto 0) := (others => '0');
begin
-- -----------------------------------------------------------------------
-- Memory write
-- -----------------------------------------------------------------------
	process(clk)
	begin
		if rising_edge(clk) then
			if we = '1' then
				ram(to_integer(wAddr)) <= d;
			end if;
		end if;
	end process;
	
-- -----------------------------------------------------------------------
-- Memory read
-- -----------------------------------------------------------------------
	process(clk)
	begin
		if rising_edge(clk) then
			rAddrReg <= rAddr;
		end if;
	end process;
	q <= ram(to_integer(rAddrReg));
end architecture;


