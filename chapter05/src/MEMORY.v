// Chip name: MEMORY (data memory)
// Input: in[16], address[15], load
// Output: out[16]
// Function: 
//    The complete address space of the Hack computer's data memory.
//    Only the top 16K+8K+1 words of the address space are used.
//    Accessing an address in the range 0-16383 results in accessing RAM16K;
//    Accessing an address in the range 16384-24575 results in accessing SCREEN;
//    Accessing the address 24576 results in accessing KEYBOARD;
//    Accessing any other address is invalid.
`timescale 1ns / 1ps

`include "../../chapter01/src/OR.v"
`include "../../chapter01/src/DMUX4WAY.v"
`include "../../chapter01/src/MUX4WAY16.v"
`include "../../chapter03/src/RAM16K.v"

module MEMORY (
    input [15:0] in,
    input [14:0] address,
    input load, clk,
    output [15:0] out
);
    wire a, b, c, d, or_out;
    wire [15:0] kbd_out, scn_out, ram_out;

    DMUX4WAY dmux (
        .in(load),
        .sel(address[14:13]),
        .a(a),
        .b(b),
        .c(c),
        .d(d)
    );
    OR or_gate (
        .a(a),
        .b(b),
        .out(or_out)
    );
    RAM16K ram (
        .in(in),
        .address(address[13:0]),
        .load(or_out),
        .clk(clk),
        .out(ram_out)
    );
    SCREEN screen (
        .in(in),
        .address(address[12:0]),
        .load(c),
        .clk(clk),
        .out(scn_out)
    );
    KEYBOARD keyboard (
        .clk(clk),
        .out(kbd_out)
    );
    MUX4WAY16 mux (
        .a(ram_out),
        .b(ram_out),
        .c(scn_out),
        .d(kbd_out),
        .out(out)
    );
endmodule