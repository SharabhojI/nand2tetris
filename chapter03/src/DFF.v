// Chip name: DFF
// Input(s): in
// Output: out
// Function: out(t+1) = in(t)
`timescale 1ns / 1ps

module DFF (
    input in, clk,
    output reg out
);
    always @(posedge clk) begin
        out <= in; // non-blocking assignment for sequential logic
    end
endmodule