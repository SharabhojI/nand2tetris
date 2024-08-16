// ALU_tb.v
`timescale 1ns / 1ps

module ALU_tb();
    reg [15:0] x, y;
    reg zx, nx, zy, ny, f, no;
    wire [15:0] out;
    wire zr, ng;

    ALU uut (
        .x(x), .y(y),
        .zx(zx), .nx(nx), .zy(zy), .ny(ny), .f(f), .no(no),
        .out(out), .zr(zr), .ng(ng)
    );

    task checkALU;
        input [15:0] expectedOut;
        input expectedZr, expectedNg;
        begin
            #1; // Add a small delay to allow for propagation
            if (out !== expectedOut || zr !== expectedZr || ng !== expectedNg)
                $display("Error at time %0t: x=%h, y=%h, zx=%b, nx=%b, zy=%b, ny=%b, f=%b, no=%b, out=%h (expected %h), zr=%b (expected %b), ng=%b (expected %b)",
                        $time, x, y, zx, nx, zy, ny, f, no, out, expectedOut, zr, expectedZr, ng, expectedNg);
            else
                $display("Correct at time %0t: x=%h, y=%h, zx=%b, nx=%b, zy=%b, ny=%b, f=%b, no=%b, out=%h, zr=%b, ng=%b",
                        $time, x, y, zx, nx, zy, ny, f, no, out, zr, ng);
        end
    endtask

    initial begin
        $dumpfile("ALU_tb.vcd");
        $dumpvars(0, ALU_tb);

        // Test basic operations
        x = 16'h0009; y = 16'h0005;
        
        // x AND y
        {zx, nx, zy, ny, f, no} = 6'b000000; #10;
        checkALU(16'h0001, 1'b0, 1'b0);

        // x + y
        {zx, nx, zy, ny, f, no} = 6'b000010; #10;
        checkALU(16'h000E, 1'b0, 1'b0);

        // 0
        {zx, nx, zy, ny, f, no} = 6'b101010; #10;
        checkALU(16'h0000, 1'b1, 1'b0);

        // 1
        {zx, nx, zy, ny, f, no} = 6'b111111; #10;
        checkALU(16'h0001, 1'b0, 1'b0);

        // -1
        {zx, nx, zy, ny, f, no} = 6'b111010; #10;
        checkALU(16'hFFFF, 1'b0, 1'b1);

        // Test with negative numbers
        x = 16'hFFF9; y = 16'h0005; // -7 and 5

        // x AND y
        {zx, nx, zy, ny, f, no} = 6'b000000; #10;
        checkALU(16'h0001, 1'b0, 1'b0);

        // x + y
        {zx, nx, zy, ny, f, no} = 6'b000010; #10;
        checkALU(16'hFFFE, 1'b0, 1'b1);

        $finish;
    end
endmodule