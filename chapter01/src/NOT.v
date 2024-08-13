// Chip name: NOT
// Input(s): in
// Output: out
// Function: if (in==0) then out = 1, else out = 0
module NOT (
    input in,
    output out
);
    NAND nand_gate (
        .a(in),
        .b(in),
        .out(out)
    );
endmodule