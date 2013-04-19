# 
#

RM = rm
RMFLAGS = -f
XAS = ../../dasm/dasm.exe
ROM2VHDL = ../../rom2vhdl/rom2vhdl.exe

all:   ../../VHDL/testrom.vhd

../../VHDL/testrom.vhd: test.bin test.template
	$(ROM2VHDL) test.bin test.template ../../VHDL/testrom.vhd

test.bin: test.asm
	$(XAS) test.asm -f3 -otest.bin -ltest.lst

clean:
	$(RM) $(RMFLAGS) ../../VHDL/testrom.vhd
	$(RM) $(RMFLAGS) test.bin test.lst *.BAK


#.PHONY: all clean

