// Chip name: COMPUTER
// Input: reset
// Function: 
//    When reset==0, the program stored in the computer executes.
//    When reset==1, the execution of the program restarts.
//    To start the program's execution, set reset to 1, and then to 0.
//    (It is assumed that the computer's instruction memory is loaded
//    with a program written in the Hack machine language).
`timescale 1ns / 1ps

module COMPUTER (
    input reset, clk
);
    wire [15:0] instruction, inM, outM;
    wire [14:0] pc, addressM;
    wire writeM;

    ROM32K rom (
        .clk(clk),
        .address(pc),
        .out(instruction)
    );
    CPU processor (
        .instruction(instruction),
        .inM(inM),
        .reset(reset),
        .clk(clk),
        .outM(outM),
        .addressM(addressM),
        .pc(pc),
        .writeM(writeM)
    );
    MEMORY mem (
        .in(outM),
        .address(addressM),
        .load(writeM),
        .clk(clk),
        .out(inM)
    );
endmodule