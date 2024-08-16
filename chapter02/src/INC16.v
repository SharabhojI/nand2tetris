// Chip name: INC16
// Input(s): in[16]
// Output(s): out[16]
// Function: out = in + 1
// Comment: The overflow bit is ignored.
`timescale 1ns / 1ps

module INC16 (
    input [15:0] in,
    output [15:0] out
);
    wire [14:0] carry_bits; // 15 carry bits to connect half-adders

    // Initial half-adder for LSB
    HALFADDER halfadder_0 (
        .a(in[0]),
        .b(1'b1), // Adding 1 to the least significant bit
        .sum(out[0]),
        .carry(carry_bits[0])
    );

    // Generate 14 additional half-adders in the loop
    genvar i;
    generate
        for (i = 1; i < 15; i = i + 1) begin : halfadder_loop
            HALFADDER halfadder (
                .a(in[i]),
                .b(carry_bits[i-1]),
                .sum(out[i]),
                .carry(carry_bits[i])
            );
        end
    endgenerate 

    // Final half-adder for MSB
    HALFADDER halfadder_15 (
        .a(in[15]),
        .b(carry_bits[14]),
        .sum(out[15]),
        .carry(carry_bits[15]) // capture overflow bit
    );

    // Debugging
    always @* begin
        $display("INC16: in=%h, out=%h", in, out);
        $display("INC16: carry_bits=%b", carry_bits);
        $display("INC16: halfadder_0: a=%b, b=%b, sum=%b, carry=%b", in[0], 1'b1, out[0], carry_bits[0]);
        $display("INC16: halfadder_15: a=%b, b=%b, sum=%b", in[15], carry_bits[14], out[15]);
    end
endmodule
