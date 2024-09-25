# Chapter 7: VM Translator

This folder contains the implementation and testing infrastructure for the VM Translator described in Chapter 7 of "The Elements of Computing Systems" (also known as "Nand to Tetris").

## Contents

- **run_test.bat**: Batch script to compile the VM Translator and translate all test VM programs

### Source Files (/src/)
The `src` folder contains C++ implementation files (`.cpp`) and their corresponding header files (`.h`) for the following VM Translator modules:

- vm_translator.cpp
- parser.cpp / parser.h
- code_writer.cpp / code_writer.h

### Test Files (/test/)
The `test` folder contains VM (`.vm`) test programs:

- BasicTest.vm
- PointerTest.vm
- SimpleAdd.vm
- StackTest.vm
- StaticTest.vm

## Running Tests

To compile the VM Translator and run translations on all test programs:

1. Ensure you have a C++ compiler (g++) installed and properly set up.
2. Run the `run_test.bat` script.

This will compile the VM Translator into an executable (VMTranslator.exe) and then translate each test program in the `test` folder. The generated `.asm` files can be tested using the CPU Emulator available at https://nand2tetris.github.io/web-ide/cpu.

## VM Translator Structure

The VM Translator is composed of three main modules:

1. **vm_translator.cpp**: The main program that coordinates the translation process.
2. **parser.cpp/h**: Parses the VM commands into their components.
3. **code_writer.cpp/h**: Generates assembly code from the parsed VM commands.

## Translation Process

The `run_test.bat` script performs the following steps:

1. Compiles the VM Translator from the source files in the `src` folder.
2. For each `.vm` file in the `test` folder:
   a. Runs the VM Translator on the `.vm` file.
   b. Generates a corresponding `.asm` file.

## Testing

After running the `run_test.bat` script, you should manually test the generated `.asm` files using the CPU Emulator at https://nand2tetris.github.io/web-ide/cpu. This step is not automated and requires manual verification of the translated code's correctness.

## Error Handling

The VM Translator includes error checking for various scenarios:
- File opening errors
- Unknown VM commands
- Incorrect command formats

If any of these errors occur, the VM Translator will throw a runtime exception with a descriptive error message.

## Adding New Test Programs

To add a new test program:

1. Create the VM program in the `test` folder (e.g., `NEWPROGRAM.vm`).
2. Modify the `run_test.bat` script to include the new test program in its list of files to process.

Remember to test the generated `.asm` file using the CPU Emulator to verify correct translation.