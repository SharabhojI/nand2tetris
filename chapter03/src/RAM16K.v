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

`include "../../chapter01/src/DMUX4WAY.v"
`include "../../chapter01/src/MUX4WAY16.v"

module RAM16K (
    input [15:0] in,
    input [13:0] address,
    input load, clk,
    output [15:0] out
);

    wire [3:0] ram_in;
    wire [15:0] ram_out [3:0];

    DMUX4WAY dmux (
        .in(load),
        .sel(address[13:12]),
        .a(ram_in[0]),
        .b(ram_in[1]),
        .c(ram_in[2]),
        .d(ram_in[3])
    );

    genvar i;
    generate
        for (i = 0; i < 4; i = i + 1) begin : ram_chips
            RAM4K ram_chip (
                .in(in),
                .address(address[11:0]),
                .load(ram_in[i]),
                .clk(clk),
                .out(ram_out[i])
            );
        end
    endgenerate
    
    MUX4WAY16 mux (        
        .a(ram_out[0]),
        .b(ram_out[1]),
        .c(ram_out[2]),
        .d(ram_out[3]),
        .sel(address[13:12]),
        .out(out)
    );
endmodule