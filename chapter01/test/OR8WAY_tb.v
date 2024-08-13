// OR8WAY_tb.v
module OR8WAY_tb();
    reg [7:0] in;
    wire out;
    
    OR8WAY uut (.in(in), .out(out));
    
    initial begin
        in = 8'h00; #10;
        if (out !== 0) $display("Test failed for input 00");
        
        in = 8'h01; #10;
        if (out !== 1) $display("Test failed for input 01");
        
        in = 8'h80; #10;
        if (out !== 1) $display("Test failed for input 80");
        
        in = 8'hFF; #10;
        if (out !== 1) $display("Test failed for input FF");
        
        $display("All tests completed");
    end
endmodule
