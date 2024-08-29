// Chip name: SCREEN
// Input(s): in[16], address[13], load
// Output: out[16]
// Function: Exactly like a 16-bit, 8K RAM, plus refresh side effect.
// Emits the value stored at the memory location specified by address.
// If load==1, then the memory location specified by address is set to the value of in.
// The loaded value will be emitted by out from the next time step onward.
// In addition, the chip continuously refreshes a physical screen, consisting of 256 rows
// and 512 columns of black and white pixels.
// The pixel at row r from the top and column c from the left (0<=r<=255, 0<=c<=511)
// is mapped onto the c%16 bit (counting from LSB to MSB) of the 16-bit word stored
// in SCREEN[r * 32 + c / 16].
`timescale 1ns / 1ps

module SCREEN (
    input [15:0] in,
    input [12:0] address,
    input load, clk,
    output [15:0] out
);
    // 8K 16-bit memory (2^13 addresses = 8192)
    reg [15:0] memory [0:8191];

    // asynchronous read operation
    always @(*) begin
        out = memory[address];
    end

    // synchronous write operation
    always @(posedge clk) begin
        if (load) begin
            memory[address] <= in;
        end
    end
endmodule

// NOTE: For the purposes of this project, the implementation
//       of SCREEN is treated as a primivite or 'black box' 
//       abstraction.