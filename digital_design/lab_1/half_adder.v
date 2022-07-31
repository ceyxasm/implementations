`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

// Create Date: 13.01.2022 23:07:47
// Design Name: half adder
// Module Name: half_adder
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


module half_adder(a,b,s,c); 
input a,b;
output s,c;
assign s=a^b;
assign c=a&b;
endmodule
