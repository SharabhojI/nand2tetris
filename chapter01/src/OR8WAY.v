// Chip name: OR8WAY
// Input(s): in[8]
// Output: out
// Function: out = OR(in[0], in[1], ..., in[7])
module OR8WAY (
    input [7:0] in,
    output out
);
    wire a, b, c, d, e, f;
    OR or_1 (
        .a(in[0]),
        .b(in[1]),
        .out(a)
    );
    OR or_2 (
        .a(in[2]),
        .b(in[3]),
        .out(b)
    );
    OR or_3 (
        .a(in[4]),
        .b(in[5]),
        .out(c)
    );
    OR or_4 (
        .a(in[6]),
        .b(in[7]),
        .out(d)
    );
    OR or_5 (
        .a(a),
        .b(b),
        .out(e)
    );
    OR or_6 (
        .a(c),
        .b(d),
        .out(f)
    );
    OR or_7 (
        .a(e),
        .b(f),
        .out(out)
    );
endmodule