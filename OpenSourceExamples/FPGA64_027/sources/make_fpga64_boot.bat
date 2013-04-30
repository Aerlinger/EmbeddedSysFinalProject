del /q boot
rmdir boot

mkdir boot
copy roms\c64basic_901226_01.bin boot\8r05a000.bin
copy roms\c64kernal_901227_03.bin boot\8r05e000.bin
copy roms\c64char_901225_01.bin boot\8r051000.bin
copy roms\c64char_901225_01.bin boot\8r059000.bin
copy roms\c64char_901225_01.bin boot\8r05d000.bin
copy roms\drivecpu_1k30.bin boot\8drive.bin
copy quartus_cone\quartus_cone.rbf boot\8fpga.bin
