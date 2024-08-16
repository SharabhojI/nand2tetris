// Chip name: HALFADDER
// Input(s): a, b
// Output(s): sum, carry
// Function: sum   = LSB of a + b
//           carry = MSB of a + b
`timescale 1ns / 1ps

`include "../../chapter01/src/AND.v"
`include "../../chapter01/src/XOR.v"

module HALFADDER (
    input a, b,
    output sum, carry
);
    AND and_gate(
        .a(a),
        .b(b),
        .out(carry)
    );
    XOR xor_gate(
        .a(a),
        .b(b),
        .out(sum)
    );
endmodule