// Chip name: MUX4WAY16
// Input(s): a[16], b[16], c[16], d[16], sel[2]
// Output: out[16]
// Function: if (sel == 00, 01, 10, or 11) then out = a, b, c, or d
// Comment: The assingment is a 16-bit operation.
//          For example, "out = a" means "for i = 0..15 out[i] = a[i]".
module MUX4WAY16 (
    input [15:0] a, [15:0] b, [15:0] c, [15:0] d,
    input [1:0] sel, 
    output [15:0] out
);
    wire [15:0] ab, cd;
    MUX16 mux_1 (
        .a(a),
        .b(b),
        .sel(sel[0]),
        .out(ab)
    );
    MUX16 mux_2 (
        .a(c),
        .b(d),
        .sel(sel[0]),
        .out(cd)
    );
    MUX16 mux_3 (
        .a(ab),
        .b(cd),
        .sel(sel[1]),
        .out(out)
    );
endmodule