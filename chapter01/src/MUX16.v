// Chip name: MUX16
// Input(s): a[16], b[16], sel
// Output: out[16]
// Function: if (sel==0) then for i = 0..15 out[i] = a[i],
//           else for i = 0..15 out[i] = b[i]
module MUX16 (
    input [15:0] a, [15:0] b, 
    input sel,
    output [15:0] out
);
    genvar i;
    generate
        for(i = 0; i < 16; i = i + 1) begin : mux_gates
            MUX mux_gate (
                .a(a[i]),
                .b(b[i]),
                .sel(sel),
                .out(out[i])
            );          
        end
    endgenerate
endmodule