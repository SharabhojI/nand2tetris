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

## Known Issues

### RAM16K Testing

Significant difficulties were encountered in testing the RAM16K module:

1. **Simulation Challenges**: Attempts to simulate the RAM16K module resulted in excessive memory usage, causing system instability (blue screens).

2. **FPGA Implementation**: The RAM16K module, as designed in the textbook using a hierarchical structure of smaller RAM units, exceeds the available resources when attempting to test on the PYNQ-Z2 board's FPGA (Xilinx Zynq XC7Z020).

3. **Testing Limitations**: Due to these constraints, full testing of the RAM16K module as specified in the textbook was not feasible.

These issues highlight the challenges of mapping theoretical designs to real-world hardware constraints, especially when dealing with larger memory structures.

## Adding New Chips

To add a new chip:

1. Create the chip implementation in the `src` folder (e.g., `NEWCHIP.v`).
2. Create a corresponding testbench in the `test` folder (e.g., `NEWCHIP_tb.v`).
3. Add the chip name to `chip_list.txt`.