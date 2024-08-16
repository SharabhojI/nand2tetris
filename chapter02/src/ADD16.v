// Chip name: ADD16
// Input(s): a[16], b[16]
// Output: out[16]
// Function: Adds two 16-bit numbers.
//           The overflow bit is ignored.
`timescale 1ns / 1ps

module ADD16 (
    input [15:0] a, [15:0] b,
    output [15:0] out
);
    wire [14:0] carry_bits;

    // LSB
    FULLADDER adder_0 (
      .a(a[0]), 
      .b(b[0]),
      .c(1'b0), // No carry-in for first adder (1-bit binary zero) 
      .sum(out[0]),
      .carry(carry_bits[0])  
    );

    genvar i;
    generate
        for (i = 1; i < 15; i = i + 1) begin : adder_loop
            FULLADDER adder (
                .a(a[i]),
                .b(b[i]),
                .c(carry_bits[i-1]),
                .sum(out[i]),
                .carry(carry_bits[i])
            );
        end
    endgenerate

    // MSB
    FULLADDER adder_15 (
        .a(a[15]),
        .b(b[15]),
        .c(carry_bits[14]),
        .sum(out[15]),
        .carry() // Final carry-out ignored
    );
endmodule