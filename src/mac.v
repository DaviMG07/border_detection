module mac(
  input                    clock,
  input                    clear,
  input                    enable,
  input             [7:0]  value_a, 
  input signed      [7:0]  value_b,
  output            [7:0]  result,
  output reg               done
);
reg signed [39:0] accumulator;
wire signed [15:0] product;
assign product = $signed(value_a) * value_b;
always @(posedge clock) begin
  if (clear) begin
    accumulator <= 0;
  end else if (enable) begin
    accumulator <= accumulator + product;
  end
end
always @(posedge clock) begin
    if (clear || enable) begin
        done <= 1;
    end else begin
        done <= 0;
    end
end
assign result = (accumulator > 255) ? 8'd255 :
                (accumulator < 0)   ? 8'd0   :
                                      accumulator[7:0];
endmodule
