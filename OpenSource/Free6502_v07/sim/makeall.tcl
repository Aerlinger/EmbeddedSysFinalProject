vcom -reportprogress 300 -work work {G:/prj/Free-IP/6502/VHDL/ramlib_sim.vhd}
vcom -reportprogress 300 -work work {G:/prj/Free-IP/6502/VHDL/microcode.vhd}
vcom -reportprogress 300 -work work {G:/prj/Free-IP/6502/VHDL/free6502.vhd}
vcom -reportprogress 300 -work work {G:/prj/Free-IP/6502/VHDL/testrom.vhd}
vcom -reportprogress 300 -work work {G:/prj/Free-IP/6502/VHDL/testsuite.vhd}
vsim work.testsuite
view *
do wave.do
run -all

