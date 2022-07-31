`timescale 1ns / 1ps
module tb_serial_adder_8_bit();
wire [7:0] out_a,out_b;
wire s;
reg [7:0] a,b;
reg on;
serial_adder_8_bit H1(a,b,on,out_a,out_b,s);
initial
begin
    a=8'b00000000;b=8'b00000001;on=1'b0;
#5 on=1'b1;
#5 on=1'b0;
#90 a=8'b00000101;b=8'b00001001;
#5 on=1'b1;
#5 on=1'b0;
#90 a=8'b00011000;b=8'b00010001;
#5 on=1'b1;
#5 on=1'b0;
end
initial #300 $finish;
endmodule
