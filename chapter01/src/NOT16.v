// Chip name: NOT16
// Input(s): in[16]
// Output: out[16]
// Function: for i = 0..15 out[i] = NOT(in[i])
module NOT16 (
    input [15:0] in,
    output [15:0] out
);
    genvar i;
    generate
        for(i = 0; i < 16; i = i + 1) begin : not_gates
        NOT not_gate (
            .in(in[i]),
            .out(out[i])
        );
        end
    endgenerate
endmodule