# Chapter 4: Machine Language

This folder contains the implementation of assembly programs described in Chapter 4 of "The Elements of Computing Systems" (also known as "Nand to Tetris").

## Contents

- **Mult.asm**: Program that performs multiplication
- **Fill.asm**: Program that fills the screen based on keyboard input

## Testing the Programs

To test these assembly programs, you have two options:

1. **Use the Nand2Tetris Software Suite**:
   - Download and install the Nand2Tetris Software Suite from the official website.
   - Use the CPU Emulator tool to load the .asm files.
   - Load the corresponding .tst file for the program you want to test.
   - For Mult.asm, use Mult.tst and Mult.cmp to test on representative data values.
   - For Fill.asm, use Fill.tst. There's no .cmp file - check by visually inspecting the simulated screen.

2. **Use the Web-based CPU Emulator**:
   - Visit the web-based CPU Emulator at https://nand2tetris.github.io/web-ide/cpu
   - Load the .asm files into the emulator.
   - Load the corresponding .tst file for the program you want to test.
   - Run the test scripts as described above for each program.

Note: The .tst and .cmp files are not included in this folder but are available in the Nand2Tetris Software Suite and the web-based simulator.

## Program Descriptions

### Mult.asm
This program multiplies two numbers stored in RAM[0] and RAM[1] and stores the result in RAM[2].

### Fill.asm
This program runs an infinite loop that listens to the keyboard input. When a key is pressed, the program blackens the screen, and when no key is pressed, it clears the screen.
