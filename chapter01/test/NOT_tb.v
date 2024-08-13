// NOT_tb.v
module NOT_tb();
    reg in;
    wire out;
    
    // Instantiate the Unit Under Test (UUT)
    NOT uut (
        .in(in),
        .out(out)
    );
    
    initial begin
        // Initialize Inputs
        in = 0;
        
        // Wait 100 ns for global reset to finish
        #100;
        
        in = 0; #10;
        if (out !== 1) $display("Test failed for input 0");
        
        in = 1; #10;
        if (out !== 0) $display("Test failed for input 1");
        
        $display("All tests completed");
    end
endmodule