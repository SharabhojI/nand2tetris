// Chip name: PC (Program Counter)
// Input(s): in[16], load, inc, reset
// Output: out[16]
// Function: 16-bit counter
// if reset(t)      out(t+1) = 0
// else if load(t)  out(t+1) = in(t)
// else if inc(t)   out(t+1) = out(t) + 1 (integer addition)
// else             out(t+1) = out(t)
`timescale 1ns / 1ps

`include "../../chapter01/src/MUX16.v"
`include "../../chapter02/src/INC16.v"

module PC (
    input [15:0] in,
    input load, inc, reset, clk,
    output [15:0] out
);
    wire [15:0] inc_out, inc_mux_out, load_mux_out, reset_mux_out;

    INC16 inc16 (
        .in(out),
        .out(inc_out)
    );
    MUX16 inc_mux (
        .a(out),
        .b(inc_out),
        .sel(inc),
        .out(inc_mux_out)
    );
    MUX16 load_mux (
        .a(inc_mux_out),
        .b(in),
        .sel(load),
        .out(load_mux_out)
    );
    MUX16 reset_mux (
        .a(load_mux_out),
        .b(16'b0),
        .sel(reset),
        .out(reset_mux_out)
    );
    REGISTER register (
        .in(reset_mux_out),
        .load(1'b1),
        .clk(clk),
        .out(out)
    );    
endmodule