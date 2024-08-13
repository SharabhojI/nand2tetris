// MUX4WAY16_tb.v
module MUX4WAY16_tb();
    reg [15:0] a, b, c, d;
    reg [1:0] sel;
    wire [15:0] out;
    
    MUX4WAY16 uut (.a(a), .b(b), .c(c), .d(d), .sel(sel), .out(out));
    
    initial begin
        a = 16'hAAAA; b = 16'hBBBB; c = 16'hCCCC; d = 16'hDDDD;
        
        sel = 2'b00; #10;
        if (out !== 16'hAAAA) $display("Test failed for sel=00");
        
        sel = 2'b01; #10;
        if (out !== 16'hBBBB) $display("Test failed for sel=01");
        
        sel = 2'b10; #10;
        if (out !== 16'hCCCC) $display("Test failed for sel=10");
        
        sel = 2'b11; #10;
        if (out !== 16'hDDDD) $display("Test failed for sel=11");
        
        $display("All tests completed");
    end
endmodule