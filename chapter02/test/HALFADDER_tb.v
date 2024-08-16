// HALFADDER_tb.v
`timescale 1ns / 1ps

module HALFADDER_tb();
    reg a, b;
    wire sum, carry;

    HALFADDER uut (.a(a), .b(b), .sum(sum), .carry(carry));

    initial begin
        $dumpfile("HALFADDER_tb.vcd");
        $dumpvars(0, HALFADDER_tb);

        // Test all possible input combinations
        a = 0; b = 0; #10;
        a = 0; b = 1; #10;
        a = 1; b = 0; #10;
        a = 1; b = 1; #10;

        $finish;
    end

    always @(a or b)
        if ((a + b) != {carry, sum})
            $display("Error at time %0t: a=%b, b=%b, sum=%b, carry=%b", $time, a, b, sum, carry);
endmodule