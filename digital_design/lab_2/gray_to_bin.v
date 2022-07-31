`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2022 13:00:57
// Design Name: 
// Module Name: gray_to_bin
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


module gray_to_bin(g,i );
input [3:0] g;
output [3:0] i;
assign i[3]= g[3];
assign i[2]=g[3]^g[2];
assign i[1]=i[2]^g[1];
assign i[0]=i[1]^g[0];
endmodule
