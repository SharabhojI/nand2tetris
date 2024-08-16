// Chip name: ALU
// Input(s):   x[16], y[16],  (16-bit data inputs)
//             zx,            (Zero the x input)
//             nx,            (Negate the x input)
//             zy,            (Zero the y input)
//             ny,            (Negate the y input)
//             f,             (if f==1 out=add(x,y) else out=and(x,y))
//             no             (Negate the out output)
// Output(s):  out[16],       (16-bit output)
//             zr,            (if out==0 zr=1 else zr=0)
//             ng             (if out<0 ng=1 else ng=0)
// Function:
//             if zx x=0      (16-bit zero constant)
//             if nx x=!x     (Bit-wise negation)
//             if zy y=0      (16-bit zero constant)
//             if ny y=!y     (Bit-wise negation)
//             if f out=x+y   (Integer two's complement addition)
//             else out=x&y   (Bit-wise And)
//             if no out=!out (Bit-wise negation)
//             if out==0 zr=1 else zr=0  (16-bit equality comparison)
//             if out<0 ng=1  else ng=0  (two's complement comparison)
// Comment:    The oveflow bit is ignored.
`timescale 1ns / 1ps

`include "../../chapter01/src/MUX16.v"
`include "../../chapter01/src/AND16.v"
`include "../../chapter01/src/OR8WAY.v"
`include "../../chapter01/src/OR.v"
`include "../../chapter01/src/NOT16.v"
`include "../../chapter01/src/NOT.v"
module ALU (
    input [15:0] x, y,
    input zx, nx, zy, ny, f, no,
    output [15:0] out,
    output zr, ng 
);
    wire [15:0] x1, y1, x2, y2, notx1, noty1, xandy, xplusy, xy, notxy;
    wire or1, or2, or3;

    MUX16 mux_x1 (
        .a(x),
        .b(16'd0),
        .sel(zx),
        .out(x1)
    );
    MUX16 mux_y1 (
        .a(y),
        .b(16'd0),
        .sel(zy),
        .out(y1)
    );
    
    NOT16 not_x1 (
        .in(x1),
        .out(notx1)
    );
    NOT16 not_y1 (
        .in(y1),
        .out(noty1)
    );
    MUX16 mux_x2 (
        .a(x1),
        .b(notx1),
        .sel(nx),
        .out(x2)
    );
    MUX16 mux_y2 (
        .a(y1),
        .b(noty1),
        .sel(ny),
        .out(y2)
    );

    AND16 and_gate (
        .a(x2),
        .b(y2),
        .out(xandy)
    );
    ADD16 adder (
        .a(x2),
        .b(y2),
        .out(xplusy)
    );
    MUX16 mux_xy (
        .a(xandy),
        .b(xplusy),
        .sel(f),
        .out(xy)
    );

    NOT16 not_xy (
        .in(xy),
        .out(notxy)
    );
    MUX16 mux_out (
        .a(xy),
        .b(notxy),
        .sel(no),
        .out(out)
    );
    assign ng = out[15];
    OR8WAY port1 (
        .in(out[7:0]),
        .out(or1)
    );
    OR8WAY port2 (
        .in(out[15:8]),
        .out(or2)
    );
    OR or_gate (   
        .a(or1),
        .b(or2),
        .out(or3)
    );
    NOT not_or3 (
        .in(or3),
        .out(zr)
    );

    // Debugging
    always @* begin
        $display("ALU: x=%h, y=%h, zx=%b, nx=%b, zy=%b, ny=%b, f=%b, no=%b", x, y, zx, nx, zy, ny, f, no);
        $display("ALU: x1=%h, y1=%h, notx1=%h, noty1=%h", x1, y1, notx1, noty1);
        $display("ALU: x2=%h, y2=%h", x2, y2);
        $display("ALU: xandy=%h, xplusy=%h, xy=%h, notxy=%h", xandy, xplusy, xy, notxy);
        $display("ALU: out=%h, zr=%b, ng=%b", out, zr, ng);
        $display("ALU: or1=%b, or2=%b, or3=%b", or1, or2, or3);
    end

endmodule