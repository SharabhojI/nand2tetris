# Nand2Tetris

This repository contains my implementation of the projects from [The Elements of Computing Systems](https://www.nand2tetris.org/), also known as Nand2Tetris. The projects build a computer system from first principles, starting with basic logic gates and working up through hardware and architecture to an operating system.

## Project Structure

The repository is organized into chapters matching the book structure. Currently implemented chapters include:

- [Chapter 1: Boolean Logic](./chapter01) - Implementation of basic logic gates
- [Chapter 2: Boolean Arithmetic](./chapter02) - ALU and arithmetic chips
- [Chapter 3: Sequential Logic](./chapter03) - Registers, memory, and program counter
- [Chapter 4: Machine Language](./chapter04) - Assembly language programs
- [Chapter 5: Computer Architecture](./chapter05) - CPU and computer implementation
- [Chapter 6: Assembler](./chapter06) - Hack assembler implementation
- [Chapter 7: Virtual Machine I](./chapter07) - Stack arithmetic VM implementation
- [Chapter 8: Virtual Machine II](./chapter08) - Program control VM implementation
- [Chapter 9: High Level Language](./chapter09) - Implementation of Snake in Jack
- [Chapter 10: Compiler I](./chapter10) - Syntax Analysis

Future chapters to be implemented:
- Chapter 11: Compiler
- Chapter 12: Operating System

## Testing

All implementations are tested using the web-based tools available at [nand2tetris.github.io/web-ide/chip](https://nand2tetris.github.io/web-ide/chip). This provides an integrated development and testing environment that works directly in the browser, requiring no local software installation.

The web IDE provides:
- Hardware simulator for testing `.hdl` files (Chapters 1-5)
- CPU Emulator for testing assembly (`.asm`) programs (Chapter 4)
- VM Emulator for testing VM (`.vm`) implementations (Chapters 7-8)
- Jack Compiler for compiling Jack files (`.jack`) into VM files (`.vm`)
- Built-in test scripts and comparison files

## Resources

- [Official Nand2Tetris Website](https://www.nand2tetris.org/)
- [Nand2Tetris Web IDE](https://nand2tetris.github.io/web-ide/chip)