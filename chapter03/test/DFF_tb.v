// DFF_tb.v
`timescale 1ns / 1ps

module DFF_tb();
    reg in, clk;
    wire out;
    
    DFF uut(.in(in), .clk(clk), .out(out));
    
    always #5 clk = ~clk;
    
    initial begin
        clk = 0;
        in = 0;
        #10 in = 1;
        #10 in = 0;
        #10 in = 1;
        #10 $finish;
    end
    
    always @(posedge clk) begin
        $display("Time=%0t: in=%b, out=%b", $time, in, out);
        if (out != $past(in))
            $display("Error at time %0t", $time);
    end
endmodule