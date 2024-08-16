@echo off
call C:\Xilinx\Vivado\2024.1\settings64.bat
C:\Xilinx\Vivado\2024.1\bin\vivado -mode tcl -source test_chip.tcl
pause