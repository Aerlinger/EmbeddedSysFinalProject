# 

CC = gcc
RM = rm
RMFLAGS = -f

all:   mcgen.exe mcgen_verilog.exe ../VHDL/microcode.vhd ../verilog/microcode.v

mcgen.exe: mcgen.c
	$(CC) -s -o mcgen.exe mcgen.c

mcgen_verilog.exe: mcgen_verilog.c
	$(CC) -s -o mcgen_verilog.exe mcgen_verilog.c

clean:
	$(RM) $(RMFLAGS) mcgen.exe 
	$(RM) $(RMFLAGS) mcgen_verilog.exe 
	$(RM) $(RMFLAGS) ../VHDL/microcode.vhd
	$(RM) $(RMFLAGS) ../verilog/microcode.v
	$(RM) $(RMFLAGS) *.BAK

microcode:	../VHDL/microcode.vhd ../verilog/microcode.v

../VHDL/microcode.vhd:  microcode.csv  mcgen.exe
	./mcgen.exe microcode.csv >../VHDL/microcode.vhd

../verilog/microcode.v:  microcode.csv  mcgen_verilog.exe
	./mcgen_verilog.exe microcode.csv >../verilog/microcode.v


#.PHONY: all clean

