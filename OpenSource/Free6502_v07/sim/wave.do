onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -radix default -format Logic /testsuite/clk
add wave -noupdate -radix default -format Logic /testsuite/reset
add wave -noupdate -radix hexadecimal /testsuite/addr
add wave -noupdate -radix hexadecimal /testsuite/din
add wave -noupdate -radix hexadecimal /testsuite/dout
add wave -noupdate -radix default -format Logic /testsuite/dout_oe
add wave -noupdate -radix default -format Logic /testsuite/we
add wave -noupdate -radix default -format Logic /testsuite/re
add wave -noupdate -radix default -format Logic /testsuite/sync
add wave -noupdate -radix hexadecimal /testsuite/postcode
add wave -noupdate -radix default -format Logic /testsuite/nmi
add wave -noupdate -radix default -format Logic /testsuite/irq
add wave -noupdate -radix hexadecimal /testsuite/u1/u6502/a_reg
add wave -noupdate -radix hexadecimal /testsuite/u1/u6502/x_reg
add wave -noupdate -radix hexadecimal /testsuite/u1/u6502/y_reg
add wave -noupdate -radix hexadecimal /testsuite/u1/u6502/pc
add wave -noupdate -radix default -format Logic /testsuite/u1/u6502/n_flag
add wave -noupdate -radix default -format Logic /testsuite/u1/u6502/v_flag
add wave -noupdate -radix default -format Logic /testsuite/u1/u6502/b_flag
add wave -noupdate -radix default -format Logic /testsuite/u1/u6502/d_flag
add wave -noupdate -radix default -format Logic /testsuite/u1/u6502/i_flag
add wave -noupdate -radix default -format Logic /testsuite/u1/u6502/z_flag
add wave -noupdate -radix default -format Logic /testsuite/u1/u6502/c_flag
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {0 ns}
WaveRestoreZoom {0 ns} {4918 ns}
