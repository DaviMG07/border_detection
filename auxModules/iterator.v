module iterator(
    input clk,
    input en,
    input [199:0] MatA,
    input [199:0] MatB,
    output reg [199:0] resultSum,
    output reg done
);

    wire [8:0] mac_result;
    wire [7:0] value_a;
    wire [7:0] value_b;

    mac mac_unit (
        .clock(clk),
        .clear(clear_mac),
        .enable(en_mac),
        .value_a(value_a),
        .value_b(value_b),
        .result(mac_result)
    );

    reg [4:0] counter;
    reg en_mac;
    reg clear_mac;

    assign value_a = MatA[counter * 8 +: 8];
    assign value_b = MatB[counter * 8 +: 8];

    reg [199:0] temp_sum;

    always @(posedge clk) begin
        if (en) begin
            clear_mac <= 1'b0;

            if (counter < 5'd24) begin
                en_mac <= 1'b1;
                counter <= counter + 1;
                done <= 1'b0;
            end else begin
                en_mac <= 1'b1;
                resultSum <= mac_result;
                done <= 1'b1;
                counter <= 5'd0;
            end
        end else begin
            done <= 1'b0;
            en_mac <= 1'b0;
            counter <= 5'd0;
            clear_mac <= 1'b1;
        end
    end

endmodule
