`timescale 1ns / 1ps
module cfc_tb;
  reg clock;
  reg [1:0] op_code;
  reg [1:0] index;
  reg [7:0] value_a;
  reg signed [7:0] value_b;
  wire [31:0] data_out;
  wire done;
  reg [31:0] expected_data;
  cfc uut (
    .clock(clock),
    .op_code(op_code),
    .index(index),
    .value_a(value_a),
    .value_b(value_b),
    .data_out(data_out),
    .done(done)
  );
  initial begin
    clock = 0;
    forever #5 clock = ~clock;
  end
  initial begin
    $display("--- Starting CFC Concatenation Testbench with Done Signal Check ---");
    $monitor("Time=%0t: op_code=%d, index=%d, value_a=%d, value_b=%d -> mac3=%d, mac2=%d, mac1=%d, mac0=%d, done=%b",
             $time, op_code, index, value_a, value_b, data_out[31:24], data_out[23:16], data_out[15:8], data_out[7:0], done);
    $display("\n--- Resetting CFC ---");
    op_code = 1; 
    index = 0;
    value_a = 0;
    value_b = 0;
    #10; 
    op_code = 0; 
    #10; 
    if (done !== 1) $display("*** RESET DONE FAILED ***");
    else $display("--- RESET DONE PASSED ---");
    #10; 

    
    $display("\n--- Loading values into MACs ---");
    op_code = 2; 
    index = 0; value_a = 10; value_b = 1; #10; 
    op_code = 0; #10; 
    if (done !== 1) $display("*** MAC 0 DONE FAILED ***");
    else $display("--- MAC 0 DONE PASSED ---");
    #10;

    op_code = 2; 
    index = 1; value_a = 20; value_b = 1; #10; 
    op_code = 0; #10; 
    if (done !== 1) $display("*** MAC 1 DONE FAILED ***");
    else $display("--- MAC 1 DONE PASSED ---");
    #10;

    op_code = 2; 
    index = 2; value_a = 30; value_b = 1; #10; 
    op_code = 0; #10; 
    if (done !== 1) $display("*** MAC 2 DONE FAILED ***");
    else $display("--- MAC 2 DONE PASSED ---");
    #10;

    op_code = 2; 
    index = 3; value_a = 40; value_b = 1; #10; 
    op_code = 0; #10; 
    if (done !== 1) $display("*** MAC 3 DONE FAILED ***");
    else $display("--- MAC 3 DONE PASSED ---");
    #10;

    
    $display("\n--- Getting concatenated result ---");
    op_code = 3; 
    index = 0;   
    
    
    expected_data = {8'd40, 8'd30, 8'd20, 8'd10};
    #10; 
    op_code = 0; 
    #10; 

    
    if (data_out !== expected_data) begin
        $display("*** DATA OUT FAILED ***");
        $display("Expected: %d, %d, %d, %d, Got: %d, %d, %d, %d", expected_data[31:24], expected_data[23:16], expected_data[15:8], expected_data[7:0], data_out[31:24], data_out[23:16], data_out[15:8], data_out[7:0]);
    end else begin
        $display("--- DATA OUT PASSED ---");
    end
    if (done !== 1) $display("*** GET DONE FAILED ***");
    else $display("--- GET DONE PASSED ---");
    #10;
    $display("\n--- CFC Testbench Finished ---");
    $finish;
  end
endmodule
