# Chapter 10: Compiler Part I - Syntax Analyzer

This folder contains the implementation and testing infrastructure for the Syntax Analyzer described in Chapter 10 of *The Elements of Computing Systems* (also known as *Nand to Tetris*).

## Contents

- **run_test.bat**: Batch script to compile the Syntax Analyzer and run it on all provided `.jack` files, testing outputs against the provided `_cmp.xml` files.

### Source Files (/src/)
The `src` folder contains C++ implementation files (`.cpp`) and their corresponding header files (`.h`) for the following Syntax Analyzer modules:

- **jack_analyzer.cpp**: Main program for performing syntax analysis.
- **jack_tokenizer.cpp / jack_tokenizer.h**: Tokenizer for parsing the `.jack` files.
- **compilation_engine.cpp / compilation_engine.h**: Converts tokens into the appropriate syntax structure.

### Test Files (/test/)
The `test` folder includes sub-folders containing `.jack` test programs for testing the syntax analyzer, and `_cmp.xml` files for comparing the generated `.xml` files against.

- **ArrayTest/**
   - Main.jack
   - Main_cmp.xml
   - MainT_cmp.xml
- **ExpressionLessSquare/**
   - Main.jack
   - Main_cmp.xml
   - MainT_cmp.xml
   - Square.jack
   - Square_cmp.xml
   - SquareT_cmp.xml
   - SquareGame.jack
   - SquareGame_cmp.xml
   - SquareGameT_cmp.xml
- **Square/**
   - Main.jack
   - Main_cmp.xml
   - MainT_cmp.xml
   - Square.jack
   - Square_cmp.xml
   - SquareT_cmp.xml
   - SquareGame.jack
   - SquareGame_cmp.xml
   - SquareGameT_cmp.xml

## Running Tests

To compile the Syntax Analyzer and run tests and comparisons on all programs:

1. Ensure you have a C++ compiler (g++) installed and properly set up.
2. Run the `run_test.bat` script.

This will compile the Syntax Analyzer into an executable (`JackTokenizer.exe`) and then run it on each `.jack` file in the sub-folders of the `test`. The corresponding `.xml` files will be generated in the respective folders.

## Syntax Analyzer Structure

The Syntax Analyzer is composed of the following main modules:

1. **jack_analyzer.cpp**: The main program that coordinates the syntax analysis process.
2. **jack_tokenizer.cpp/h**: Tokenizes the `.jack` source files for the analyzer.
3. **compilation_engine.cpp/h**: Processes the tokens and generates the correct XML output representing the syntax structure.

## Analysis Process

The `run_test.bat` script performs the following steps:

1. Compiles the Syntax Analyzer from the source files in the `src` folder.
2. For each sub-folder in the `test` folder:
   - Runs the Syntax Analyzer on all `.jack` files in the folder.
   - Generates the appropriate `.xml` files.
3. Compares the generated `.xml` files against the provided `_cmp.xml` files.

## Testing

After running the `run_test.bat` script, the `.xml` files generated for each test are compared against the expected outputs. Any discrepancies are noted, and you may need to manually inspect the generated XML files to verify the correctness of the syntax analysis.

## Error Handling

The Syntax Analyzer includes error checking for various scenarios:

- Invalid syntax in `.jack` files.
- Tokenization issues.
- Mismatches between generated XML files and expected output.

If any of these errors occur, the Syntax Analyzer will throw an appropriate error message.

## Adding New Test Programs

To add a new test program:

1. Create the `.jack` file in the `test` folder (e.g., `NEWPROGRAM.jack`).
2. Modify the `run_test.bat` script to include the new test program in its list of files to process.
3. (Optional) Create a `_cmp.xml` file to compare the generated `.xml` file against if the structure is known.

After this, run the batch script to generate the `.xml` output for the new test program and optionally compare it with the expected result. If a relevant `_cmp.xml` file does not exist, a warning will be displayed.
