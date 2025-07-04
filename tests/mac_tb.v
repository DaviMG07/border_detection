`timescale 1ns / 1ps
module mac_tb;
  reg clock;
  reg clear;
  reg enable;
  reg [7:0] value_a;
  reg signed [7:0] value_b;
  wire [7:0] result;
  wire done;
  reg [7:0] expected_result;
  mac uut (
    .clock(clock),
    .clear(clear),
    .enable(enable),
    .value_a(value_a),
    .value_b(value_b),
    .result(result),
    .done(done)
  );
  initial begin
    clock = 0;
    forever #5 clock = ~clock;
  end
  initial begin
    $display("--- Starting MAC Testbench (Corrected Types) ---");
    $monitor("Time=%0t: clear=%b, enable=%b, value_a=%d, value_b=%d -> result=%d, done=%b",
             $time, clear, enable, value_a, value_b, result, done);
    clear = 1; #10; clear = 0; #10;
    $display("\n--- Test 1: Simple Multiplication ---");
    value_a = 10; value_b = 5; enable = 1; expected_result = 50;
    #10;
    enable = 0;
    if (result !== expected_result) $display("*** TEST 1 FAILED: Result=%d, Expected=%d ***", result, expected_result);
    else $display("--- TEST 1 PASSED ---");
    #10;
    $display("\n--- Test 2: Saturation (Positive) ---");
    clear = 1; #10; clear = 0; #10;
    value_a = 100; value_b = 3; enable = 1; expected_result = 255;
    #10;
    enable = 0;
    if (result !== expected_result) $display("*** TEST 2 FAILED: Result=%d, Expected=%d ***", result, expected_result);
    else $display("--- TEST 2 PASSED ---");
    #10;
    $display("\n--- Test 3: Saturation (Negative) ---");
    clear = 1; #10; clear = 0; #10;
    value_a = 10; value_b = -2; enable = 1; expected_result = 0;
    #10;
    enable = 0;
    if (result !== expected_result) $display("*** TEST 3 FAILED: Result=%d, Expected=%d ***", result, expected_result);
    else $display("--- TEST 3 PASSED ---");
    #10;
    $display("\n--- Test 4: Accumulation ---");
    clear = 1; #10; clear = 0; #10;
    value_a = 10; value_b = 2; enable = 1; #10;
    value_a = 5; value_b = 3; enable = 1; expected_result = 35;
    #10;
    enable = 0;
    if (result !== expected_result) $display("*** TEST 4 FAILED: Result=%d, Expected=%d ***", result, expected_result);
    else $display("--- TEST 4 PASSED ---");
    $display("\n--- MAC Testbench Finished ---");
    $finish;
  end
endmodule