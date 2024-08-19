// RAM4K_tb.v
`timescale 1ns / 1ps

module RAM4K_tb();
    reg [15:0] in;
    reg [11:0] address;
    reg load, clk;
    wire [15:0] out;
    
    RAM4K uut(.in(in), .address(address), .load(load), .clk(clk), .out(out));
    
    always #5 clk = ~clk;
    
    initial begin
        clk = 0;
        in = 16'h0000;
        address = 12'b000000000000;
        load = 0;
        
        // Test 1: Write and read from address 0
        #10 load = 1; in = 16'hAAAA;
        #10 load = 0;
        #10 address = 12'b000000000000;
        
        // Test 2: Write and read from a different address
        #10 address = 12'b000000000001; load = 1; in = 16'h5555;
        #10 load = 0; address = 12'b000000000001;
        
        // Test 3: Read back from the initial address to verify no data corruption
        #10 address = 12'b000000000000;
        
        // Test 4: Random write and read from an upper address
        #10 address = 12'b000000011111; load = 1; in = 16'hF0F0;
        #10 load = 0; address = 12'b000000011111;
        
        #10 $finish;
    end
    
    always @(posedge clk) begin
        $display("Time=%0t: address=%b, in=%h, load=%b, out=%h", $time, address, in, load, out);
        if (load == 1 && out != in)
            $display("Error at time %0t", $time);
    end
endmodule
