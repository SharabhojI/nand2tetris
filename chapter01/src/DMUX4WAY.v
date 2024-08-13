// Chip name: DMUX4WAY
// Input(s): in, sel[2]
// Output(s): a, b, c, d
// Function: if (sel==00)      then {a, b, c, d} = {1, 0, 0, 0},
//           else if (sel==01) then {a, b, c, d} = {0, 1, 0, 0},
//           else if (sel==10) then {a, b, c, d} = {0, 0, 1, 0},
//           else if (sel==11) then {a, b, c, d} = {0, 0, 0, 1}
module DMUX4WAY (
    input in, 
    input [1:0] sel,
    output a, b, c, d
);
    wire out1, out2;
    DMUX dmux_1 (
        .in(in),
        .sel(sel[1]),
        .a(out1),
        .b(out2)
    );
    DMUX dmux_2 (
        .in(out1),
        .sel(sel[0]),
        .a(a),
        .b(b)
    );
    DMUX dmux_3 (
        .in(out2),
        .sel(sel[0]),
        .a(c),
        .b(d)
    );
    
endmodule