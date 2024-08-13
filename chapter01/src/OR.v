// Chip name: OR
// Input(s): a, b
// Output: out
// Function: if ((a==0) and (b==0)) then out = 0, else out = 1
module OR (
    input a, b,
    output out
);
    wire nota, notb, intermediate;
    NOT not_a (
        .in(a),
        .out(nota)
    );
    NOT not_b (
        .in(b),
        .out(notb)
    );
    AND and_gate (
        .a(nota),
        .b(notb),
        .out(intermediate)
    );
    NOT not_gate (
        .in(intermediate),
        .out(out)
    );
endmodule