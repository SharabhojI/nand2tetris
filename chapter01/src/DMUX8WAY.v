// Chip name: DMUX8WAY
// Input(s): in, sel[3]
// Output(s): a, b, c, d, e, f, g, h
// Function: if (sel==000)      then {a, b, c, ..., h} = {1, 0, 0, 0, 0, 0, 0, 0},
//           else if (sel==001) then {a, b, c, ..., h} = {0, 1, 0, 0, 0, 0, 0, 0},
//           else if (sel==010) then {a, b, c, ..., h} = {0, 0, 1, 0, 0, 0, 0, 0},
//           ...
//           else if (sel==111) then {a, b, c, ..., h} = {0, 0, 0, 0, 0, 0, 0, 1}
module DMUX8WAY (
    input in, 
    input [2:0] sel,
    output a, b, c, d, e, f, g, h
);
    wire out1, out2, out3, out4, out5, out6;
    DMUX dmux_1 (
        .in(in),
        .sel(sel[2]),
        .a(out1),
        .b(out2)
    );
    DMUX dmux_2 (
        .in(out1),
        .sel(sel[1]),
        .a(out3),
        .b(out4)
    );
    DMUX dmux_3 (
        .in(out2),
        .sel(sel[1]),
        .a(out5),
        .b(out6)
    );
    DMUX dmux_4 (
        .in(out3),
        .sel(sel[0]),
        .a(a),
        .b(b)
    );
    DMUX dmux_5 (
        .in(out4),
        .sel(sel[0]),
        .a(c),
        .b(d)
    );
    DMUX dmux_6 (
        .in(out5),
        .sel(sel[0]),
        .a(e),
        .b(f)
    );
    DMUX dmux_7 (
        .in(out6),
        .sel(sel[0]),
        .a(g),
        .b(h)
    );
    
endmodule