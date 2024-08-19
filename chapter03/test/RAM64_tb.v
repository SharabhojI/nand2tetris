// RAM64_tb.v
`timescale 1ns / 1ps

module RAM64_tb();
    reg [15:0] in;
    reg [5:0] address;
    reg load, clk;
    wire [15:0] out;
    
    RAM64 uut(.in(in), .address(address), .load(load), .clk(clk), .out(out));
    
    always #5 clk = ~clk;
    
    initial begin
        clk = 0;
        in = 16'h0000;
        address = 6'b000000;
        load = 0;
        #10 load = 1; in = 16'hAAAA;
        #10 load = 0;
        #10 address = 6'b000001; in = 16'h5555; load = 1;
        #10 load = 0;
        #10 address = 6'b000000;
        #10 address = 6'b000001;
        #10 $finish;
    end
    
    always @(posedge clk) begin
        $display("Time=%0t: address=%b, in=%h, load=%b, out=%h", $time, address, in, load, out);
        if (load == 1 && out != in)
            $display("Error at time %0t", $time);
    end
endmodule