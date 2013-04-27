#!/usr/bin/env ruby

`ghdl -i *.vhd*`
filename = ARGV[0]

filename_no_extension = filename.gsub(/\.vhd.?$/, "")

puts "Writing #{filename} to #{filename_no_extension}"

`ghdl -a #{filename}`
`ghdl -e #{filename_no_extension}`
`ghdl -r #{filename_no_extension} --vcd=#{filename_no_extension}.vcd`
