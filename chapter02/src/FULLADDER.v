// Chip name: FULLADDER
// Input(s): a, b, c
// Output(s): sum, carry
// Function: sum   = LSB of a + b + c
//           carry = MSB of a + b + c
`timescale 1ns / 1ps

`include "../../chapter01/src/OR.v"

module FULLADDER (
    input a, b, c,
    output sum, carry
);
    wire add1_sum, add1_carry, add2_carry;
    HALFADDER adder_1 (
        .a(a),
        .b(b),
        .sum(add1_sum),
        .carry(add1_carry)
    );
    HALFADDER adder_2 (
        .a(add1_sum),
        .b(c),
        .sum(sum),
        .carry(add2_carry)
    );
    OR or_gate (
        .a(add2_carry),
        .b(add1_carry),
        .out(carry)
    );
endmodule