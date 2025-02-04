# Chapter 9: High Level Language

This folder contains a simple implementation of the game of Snake in the Jack programming language described in Chapter 9 of "The Elements of Computing Systems" (also known as "Nand to Tetris").

## Contents

### Source Files (/src/)
The `src` folder contains Jack language files (`.jack`) for the game of Snake:

- Main.jack
- Game.jack
- Snake.jack
- Food.jack

### Test Programs (/test/)
The `test` folder contains a variety of premade Jack programs that can be used as reference for developing your own programs.

## Compiling Jack Programs

To compile Jack programs:

1. Place all the .jack files into a singular input directory.
2. Use the [Jack Compiler](https://nand2tetris.github.io/web-ide/compiler) to compile the program files in to `.vm` code.

This will compile the Jack files and translate them into their respective `.vm` files, storing them in the input folder. The generated `.vm` files can be tested using the VM Emulator available at https://nand2tetris.github.io/web-ide/vm.

## Running Jack Programs

After generating the `vm` files, you can run and test the program using the VM Emulator at https://nand2tetris.github.io/web-ide/vm.

## Limitations Of The Jack Language
Jack is designed as a simplified, high-level object-oriented language. Limitations of Jack include (but are not limited to):

- No inheritance
- No standard input/output beyond Screen and Keyboard
- Limited standard library
- Limited data types
- No floating-point arithmetic
- No string manipulation beyond basic operations
- No `else if` construct
- No garbage collection (memory must be managed manually)

## Common Errors

Jack programming pitfalls to watch for:
- Missing return statements
- Invalid operator usage (== and != for comparison instead of = and ~(x = y))
- Improper nesting of if-else blocks
- Memory leaks from undisposed objects

The Jack compiler provides some basic error checking with regards to operators.

## Adding New Programs

To create a new Jack program:

1. Create class files with .jack extension (e.g. `Game.jack`, `Main.jack`).
2. Include a `Main.jack` class with a main() function.
4. Compile and test using the online IDE tools.
