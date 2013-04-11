# use "make log" to generate the log file

CC = gcc
RM = rm
RMFLAGS = -f

all:   opcode_log.exe

opcode_log.exe: opcode_log.c
	$(CC) -s -o opcode_log.exe opcode_log.c

clean:
	$(RM) $(RMFLAGS) opcode_log.exe opcode_log.txt *.BAK

log:	opcode_log.txt

opcode_log.txt:  ../sim/opcode.log  opcode_log.exe
	./opcode_log.exe ../sim/opcode.log >opcode_log.txt


#.PHONY: all clean

