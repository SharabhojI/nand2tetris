// NOT16_tb.v
module NOT16_tb();
    reg [15:0] in;
    wire [15:0] out;
    
    NOT16 uut (.in(in), .out(out));
    
    initial begin
        in = 16'h0000; #10;
        if (out !== 16'hFFFF) $display("Test failed for input 0000");
        
        in = 16'hFFFF; #10;
        if (out !== 16'h0000) $display("Test failed for input FFFF");
        
        in = 16'hA5A5; #10;
        if (out !== 16'h5A5A) $display("Test failed for input A5A5");
        
        $display("All tests completed");
    end
endmodule