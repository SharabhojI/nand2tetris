// DMUX4WAY_tb.v
module DMUX4WAY_tb();
    reg in;
    reg [1:0] sel;
    wire a, b, c, d;
    
    DMUX4WAY uut (.in(in), .sel(sel), .a(a), .b(b), .c(c), .d(d));
    
    initial begin
        in = 1;
        
        sel = 2'b00; #10;
        if (a !== 1 || b !== 0 || c !== 0 || d !== 0) $display("Test failed for sel=00");
        
        sel = 2'b01; #10;
        if (a !== 0 || b !== 1 || c !== 0 || d !== 0) $display("Test failed for sel=01");
        
        sel = 2'b10; #10;
        if (a !== 0 || b !== 0 || c !== 1 || d !== 0) $display("Test failed for sel=10");
        
        sel = 2'b11; #10;
        if (a !== 0 || b !== 0 || c !== 0 || d !== 1) $display("Test failed for sel=11");
        
        $display("All tests completed");
    end
endmodule