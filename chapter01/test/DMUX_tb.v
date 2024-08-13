// DMUX_tb.v
module DMUX_tb();
    reg in, sel;
    wire a, b;
    
    DMUX uut (.in(in), .sel(sel), .a(a), .b(b));
    
    initial begin
        in = 1; sel = 0; #10;
        if (a !== 1 || b !== 0) $display("Test failed for sel=0, in=1");
        
        sel = 1; #10;
        if (a !== 0 || b !== 1) $display("Test failed for sel=1, in=1");
        
        in = 0; sel = 0; #10;
        if (a !== 0 || b !== 0) $display("Test failed for sel=0, in=0");
        
        sel = 1; #10;
        if (a !== 0 || b !== 0) $display("Test failed for sel=1, in=0");
        
        $display("All tests completed");
    end
endmodule