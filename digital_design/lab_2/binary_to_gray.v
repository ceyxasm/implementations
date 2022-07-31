`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2022 12:14:10
// Design Name: 
// Module Name: binary_to_gray
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


module binary_to_gray(i, g);
input [3:0] i;
output [3:0] g;
assign g[3]=i[3];
assign g[2]=i[3]^i[2];
assign g[1]=i[2]^i[1];
assign g[0]=i[0]^i[1];
endmodule
