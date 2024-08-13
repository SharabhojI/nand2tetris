// MUX8WAY16_tb.v
module MUX8WAY16_tb();
    reg [15:0] a, b, c, d, e, f, g, h;
    reg [2:0] sel;
    wire [15:0] out;
    
    MUX8WAY16 uut (.a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g), .h(h), .sel(sel), .out(out));
    
    initial begin
        a = 16'h1111; b = 16'h2222; c = 16'h3333; d = 16'h4444;
        e = 16'h5555; f = 16'h6666; g = 16'h7777; h = 16'h8888;
        
        sel = 3'b000; #10;
        if (out !== 16'h1111) $display("Test failed for sel=000");
        
        sel = 3'b001; #10;
        if (out !== 16'h2222) $display("Test failed for sel=001");
        
        sel = 3'b010; #10;
        if (out !== 16'h3333) $display("Test failed for sel=010");
        
        sel = 3'b011; #10;
        if (out !== 16'h4444) $display("Test failed for sel=011");
        
        sel = 3'b100; #10;
        if (out !== 16'h5555) $display("Test failed for sel=100");
        
        sel = 3'b101; #10;
        if (out !== 16'h6666) $display("Test failed for sel=101");
        
        sel = 3'b110; #10;
        if (out !== 16'h7777) $display("Test failed for sel=110");
        
        sel = 3'b111; #10;
        if (out !== 16'h8888) $display("Test failed for sel=111");
        
        $display("All tests completed");
    end
endmodule