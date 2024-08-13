// Chip name: DMUX
// Input(s): in, sel
// Output(s): a, b
// Function: if (sel==0) then {a, b} = {in, 0}
//           else             {a, b} = {0, in}
module DMUX (
    input in, sel,
    output a, b
);
    wire nots;
    NOT not_s (
        .in(sel),
        .out(nots)
    );
    AND and_1 (
        .a(in),
        .b(sel),
        .out(b)
    );
    AND and_2 (
        .a(in),
        .b(nots),
        .out(a)
    );
endmodule