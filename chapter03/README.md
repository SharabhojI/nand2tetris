# Chapter 3: Memory

This folder contains the implementation and testing infrastructure for the memory chips described in Chapter 3 of "The Elements of Computing Systems" (also known as "Nand to Tetris").

## Contents

- **run_test.bat**: Batch script to run tests on all implemented chips
- **test_chip.tcl**: TCL script that compiles, elaborates, and simulates each chip
- **chip_list.txt**: List of chips to be tested

### Source Files (/src/)
The `src` folder contains Verilog (`.v`) implementations of the following chips:

- DFF
- BIT
- REGISTER
- RAM8
- RAM64
- RAM512
- RAM4K
- RAM16K
- PC

### Test Files (/test/)
The `test` folder contains testbench files (`.v`) for each implemented chip.

## Running Tests

To run tests on all implemented chips:

1. Ensure you have Xilinx Vivado installed and properly set up.
2. Run the `run_test.bat` script.

This will execute the `test_chip.tcl` script, which compiles, elaborates, and simulates each chip listed in `chip_list.txt`.

## Adding New Chips

To add a new chip:

1. Create the chip implementation in the `src` folder (e.g., `NEWCHIP.v`).
2. Create a corresponding testbench in the `test` folder (e.g., `NEWCHIP_tb.v`).
3. Add the chip name to `chip_list.txt`.