// BIT_tb.v
`timescale 1ns / 1ps

module BIT_tb();
    reg in, load, clk;
    wire out;
    
    BIT uut(.in(in), .load(load), .clk(clk), .out(out));
    
    always #5 clk = ~clk; // 10ns clock period
    
    initial begin
        clk = 0;
        in = 0;
        load = 0;
        #10 load = 1; in = 1;
        #10 load = 0;
        #10 in = 0;
        #10 load = 1;
        #10 $finish;
    end
    
    always @(posedge clk) begin
        #1; // Add a 1ns delay before checking the output
        $display("Time=%0t: in=%b, load=%b, out=%b", $time, in, load, out);
        if ((load == 1 && out != in) || (load == 0 && $past(out) != out))
            $display("Error at time %0t", $time);
    end
endmodule
