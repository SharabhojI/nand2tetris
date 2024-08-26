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

module RAM64 (
    input [15:0] in,
    input [5:0] address,
    input load, clk,
    output [15:0] out
);
    wire [7:0] ram_in;
    wire [15:0] ram_out [7:0];

    DMUX8WAY dmux (
        .in(load),
        .sel(address[5:3]),
        .a(ram_in[0]),
        .b(ram_in[1]),
        .c(ram_in[2]),
        .d(ram_in[3]),
        .e(ram_in[4]),
        .f(ram_in[5]),
        .g(ram_in[6]),
        .h(ram_in[7])
    );

    genvar i;
    generate
        for (i = 0; i < 8; i = i + 1) begin : ram_chips
            RAM8 ram_chip (
                .in(in),
                .address(address[2:0]),
                .load(ram_in[i]),
                .clk(clk),
                .out(ram_out[i])
            );
        end
    endgenerate

    MUX8WAY16 mux (        
        .a(ram_out[0]),
        .b(ram_out[1]),
        .c(ram_out[2]),
        .d(ram_out[3]),
        .e(ram_out[4]),
        .f(ram_out[5]),
        .g(ram_out[6]),
        .h(ram_out[7]),
        .sel(address[5:3]),
        .out(out)
    );
endmodule