// Chip name: MUX8WAY16
// Input(s): a[16], b[16], c[16], d[16], e[16], f[16], g[16], h[16], sel[3]
// Output: out[16]
// Function: if (sel == 000, 001, 010, ..., or 111) 
//           then out = a, b, c, d, ..., or h
// Comment: The assingment is a 16-bit operation.
//          For example, "out = a" means "for i = 0..15 out[i] = a[i]".
module MUX8WAY16 (
    input [15:0] a, [15:0] b, [15:0] c, [15:0] d, [15:0] e, [15:0] f, [15:0] g, [15:0] h,
    input [2:0] sel, 
    output [15:0] out
);
    wire [15:0] ab, cd, ef, gh, abcd, efgh;
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
        .a(e),
        .b(f),
        .sel(sel[0]),
        .out(ef)
    );
    MUX16 mux_4 (
        .a(g),
        .b(h),
        .sel(sel[0]),
        .out(gh)
    );
    MUX16 mux_5 (
        .a(ab),
        .b(cd),
        .sel(sel[1]),
        .out(abcd)
    );
    MUX16 mux_6 (
        .a(ef),
        .b(gh),
        .sel(sel[1]),
        .out(efgh)
    );
    MUX16 mux_7 (
        .a(abcd),
        .b(efgh),
        .sel(sel[2]),
        .out(out)
    );
endmodule