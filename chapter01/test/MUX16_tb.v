// MUX16_tb.v
module MUX16_tb();
    reg [15:0] a, b;
    reg sel;
    wire [15:0] out;
    
    // Instantiate the Unit Under Test (UUT)
    MUX16 uut (
        .a(a),
        .b(b),
        .sel(sel),
        .out(out)
    );
    
    initial begin
        // Initialize Inputs
        a = 16'h0000; b = 16'hFFFF; sel = 0;
        
        // Wait 100 ns for global reset to finish
        #100;
        
        // Test case 1: sel = 0, should select a
        sel = 0; #10;
        if (out !== a) $display("Test failed for sel = 0");
        
        // Test case 2: sel = 1, should select b
        sel = 1; #10;
        if (out !== b) $display("Test failed for sel = 1");
        
        // Test case 3: Different values
        a = 16'hA5A5; b = 16'h5A5A; sel = 0; #10;
        if (out !== a) $display("Test failed for sel = 0 with new values");
        
        sel = 1; #10;
        if (out !== b) $display("Test failed for sel = 1 with new values");
        
        $display("All tests completed");
    end
endmodule