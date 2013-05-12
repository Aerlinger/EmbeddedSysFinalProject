#!/usr/bin/env ruby

filename = ARGV[0]

puts "Writing #{filename}"

# Compile the source file:
`ghdl -a --ieee=synopsys -fexplicit #{filename}.vhd`
`ghdl -e --ieee=synopsys -fexplicit #{filename}`
`ghdl -r --ieee=synopsys -fexplicit #{filename}`

# Compile the test bench if it exists:
`ghdl -a --ieee=synopsys -fexplicit #{filename}_tb.vhd`
`ghdl -e --ieee=synopsys -fexplicit #{filename}_tb`
`ghdl -r --ieee=synopsys -fexplicit #{filename}_tb --vcd=#{filename}_tb.vcd`
