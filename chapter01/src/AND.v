// Chip name: AND
// Input(s): a, b
// Output: out
// Function: if ((a==1) and (b==1)) then out = 1, else out = 0
module AND (
    input a, b,
    output out
);
    wire intermediate; 

    NAND nand_gate (
        .a(a),
        .b(b),
        .out(intermediate)
    );
    NOT not_gate (
        .in(intermediate),
        .out(out)
    );
endmodule