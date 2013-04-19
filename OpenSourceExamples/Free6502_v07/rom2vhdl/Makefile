# 

CC = gcc
RM = rm
RMFLAGS = -f

all:   rom2vhdl.exe

rom2vhdl.exe: rom2vhdl.c
	$(CC) -s -o rom2vhdl.exe rom2vhdl.c

clean:
	$(RM) $(RMFLAGS) rom2vhdl.exe
	$(RM) $(RMFLAGS) *.BAK

#.PHONY: all clean

