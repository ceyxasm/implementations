`timescale 1ns / 1ps

module tb_dflipflop_asynrst();
reg data_in;
reg clock,reset;
wire data_out;
d_flipflop_asynrst dff(data_in,data_out,clock,reset);
initial 
begin
 data_in = 0;
 clock = 0;
 reset=0;
end
always #100 clock=~clock;
initial
  begin
    #200 data_in = 1'b1;
         reset = 1'b1;
    #200 data_in = 1'b1;
         reset = 1'b1;

    #300 data_in = 1'b1;
         reset=1'b0;
    #600 data_in = 1'b0;
    #500 data_in = 1'b1;
    #200 data_in = 1'b0;
    #400 $stop;
   end
endmodule
