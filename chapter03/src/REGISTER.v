// Chip name: REGISTER (16-bit register)
// Input(s): in[16], load
// Output: out[16]
// Function: if load(t) then out(t+1) = in(t)
//           else            out(t+1) = out(t)
// Comment:  "=" is a 16-bit operation.
`timescale 1ns / 1ps

`include "../../chapter01/src/MUX16.v"

module REGISTER (
    input [15:0] in, 
    input load, clk,
    output [15:0] out
);
    wire [15:0] mux_out;
    MUX16 mux (
        .a(out), 
        .b(in), 
        .sel(load),
        .out(mux_out)
    );

    genvar i;
    generate
        for (i = 0;  i < 16; i = i + 1) begin : bit_registers
            BIT bit_register (
                .in(mux_out[i]),
                .load(load),
                .clk(clk),
                .out(out[i])
            );
        end
    endgenerate
endmodule