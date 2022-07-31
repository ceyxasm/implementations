`timescale 1ns / 1ps

module d_non_blocking(d,clk,q1,q2);
input d, clk;
output reg q1, q2;

always @(posedge clk)
 begin
   q1 <= d;
   q2 <= q1;
 end
endmodule
