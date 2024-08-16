// HALFADDER_tb.v
`timescale 1ns / 1ps

module FULLADDER_tb();
    reg a, b, c;
    wire sum, carry;

    FULLADDER uut (.a(a), .b(b), .c(c), .sum(sum), .carry(carry));

    initial begin
        $dumpfile("FULLADDER_tb.vcd");
        $dumpvars(0, FULLADDER_tb);

        // Test all possible input combinations
        for (int i = 0; i < 8; i++) begin
            {a, b, c} = i[2:0];
            #10;
        end

        $finish;
    end

    always @(a or b or c)
        if ((a + b + c) != {carry, sum})
            $display("Error at time %0t: a=%b, b=%b, c=%b, sum=%b, carry=%b", $time, a, b, c, sum, carry);
endmodule