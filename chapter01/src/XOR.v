// Chip name: XOR
// Input(s): a, b
// Output: out
// Function: if ((a!=b) then out = 1, else out = 0
module XOR (
    input a, b,
    output out
);
    wire nota, notb, and1, and2;    
    NOT not_a (
        .in(a),
        .out(nota)
    );
    NOT not_b (
        .in(b),
        .out(notb)
    );
    AND and_1 (
        .a(a),
        .b(notb),
        .out(and1)
    );
    AND and_2 (
        .a(nota),
        .b(b),
        .out(and2)
    );
    OR or_gate (
        .a(and1),
        .b(and2),
        .out(out)
    );
endmodule