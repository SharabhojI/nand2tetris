# Chapter 6: Assembler

This folder contains the implementation and testing infrastructure for the Hack assembler described in Chapter 6 of "The Elements of Computing Systems" (also known as "Nand to Tetris").

## Contents

- **run_test.bat**: Batch script to compile the assembler and run tests on all test programs

### Source Files (/src/)
The `src` folder contains C++ implementation files (`.cpp`) and their corresponding header files (`.h`) for the following assembler modules:

- assembler.cpp
- parser.cpp / parser.h
- code.cpp / code.h
- symbol_table.cpp / symbol_table.h

### Test Files (/test/)
The `test` folder contains assembly (`.asm`) test programs and their corresponding expected output (`_test.hack`) files. The test programs include:

- Add.asm
- Max.asm
- Rect.asm
- Pong.asm

## Running Tests

To compile the assembler and run tests on all test programs:

1. Ensure you have a C++ compiler (g++) installed and properly set up.
2. Run the `run_test.bat` script.

This will compile the assembler into an executable (HackAssembler.exe) and then assemble each test program in the `test` folder. The generated `.hack` files are compared against the corresponding `_test.hack` files to verify correct assembly.

## Assembler Structure

The assembler is composed of four main modules:

1. **assembler.cpp**: The main program that coordinates the assembly process.
2. **parser.cpp/h**: Parses the assembly code into its components.
3. **code.cpp/h**: Translates assembly mnemonics into binary codes.
4. **symbol_table.cpp/h**: Manages symbols and their corresponding addresses.

## Testing Process

The `run_test.bat` script performs the following steps:

1. Compiles the assembler from the source files in the `src` folder.
2. For each `.asm` file in the `test` folder:
   a. Runs the assembler on the `.asm` file.
   b. Compares the generated `.hack` file with the corresponding `_test.hack` file.
   c. Reports whether the test passed or failed, showing differences if any.

## Error Handling

The assembler includes error checking for various scenarios:
- File opening errors
- Unknown mnemonics in dest, comp, and jump fields
- Incorrect instruction types when accessing symbol, dest, comp, or jump fields
- Symbol table lookup errors

If any of these errors occur, the assembler will throw a runtime exception with a descriptive error message.

## Adding New Test Programs

To add a new test program:

1. Create the assembly program in the `test` folder (e.g., `NEWPROGRAM.asm`).
2. Create a corresponding expected output file (e.g., `NEWPROGRAM_test.hack`).
3. Modify the `run_test.bat` script to include the new test program in its list of files to process.
