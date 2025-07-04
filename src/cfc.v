module cfc(
  input                 clock,
  input          [1:0]  op_code,
  input          [1:0]  index,
  input          [7:0]  value_a, 
  input signed   [7:0]  value_b, 
  output reg     [31:0] data_out,
  output reg            done
);
reg op_active;
parameter NOP   = 2'd0;
parameter RESET = 2'd1;
parameter MUL   = 2'd2;
parameter GET   = 2'd3;
wire [3:0] mac_enable;
wire [3:0] mac_done;
wire [7:0] mac_result [3:0];
wire       clear;
assign clear = (op_code == RESET);
always @(posedge clock) begin
    if (op_code == GET) begin
        data_out <= {mac_result[3], mac_result[2], mac_result[1], mac_result[0]};
    end
end
always @(posedge clock) begin
    done          <= 1'b0; 
    if (op_code != NOP) begin
        op_active <= 1'b1;
    end else if (op_active) begin
        done      <= 1'b1;
        op_active <= 1'b0;
    end
end
genvar i;
generate
  for (i = 0; i < 4; i = i + 1) begin : mac_instances
    assign mac_enable[i] = (i == index) && (op_code == MUL);
    mac u_mac (
      .clock(clock),
      .enable(mac_enable[i]),
      .clear(clear),
      .value_a(value_a),
      .value_b(value_b),
      .result(mac_result[i]),
      .done(mac_done[i])
    );
  end
endgenerate
endmodule
