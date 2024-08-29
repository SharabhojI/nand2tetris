// Chip name: ROM32K (instruction memory)
// Input: address[15]
// Output: out[16]
// Function: Emits the 16-bit value stored in the address selected by the
//           address input. It is assumed that the chip is preloaded
//           with a program written in the Hack machine language. 
`timescale 1ns / 1ps

module ROM32K (
    input clk,
    input [14:0] address,
    output [15:0] out
);
    // Internal memory array
    reg [15:0] memory [0:32767];  // 32K locations of 16-bit words

    // Asynchronous read operation
    always @(*) begin
        out = memory[address];
    end
endmodule

// NOTE: For the purposes of this project, the ROM32K implementation
//       is treated as a primivite or 'black box' abstraction. The 
//       actual preloading of the program is assumed to happen outside 
//       of this module, as per the chip description.