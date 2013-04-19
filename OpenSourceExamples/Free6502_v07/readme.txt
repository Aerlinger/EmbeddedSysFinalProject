----------------------------------------------------------------------------
----------------------------------------------------------------------------
--  The Free IP Project
--  Free-6502 -- VHDL 6502 Core
--  (c) 1999-2000, The Free IP Project and David Kessner
--
--
--  FREE IP GENERAL PUBLIC LICENSE
--  TERMS AND CONDITIONS FOR USE, COPYING, DISTRIBUTION, AND MODIFICATION
--
--  1.  You may copy and distribute verbatim copies of this core, as long
--      as this file, and the other associated files, remain intact and
--      unmodified.  Modifications are outlined below.  
--  2.  You may use this core in any way, be it academic, commercial, or
--      military.  Modified or not.  
--  3.  Distribution of this core must be free of charge.  Charging is
--      allowed only for value added services.  Value added services
--      would include copying fees, modifications, customizations, and
--      inclusion in other products.
--  4.  If a modified source code is distributed, the original unmodified
--      source code must also be included (or a link to the Free IP web
--      site).  In the modified source code there must be clear
--      identification of the modified version.
--  5.  Visit the Free IP web site for additional information.
--      http://www.free-ip.com
--
----------------------------------------------------------------------------
----------------------------------------------------------------------------

This is version 0.7 (June 20, 2000) of the Free-6502 core. 
The complete documentation can be read at http://www.free-ip.com


----------------------------------------------------------------------------
Directory Structure
./	
	Root Directory, where everything starts from

./VHDL	
	The VHDL source code.

./Verilog	
	The Verilog source code (a work in process).

./code/testsuite
	The 6502 assembly test suite

./sim
	ModelSIM related files

./microcode
	The microcode spreadsheet, and the programs to 
	convert it to VHDL and Verilog

./opcode_log
	The program that tracks opcode useage.

./rom2vhdl
	The ROM2VHDL conversion utlity

./dasm
	The 6502 assembler used for the test suite (.exe only)

./www
	Documentation and manuals



----------------------------------------------------------------------------
Change History:
v0.7
	Shortened EOR ABS by one clock cycle.
	Fixed the instantiation of RAM in testsuite.vhd.
	Fixed a small problem with sim/makeall.tcl.
	Removed old and outdated references to conversions.vhd.

v0.6
	Added HTML files to the distribution ZIP file.
	Uses the Free-RAM core (included) for the testsuite.
	Fixed a bug in mcgen_verilog that caused errors in the verilog code.

	
v0.5
	Changed the directory structure. 
	Improved Makefiles.
	Fixed several bugs reguarding BRK and status flags.
	Fixed bugs reguarding some addressing modes.
	test.asm tests for the fixed bugs.
	Now the following flags have this status at reset:
		D = 0
		I = 1
		Other flags = Undefined
	Cleaned up the code a little.
	
v0.4
	Now included with the distribution are a couple of tools for
	modifying the microcode source files and generating the VHDL
	and Verilog source of this microcode.
	Fixed a bug with branches and negative relative PC offsets
	Fixed a bug with TXS
	Fixed a bug with SBC Immediate
	Changed the test code to test for the fixed bugs

v0.3
	Optimized the ALU's
	Fixed a bug with carry flags and the SBC instruction
	Cleaned up the code.

v0.2
	Fixed interrupts

v0.1
	Inital release

----------------------------------------------------------------------------
----------------------------------------------------------------------------

