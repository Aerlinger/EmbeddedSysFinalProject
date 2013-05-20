SETLOCAL

::
:: Release value
::
SET RELEASETXT=0.27
SET RELEASE=027

::
SET TODIR=releases\FPGA64_%RELEASE%
SET TOBOOT=%TODIR%\boot
SET TOSRC=%TODIR%\sources
SET TOROMS=%TOSRC%\roms
SET TORTL=%TOSRC%\rtl

::
:: Copy readme
::
mkdir %TODIR%
copy readme.txt %TODIR%

::
:: Copy boot images
::
mkdir %TOBOOT%
call make_fpga64_boot.bat
copy boot %TOBOOT%
echo FPGA64 %RELEASETXT% >%TOBOOT%\8desc.txt 

::
:: Make source tree
::
mkdir %TOSRC%
copy make_fpga64_boot.bat %TOSRC%
copy make_fpga64_release.bat %TOSRC%
copy readme.txt %TOSRC%

::
:: Copy utilities
::
mkdir %TOSRC%\src
mkdir %TOSRC%\src\scanconverter
copy src\scanconverter\scanconverter.py %TOSRC%\src\scanconverter


::
:: Copy roms
::
mkdir %TOSRC%\roms
copy roms\c64basic_901226_01 %TOROMS%
copy roms\c64char_901225_01 %TOROMS%
copy roms\c64kernal_901227_03 %TOROMS%
copy roms\drivecpu_1k30 %TOROMS%

::
:: Copy quartus project
::
mkdir %TOSRC%\quartus_cone
copy quartus_cone\fpga64_top.bdf %TOSRC%\quartus_cone
copy quartus_cone\fpga64_cone.bsf %TOSRC%\quartus_cone
copy quartus_cone\gbridge.bsf %TOSRC%\quartus_cone
copy quartus_cone\gbridge.tdf %TOSRC%\quartus_cone
copy quartus_cone\quartus_cone.qpf %TOSRC%\quartus_cone
copy quartus_cone\quartus_cone.qsf %TOSRC%\quartus_cone

::
:: Copy RTL/vhdl code
::
mkdir %TORTL%
mkdir %TORTL%\roms
copy rtl\roms\rom_c64_basic.vhd %TORTL%\roms
copy rtl\roms\rom_c64_chargen.vhd %TORTL%\roms
copy rtl\roms\rom_c64_kernal.vhd %TORTL%\roms
copy rtl\cia6526.vhd %TORTL%
copy rtl\cpu65xx_e.vhd %TORTL%
copy rtl\cpu65xx_fast.vhd %TORTL%
copy rtl\cpu_6510.vhd %TORTL%
copy rtl\fpga64_buslogic_nommu.vhd %TORTL%
copy rtl\fpga64_buslogic_roms.vhd %TORTL%
copy rtl\fpga64_bustiming.vhd %TORTL%
copy rtl\fpga64_cone.vhd %TORTL%
copy rtl\fpga64_cone_scanconverter.vhd %TORTL%
copy rtl\fpga64_dcm100mhz.vhd %TORTL%
copy rtl\fpga64_dcm50mhz.vhd %TORTL%
copy rtl\fpga64_hexy.vhd %TORTL%
copy rtl\fpga64_hexy_vmode.vhd %TORTL%
copy rtl\fpga64_keyboard_matrix_joyemu.vhd %TORTL%
copy rtl\fpga64_keyboard_matrix_mark_mcdougall.vhd %TORTL%
copy rtl\fpga64_rgbcolor.vhd %TORTL%
copy rtl\fpga64_scandoubler.vhd %TORTL%
copy rtl\fpga64_xess_xsa3s1000.vhd %TORTL%
copy rtl\gen_ram.vhd %TORTL%
copy rtl\gen_rwram.vhd %TORTL%
copy rtl\io_ps2_keyboard.vhd %TORTL%
copy rtl\video_vicII_656x_e.vhd %TORTL%
copy rtl\video_vicII_656x_a.vhd %TORTL%


ENDLOCAL
