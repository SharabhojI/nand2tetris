# Chapter 5: Computer Architecture

This folder contains the implementation of the computer architecture chips described in Chapter 5 of "The Elements of Computing Systems" (also known as "Nand to Tetris").

## Contents

- **src/**: Folder containing Verilog (`.v`) implementations of the chips

### Source Files (/src/)
The `src` folder contains Verilog (`.v`) implementations of the following chips:

- MEMORY
- CPU
- COMPUTER

## Implementation Notes

1. Some chips in this chapter (SCREEN, KEYBOARD, ROM32K) are treated as black box abstractions due to their complexity.

2. The RAM16K module, used as a component in the MEMORY chip, is implemented exactly as it was in Chapter 3, despite the testing challenges encountered there.

3. Due to the complexity of these chips and the black box nature of some components, traditional testbench-based testing is not implemented for this chapter.

## Verification

While formal testbench-based testing is not implemented for this chapter, the correctness of these chips can be verified through:

1. Code review: Carefully examining the Verilog implementations to ensure they match the specifications provided in the textbook.

2. Integration testing: Using these chips as components in larger systems (such as in subsequent chapters) to verify their behavior indirectly.

3. Simulation with simplified inputs: Where possible, running simple simulations with reduced complexity to check basic functionality.

## Known Limitations

1. The lack of comprehensive testbenches means that full verification of these chips' behavior under all possible inputs is not available.

2. The testing challenges encountered with RAM16K in Chapter 3 persist in this chapter, as it is a component of the MEMORY chip.

These limitations reflect the challenges of implementing and testing complex computer architectures, especially when dealing with large memory structures and intricate designs.