// Chip name: NAND
// Input(s): a, b
// Output: out
// Function: if ((a==1) and (b==1)) then out = 0, else out = 1
module NAND (
    input a, b,
    output out
);
    assign out = ~(a & b);
endmodule