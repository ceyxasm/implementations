`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 14.01.2022 15:40:16
// Design Name: 
// Module Name: test_four_bit_adder
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module test_four_bit_adder;
reg [3:0] a,b;  //input 4 bit numbers
wire [3:0] s;   //output sum
wire cout;      //output carry

four_bit_adder fb1(a, b, s, cout);

initial
    begin
        a=1; b=2;
        #10  a=2; b=5;
        #10 a=3; b=7;
        #10 a=4; b=4;
        #10 a=3; b=4;
    end
initial #50 $finish; 
endmodule
