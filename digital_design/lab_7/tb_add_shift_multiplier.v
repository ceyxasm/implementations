`timescale 1ns / 1ps
module tb_add_shift_multiplier();
wire [7:0] p;
reg [3:0] a , b;
reg clk,s;

add_shift_multiplier asm(p,a,b,clk,s);
initial 
 begin
   a = 0 ; b= 0 ; clk = 0 ; s = 0;
 end
 
 always #50 clk = ~clk;
 initial
   begin
     #50 a = 6 ; b = 5;
     #50 s =  1 ;
     #450 s = 0;
     #1200 $stop;
   end

endmodule
