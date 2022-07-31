`timescale 1ns / 1ps
module add_shift_multiplier(p,a,b,clk,s);
output reg[7:0]p; //Output variable p
input [3:0]a,b; //Input variable a,b
input clk,s; //s is the control input, clk is clock input
reg [3:0]x; //Register to store input a
reg [7:0]y; //Register to store input b
always @(posedge clk)
   begin
    case(s)
      1'b0:
      begin //When s=0
           x=a; //Load input 'a' to register 'x'
           y[3:0]=b; //Load input 'b' to lower nibble of register 'y'
           y[7:4]=4'b0000; //Make upper nibble of register 'y' as '0000'
      end
      1'b1:
      begin //When s=1
        if(y[0]) //If LSB of 'y' is set
          y[7:4]=y[7:4]+x; //Add register 'x' to upper nibble of register of 'y'
        y={1'b0,y[7:1]}; // Shift right by 1 bit
      end
    endcase
  p=y; //Assign product
  end
endmodule
