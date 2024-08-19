// RAM16K_tb.v
`timescale 1ns / 1ps

module RAM16K_tb();
    reg [15:0] in;
    reg [13:0] address;
    reg load, clk;
    wire [15:0] out;
    
    // Instantiate the RAM16K module
    RAM16K uut (
        .in(in), 
        .address(address), 
        .load(load), 
        .clk(clk), 
        .out(out)
    );
    
    // Clock generation
    always #5 clk = ~clk;
    
    initial begin
        // Initialize values
        clk = 0;
        in = 16'h0000;
        address = 14'b00000000000000;
        load = 0;

        // Test sequence
        #10 load = 1; in = 16'hAAAA; address = 14'b00000000000001; // Write to address 1
        #10 load = 0; // End write

        #10 address = 14'b00000000000001; // Read from address 1
        #10 address = 14'b00000000000000; // Read from address 0 (default, not written)
                
        #10 $finish;
    end
    
    // Display output and check for errors
    always @(posedge clk) begin
        $display("Time=%0t: address=%b, in=%h, load=%b, out=%h", $time, address, in, load, out);
        // Check if the value was loaded correctly
        if (load == 1 && out != in)
            $display("Error at time %0t: expected %h, got %h", $time, in, out);
    end
endmodule
