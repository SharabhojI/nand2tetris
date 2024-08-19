// REGISTER_tb.v
`timescale 1ns / 1ps

module REGISTER_tb();
    reg [15:0] in;
    reg load, clk;
    wire [15:0] out;
    
    REGISTER uut(.in(in), .load(load), .clk(clk), .out(out));
    
    always #5 clk = ~clk; // 10ns clock period
    
    initial begin
        clk = 0;
        in = 16'h0000;
        load = 0;
        #10 load = 1; in = 16'hAAAA;
        #10 load = 0;
        #10 in = 16'h5555;
        #10 load = 1;
        #10 $finish;
    end
    
    always @(posedge clk) begin
        #1; // Add a 1ns delay before checking the output
        $display("Time=%0t: in=%h, load=%b, out=%h", $time, in, load, out);
        if ((load == 1 && out != in) || (load == 0 && $past(out) != out))
            $display("Error at time %0t", $time);
    end
endmodule
