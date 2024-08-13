// MUX_tb.v
module MUX_tb();
    reg a, b, sel;
    wire out;
    
    MUX uut (.a(a), .b(b), .sel(sel), .out(out));
    
    initial begin
        a = 0; b = 1; sel = 0; #10;
        if (out !== 0) $display("Test failed for sel=0, a=0, b=1");
        
        sel = 1; #10;
        if (out !== 1) $display("Test failed for sel=1, a=0, b=1");
        
        a = 1; b = 0; sel = 0; #10;
        if (out !== 1) $display("Test failed for sel=0, a=1, b=0");
        
        sel = 1; #10;
        if (out !== 0) $display("Test failed for sel=1, a=1, b=0");
        
        $display("All tests completed");
    end
endmodule