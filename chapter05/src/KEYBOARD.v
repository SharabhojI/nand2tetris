// Chip name: KEYBOARD
// Output: out[16]
// Function: Emit the 16-bit character code of the currently pressed
//           key on the physical keyboard or 0 if no key is pressed.
`timescale 1ns / 1ps

module KEYBOARD (
    input clk,
    output [15:0] out
);
    // Internal register to hold the current key code
    reg [15:0] key_code;

    // Output the current key code
    always @(posedge clk) begin
        out <= key_code;
    end
endmodule

// NOTE: Due to its complexity, the implementation of KEYBOARD
//       is treated as a primitive or a 'black box' abstraction
//       for the purposes of this project.