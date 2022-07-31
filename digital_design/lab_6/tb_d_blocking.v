`timescale 1ns / 1ps
module tb_d_blocking();
reg d, clk;
wire q1, q2;
d_blocking db(d,clk,q1,q2);
initial 
begin
 d = 0;
 clk = 0;
end
always #100 clk=~clk;
initial
  begin
    #200 d = 1'b1;
    #200 d = 1'b0;
    #300 d = 1'b1;
    #200 d = 1'b0;
    #400 $stop;
   end
endmodule
