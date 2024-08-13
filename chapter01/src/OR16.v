// Chip name: OR16
// Input(s): a[16], b[16]
// Output: out[16]
// Function: for i = 0..15 out[i] = OR(a[i], b[i])
module OR16 (
    input [15:0] a, [15:0] b,
    output [15:0] out
);
    genvar i;
    generate
        for(i = 0; i < 16; i = i + 1) begin : or_gates
            OR or_gate (
                .a(a[i]),
                .b(b[i]),
                .out(out[i])
            );
        end
    endgenerate    
endmodule