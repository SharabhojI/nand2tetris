// Chip name: RAMn
// Input(s): in[16], load, address[k] (k=log2n)
// Output: out[16]
// Function:
// Out emits the value stored at the memory location
// (register) specified by address. If load == 1, then the
// memory location specified by address is set to the
// value of in. The loaded value will be emitted by
// out from the next step onward.
`timescale 1ns / 1ps

`include "../../chapter01/src/DMUX8WAY.v"
`include "../../chapter01/src/MUX8WAY16.v"

module RAM8 (
    input [15:0] in,
    input [2:0] address,
    input load, clk,
    output [15:0] out
);
    wire [7:0] register_in; 
    wire [15:0] register_out [7:0];
    DMUX8WAY dmux (
        .in(load),
        .sel(address),
        .a(register_in[0]),
        .b(register_in[1]),
        .c(register_in[2]),
        .d(register_in[3]),
        .e(register_in[4]),
        .f(register_in[5]),
        .g(register_in[6]),
        .h(register_in[7])
    );

    genvar i;
    generate
        for (i = 0; i < 8; i = i + 1) begin : registers
            REGISTER register (
                .in(in),
                .load(register_in[i]),
                .clk(clk),
                .out(register_out[i])
            );
        end
    endgenerate

    MUX8WAY16 mux (        
        .a(register_out[0]),
        .b(register_out[1]),
        .c(register_out[2]),
        .d(register_out[3]),
        .e(register_out[4]),
        .f(register_out[5]),
        .g(register_out[6]),
        .h(register_out[7]),
        .sel(address),
        .out(out)
    );
endmodule