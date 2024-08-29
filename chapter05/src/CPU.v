// Chip name: CPU
// Input: instruction[16], inM[16], reset
// Output: outM[16], addressM[15], writeM, pc[15]
// Function: Designed to fetch and execute instructions written 
//           in the Hack machine language. If instruction is an
//           A-instruction, the CPU loads the 16-bit constant
//           into the A register.  If instruction is a C-instruction,
//           then (i) the CPU causes the ALU to perform the computation
//           specified by the instruction, and (ii) the CPU causes this
//           value to be stored in the subset of {A,D,M} registers
//           specified by the instruction. If one of these registers is
//           M, the CPU asserts the writeM control bit output (when 
//           writeM	is 0, any value may appear in outM). When the reset	
//           input is 0, the CPU uses the ALU output and the jump 
//           directive specified by the instruction to compute the address 
//           of the next instruction, and emits this address to the pc 
//           output. If the reset input	is 1, the CPU sets pc to 0. The
//           outM and writeM outputs are combinational, and are affected 
//           instantaneously by the instruction’s execution. The addressM 
//           and pc outputs are clocked: although they are affected by 
//           the instruction’s execution, they commit to their new values
//           only in the next time step.
`timescale 1ns / 1ps

`include "../../chapter01/src/MUX16.v"
`include "../../chapter03/src/REGISTER.v"
`include "../../chapter02/src/ALU.v"
`include "../../chapter03/src/PC.v"

module CPU (
    input [15:0] instruction, inM,
    input reset, clk,
    output [15:0] outM,
    output [14:0] addressM, pc,
    output writeM
);

    wire [15:0] inst_mux_out, in_mux_out, a_reg_out, d_reg_out;
    wire zr, ng, jump, pc_load, a_load, d_load;

    MUX16 inst_mux (
        .a(outM),
        .b(instruction),
        .sel(instruction[15]),
        .out(inst_mux_out)
    );

    assign a_load = (!instruction[15]) | (instruction[5] & instruction[15]);
    REGISTER a_register (
        .in(inst_mux_out),
        .load(a_load),
        .clk(clk),
        .out(a_reg_out)
    );
    assign d_load = instruction[4] & instruction[15];
    REGISTER d_register (
        .in(outM),
        .load(d_load),
        .clk(clk),
        .out(d_reg_out)
    );
    MUX16 in_mux (
        .a(a_reg_out),
        .b(inM),
        .sel(instruction[15]),
        .out(in_mux_out)
    );

    assign jump = (instruction[2] & ng) | (instruction[1] & zr) | (instruction[0] & (!ng & !zr));
    assign pc_load = jump & instruction[15];
    PC prog_counter (
        .in(a_reg_out),
        .load(pc_load),
        .inc(1'b1),
        .reset(reset),
        .clk(clk),
        .out(pc)
    );
    ALU alu (
        .x(d_reg_out),
        .y(in_mux_out),
        .zx(instruction[11]),
        .nx(instruction[10]),
        .zy(instruction[9]),
        .ny(instruction[8]),
        .f(instruction[7]),
        .no(instruction[6]),
        .out(outM),
        .zr(zr),
        .ng(ng)
    );

    assign writeM = instruction[3] & instruction[15];
    assign addressM = a_reg_out;
endmodule