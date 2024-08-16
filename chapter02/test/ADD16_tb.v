// ADD16_tb.v
`timescale 1ns / 1ps

module ADD16_tb();
    reg [15:0] a, b;
    wire [15:0] out;

    ADD16 uut (.a(a), .b(b), .out(out));

    initial begin
        $dumpfile("ADD16_tb.vcd");
        $dumpvars(0, ADD16_tb);

        // Test cases
        a = 16'd0; b = 16'd0; #10; // 0 + 0
        a = 16'd1; b = 16'd1; #10; // 1 + 1
        a = 16'd65535; b = 16'd1; #10; // Max + 1 (overflow)
        a = 16'd32767; b = 16'd1; #10; // Max positive + 1
        a = 16'h8000; b = 16'hFFFF; #10; // Min negative - 1
        a = 16'h4000; b = 16'h4000; #10; // Positive + Positive
        a = 16'hC000; b = 16'hC000; #10; // Negative + Negative
        a = 16'h8000; b = 16'h8000; #10; // Min negative + Min negative

        // Random tests
        for (int i = 0; i < 1000; i++) begin
            a = $random;
            b = $random;
            #10;
        end

        $finish;
    end

    always @(a or b)
        if ($signed(a) + $signed(b) != $signed(out))
            $display("Error at time %0t: a=%d, b=%d, out=%d", $time, $signed(a), $signed(b), $signed(out));
endmodule