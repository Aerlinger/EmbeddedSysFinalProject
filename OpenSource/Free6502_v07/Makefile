DIST_DIR = dist/latest
CODE_DIR = code
TESTSUITE_DIR = $(CODE_DIR)/testsuite
ROM2VHDL_DIR = rom2vhdl
MICROCODE_DIR = microcode
OPCODE_LOG_DIR = opcode_log
DASM_DIR = dasm
SIM_DIR = sim
VERILOG_DIR = verilog
VHDL_DIR = VHDL
FREERAM_DIR = ../ramlib/VHDL
WWW_SOURCE = /WINDOWS/Profiles/dk/My\ Documents/My\ Webs/myweb4/6502
WWW_DEST = www

COPY = cp
COPYDIR = cp -r
MKDIR = mkdir
RM = rm
RMFLAGS = -f
RMDIR = rm -rf


all:	free_ram
	make -C $(ROM2VHDL_DIR) all
	make -C $(MICROCODE_DIR) all
	make -C $(TESTSUITE_DIR) all
	make -C $(OPCODE_LOG_DIR) all
	
free_ram:
	$(COPY) $(FREERAM_DIR)/ramlib_sim.vhd $(VHDL_DIR)
	
web:
	$(COPYDIR) $(WWW_SOURCE)/* $(WWW_DEST)
	$(RM) $(RMFLAGS) $(WWW_DEST)/*.ZIP

clean:
	make -C $(ROM2VHDL_DIR) clean
	make -C $(MICROCODE_DIR) clean
	make -C $(TESTSUITE_DIR) clean
	make -C $(OPCODE_LOG_DIR) clean
	$(RM) $(RMFLAGS) *.BAK
	$(RM) $(RMFLAGS) $(VHDL_DIR)/*.BAK
	$(RM) $(RMFLAGS) $(VERILOG_DIR)/*.BAK
	$(RM) $(RMFLAGS) $(SIM_DIR)/*.BAK
	$(RMDIR) $(WWW_DEST)/*


dist:	clean all web
	$(RMDIR) $(DIST_DIR)
	$(MKDIR) $(DIST_DIR)
	$(COPY)  readme.txt $(DIST_DIR)
	$(COPY)  Makefile $(DIST_DIR)
	$(MKDIR) $(DIST_DIR)/$(CODE_DIR)
	$(MKDIR) $(DIST_DIR)/$(TESTSUITE_DIR)
	$(COPY)  $(TESTSUITE_DIR)/*  $(DIST_DIR)/$(TESTSUITE_DIR)
	$(MKDIR) $(DIST_DIR)/$(DASM_DIR)
	$(COPY)  $(DASM_DIR)/dasm.exe $(DIST_DIR)/$(DASM_DIR)
	$(MKDIR) $(DIST_DIR)/$(MICROCODE_DIR)
	$(COPY)  $(MICROCODE_DIR)/* $(DIST_DIR)/$(MICROCODE_DIR)
	$(MKDIR) $(DIST_DIR)/$(OPCODE_LOG_DIR)
	$(COPY)  $(OPCODE_LOG_DIR)/* $(DIST_DIR)/$(OPCODE_LOG_DIR)
	$(MKDIR) $(DIST_DIR)/$(ROM2VHDL_DIR)
	$(COPY)  $(ROM2VHDL_DIR)/* $(DIST_DIR)/$(ROM2VHDL_DIR)
	$(MKDIR) $(DIST_DIR)/$(SIM_DIR)
	$(COPY)  $(SIM_DIR)/makeall.tcl $(DIST_DIR)/$(SIM_DIR)
	$(COPY)  $(SIM_DIR)/wave.do $(DIST_DIR)/$(SIM_DIR)
	$(MKDIR) $(DIST_DIR)/$(VERILOG_DIR)
	$(COPY)  $(VERILOG_DIR)/* $(DIST_DIR)/$(VERILOG_DIR)
	$(MKDIR) $(DIST_DIR)/$(VHDL_DIR)
	$(COPY)  $(VHDL_DIR)/* $(DIST_DIR)/$(VHDL_DIR)
	$(MKDIR) $(DIST_DIR)/$(WWW_DEST)
	$(COPYDIR) $(WWW_DEST)/* $(DIST_DIR)/$(WWW_DEST)

	
#.PHONY: all clean

