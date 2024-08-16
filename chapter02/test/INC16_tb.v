// INC16_tb.v
`timescale 1ns / 1ps

module INC16_tb();
    reg [15:0] in;   // Input to the INC16 module
    wire [15:0] out; // Output from the INC16 module

    // Instantiate the INC16 module
    INC16 uut (
        .in(in),
        .out(out)
    );

    initial begin
        // Open VCD file for waveform viewing
        $dumpfile("INC16_tb.vcd");
        $dumpvars(0, INC16_tb);

        // Test cases
        in = 16'd0; #10; // Expected: 0 + 1 = 1
        check_output(16'd1);

        in = 16'd1; #10; // Expected: 1 + 1 = 2
        check_output(16'd2);

        in = 16'd65534; #10; // Expected: 65534 + 1 = 65535
        check_output(16'd65535);

        in = 16'd65535; #10; // Expected: 65535 + 1 = 0 (wrap around)
        check_output(16'd0);

        // Test some random values
        in = 16'h1234; #10; // Expected: 0x1234 + 1 = 0x1235
        check_output(16'h1235);

        in = 16'h8000; #10; // Expected: 0x8000 + 1 = 0x8001
        check_output(16'h8001);

        in = 16'hFFFF; #10; // Expected: 0xFFFF + 1 = 0x0000 (wrap around)
        check_output(16'h0000);

        // Test increment at boundaries
        for (int i = 65530; i < 65536; i++) begin
            in = i;
            #10;
            check_output(i + 1);
        end

        // End the simulation
        $finish;
    end

    // Task to check output and report errors
    task check_output;
        input [15:0] expected;
        begin
            if (out !== expected) begin
                $display("Error at time %0t: in=%h, out=%h (expected %h)", 
                    $time, in, out, expected);
            end else begin
                $display("Correct at time %0t: in=%h, out=%h", $time, in, out);
            end
        end
    endtask
endmodule
