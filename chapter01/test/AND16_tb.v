// AND16_tb.v
module AND16_tb();
    reg [15:0] a, b;
    wire [15:0] out;
    
    AND16 uut (.a(a), .b(b), .out(out));
    
    initial begin
        a = 16'hFFFF; b = 16'hFFFF; #10;
        if (out !== 16'hFFFF) $display("Test failed for FFFF AND FFFF");
        
        a = 16'h0000; b = 16'hFFFF; #10;
        if (out !== 16'h0000) $display("Test failed for 0000 AND FFFF");
        
        a = 16'hA5A5; b = 16'h5A5A; #10;
        if (out !== 16'h0000) $display("Test failed for A5A5 AND 5A5A");
        
        $display("All tests completed");
    end
endmodule