`timescale 1ns / 1ps
module d_flipflop_synrst(data_in,data_out,clock,reset);
input data_in;
input clock,reset;
output reg data_out;

always@(posedge clock)
begin
   if(reset)
     data_out<=1'd0;
   else
data_out<=data_in;
end
endmodule
