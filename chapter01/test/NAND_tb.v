// NAND_tb.v
module NAND_tb();
    reg a, b;
    wire out;
    
    NAND uut (.a(a), .b(b), .out(out));
    
    initial begin
        // Initialize Inputs
        a = 0; b = 0;

        // Start tests        
        a = 0; b = 0; #10;
        if (out !== 1) $display("Test failed for input 00");
        
        a = 0; b = 1; #10;
        if (out !== 1) $display("Test failed for input 01");
        
        a = 1; b = 0; #10;
        if (out !== 1) $display("Test failed for input 10");
        
        a = 1; b = 1; #10;
        if (out !== 0) $display("Test failed for input 11");
        
        $display("All tests completed");
    end
endmodule