`timescale 1ns / 1ps
module serial_adder_8_bit(a,b,on,out_a,out_b,s);
input [7:0] a,b;
input on;
reg uni_clk;
reg control_3;
reg reset,s0,s1;
output [7:0] out_a,out_b;
output s;
wire c,z;
wire d;
always@(posedge on)
begin
uni_clk=1'b0; s0=1'b0;s1=1'b0; control_3=1'b0; reset=1'b0;
#5 uni_clk=1'b1; s0=1'b1; s1=1'b1; reset=1'b1;
#5 uni_clk=0;s0=1'b1; s1=1'b0; control_3=1'b1; reset=1'b0;
#5 uni_clk=1'b1;  
#5 uni_clk=0;s0=1'b1; s1=1'b0; 
#5 uni_clk=1'b1;
#5 uni_clk=0;s0=1'b1; s1=1'b0; 
#5 uni_clk=1'b1;
#5 uni_clk=0;s0=1'b1; s1=1'b0; 
#5 uni_clk=1'b1;  
#5 uni_clk=0;s0=1'b1; s1=1'b0; 
#5 uni_clk=1'b1;
#5 uni_clk=0;s0=1'b1; s1=1'b0; 
#5 uni_clk=1'b1;
#5 uni_clk=0;s0=1'b1; s1=1'b0; 
#5 uni_clk=1'b1;  
#5 uni_clk=0;s0=1'b1; s1=1'b0; 
#5 uni_clk=1'b1;  
#5 uni_clk=0;s0=1'b1; s1=1'b0;
end

shift_register SR1(a,s,0,uni_clk,s0,s1,out_a);
shift_register SR2(b,0,0,uni_clk,s0,s1,out_b);
fa F1(s,c,out_a[0],out_b[0],z);
d_flipflop_synrst D1(d,z,uni_clk,reset);

assign d = (c&control_3 ) + ((control_3^1)&z) ;
endmodule
