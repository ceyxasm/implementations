`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 14.01.2022 15:23:52
// Design Name: 
// Module Name: four_bit_adder
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


module four_bit_adder(a,b,s,cout);
input [3:0] a,b;
output [3:0] s;
output cout;
full_adder f1( a[0], b[0],0,  s[0], c1);
full_adder f2( a[1], b[1],c1,  s[1], c2); 
full_adder f3( a[2], b[2],c2,  s[2], c3);
full_adder f4( a[3], b[3],c3,  s[3], cout); 
endmodule
