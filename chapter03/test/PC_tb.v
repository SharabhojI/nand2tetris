// PC_tb.v
`timescale 1ns / 1ps

module PC_tb();
    reg [15:0] in;
    reg load, inc, reset, clk;
    wire [15:0] out;
    
    PC uut(.in(in), .load(load), .inc(inc), .reset(reset), .clk(clk), .out(out));
    
    always #5 clk = ~clk;
    
    initial begin
        clk = 0;
        in = 16'h0000;
        load = 0;
        inc = 0;
        reset = 1;
        #10 reset = 0; inc = 1;
        #30 load = 1; in = 16'hAAAA;
        #10 load = 0;
        #20 reset = 1;
        #10 $finish;
    end
    
    always @(posedge clk) begin
        $display("Time=%0t: in=%h, load=%b, inc=%b, reset=%b, out=%h", $time, in, load, inc, reset, out);
        if (reset == 1 && out != 16'h0000)
            $display("Error: reset not working at time %0t", $time);
        else if (load == 1 && out != in)
            $display("Error: load not working at time %0t", $time);
        else if (inc == 1 && load == 0 && reset == 0 && out != $past(out) + 1)
            $display("Error: increment not working at time %0t", $time);
    end
endmodule