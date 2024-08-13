// Chip name: MUX
// Input(s): a, b, sel
// Output: out
// Function: if (sel==0) then out = a, else out = b
module MUX (
    input a, b, sel,
    output out
);
    wire nots, and1, and2;
    NOT not_s (
        .in(sel),
        .out(nots)
    );
    AND and_1 (
        .a(a),
        .b(nots),
        .out(and1)
    );
    AND and_2 (
        .a(b),
        .b(sel),
        .out(and2)
    );
    OR or_gate (
        .a(and1),
        .b(and2),
        .out(out)
    );
endmodule