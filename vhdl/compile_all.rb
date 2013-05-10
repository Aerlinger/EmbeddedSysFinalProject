#!/usr/bin/env ruby

`ghdl -i *.vhd*`

Dir.glob("*_tb.vhd*").shuffle.each do |filename|
  filename_no_extension = filename.gsub(/\.vhd.?$/, "")

  puts "Writing #{filename} to #{filename_no_extension}"

  `ghdl -a --ieee=synopsys -fexplicit #{filename}`
  `ghdl -e --ieee=synopsys -fexplicit #{filename_no_extension}`
  `ghdl -r --ieee=synopsys -fexplicit #{filename_no_extension} --vcd=#{filename_no_extension}.vcd`
end
