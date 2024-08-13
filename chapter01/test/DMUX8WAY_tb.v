// DMUX8WAY_tb.v
module DMUX8WAY_tb();
    reg in;
    reg [2:0] sel;
    wire a, b, c, d, e, f, g, h;
    
    DMUX8WAY uut (.in(in), .sel(sel), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g), .h(h));
    
    initial begin
        in = 1;
        
        sel = 3'b000; #10;
        if (a !== 1 || b !== 0 || c !== 0 || d !== 0 || e !== 0 || f !== 0 || g !== 0 || h !== 0) $display("Test failed for sel=000");
        
        sel = 3'b001; #10;
        if (a !== 0 || b !== 1 || c !== 0 || d !== 0 || e !== 0 || f !== 0 || g !== 0 || h !== 0) $display("Test failed for sel=001");
        
        sel = 3'b010; #10;
        if (a !== 0 || b !== 0 || c !== 1 || d !== 0 || e !== 0 || f !== 0 || g !== 0 || h !== 0) $display("Test failed for sel=010");
        
        sel = 3'b011; #10;
        if (a !== 0 || b !== 0 || c !== 0 || d !== 1 || e !== 0 || f !== 0 || g !== 0 || h !== 0) $display("Test failed for sel=011");
        
        sel = 3'b100; #10;
        if (a !== 0 || b !== 0 || c !== 0 || d !== 0 || e !== 1 || f !== 0 || g !== 0 || h !== 0) $display("Test failed for sel=100");
        
        sel = 3'b101; #10;
        if (a !== 0 || b !== 0 || c !== 0 || d !== 0 || e !== 0 || f !== 1 || g !== 0 || h !== 0) $display("Test failed for sel=101");
        
        sel = 3'b110; #10;
        if (a !== 0 || b !== 0 || c !== 0 || d !== 0 || e !== 0 || f !== 0 || g !== 1 || h !== 0) $display("Test failed for sel=110");
        
        sel = 3'b111; #10;
        if (a !== 0 || b !== 0 || c !== 0 || d !== 0 || e !== 0 || f !== 0 || g !== 0 || h !== 1) $display("Test failed for sel=111");
        
        $display("All tests completed");
    end
endmodule