IDEA:
The idea is to write a program that reads a table of 6502 
instructions and generates the VHDL code, instead of hand 
coding in VHDL.  
The table I am using is the table on 
free-ip.com (http://www.free-ip.com/6502/opcodes.htm)
The reason the core is not done in VHDL directly is that
doing so is error prone: you could for example get
LDA right, but LDX wrong even though they are very similar. But 
if you build the knowledge into a table, then the program
will get them both correctly (or both wrong) :)
Currently the C stuff knows enough about the 6502 working so
that it does not have to rely on the table at free-ip.com, but
I haven't got around to remove the dependency from this 
table yet.
----------------------------------------------------------
Files listing (partial)

funs.c : implemented some of the logic
main.c (contains main(), obvious)
ns.c: generated - do not change
poc.c: parse the (HTML) table from free-ip.com
strings.c: contains strings (VHDL statements)
defs.h : defines and externs
externs.h more externs 
ops: the opcodes (HTML format) basically modified from free-ip.com
skel.vhd: the skeleton VHDL
prog.vhd: generated (do not modify)
