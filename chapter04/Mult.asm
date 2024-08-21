// Program: Mult.asm
// Computes: RAM[2] = RAM[0] x RAM[1]
// Usage: put values in RAM[0] and in RAM[1]
    // sum = 0
    @sum
    M=0
(LOOP)
    // if (R1 = 0) goto STOP
    @R1
    D=M
    @STOP
    D;JEQ
    // sum = sum + R0
    @R0
    D=M
    @sum
    M=D+M
    // R1 = R1 - 1
    @R1
    M=M-1
    // repeat loop
    @LOOP
    0;JMP
(STOP)
    // R2 = sum
    @sum
    D=M 
    @R2
    M=D
(END)
    @END
    0;JMP