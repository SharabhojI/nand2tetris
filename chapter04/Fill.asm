// Program: Fill.asm
// Computes: Writes black to every pixel when any key is pressed, else writes white
// Usage: Press any key on the keyboard
(LOOP)
    // Read KBD Value
    @KBD
    D=M
    // if (KBD > 0) goto BLACK
    @BLACK
    D;JGT
    // else, goto WHITE
    @WHITE
    0;JMP // unconditional jump
(BLACK)
    // set color to black
    @color
    M=-1
    // jump to draw
    @DRAW
    0;JMP
(WHITE)
    // set color to white
    @color
    M=0
(DRAW)
    // initialize pointer to pixel word segment
    @SCREEN
    D=A
    @pointer
    M=D
    // initialize counter for pixel word segments
    @8192
    D=A
    @counter
    M=D
(FILL)
    // if (counter == 0) goto LOOP
    @counter
    D=M
    @LOOP
    D;JEQ
    // fill word segment with color
    @color
    D=M
    @pointer
    A=M
    M=D
    // increment to next word
    @pointer
    M=M+1
    // decrement counter
    @counter
    M=M-1
    // continue loop
    @FILL
    0;JMP
(END)
    @END
    0;JMP