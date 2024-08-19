// Chip name: BIT (1-bit register)
// Input(s): in, load
// Output: out
// Function: if load(t) then out(t+1) = in(t)
//           else            out(t+1) = out(t)
`timescale 1ns / 1ps

`include "../../chapter01/src/MUX.v"

module BIT (
    input in, load, clk,
    output out
);
    wire mux_out;
    MUX mux (
        .a(out), 
        .b(in), 
        .sel(load),
        .out(mux_out)
    );
    DFF dff (
        .in(mux_out),
        .clk(clk),
        .out(out)
    ); 
endmodule