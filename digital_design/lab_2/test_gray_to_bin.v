`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2022 13:07:13
// Design Name: 
// Module Name: test_gray_to_bin
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


module test_gray_to_bin;
wire [3:0] i;
reg [3:0] g;
gray_to_bin gb1(g, i);
initial
    begin
        g=4'b0001;
        #10 g=4'b0010;
        #10 g=4'b0111;
        #10 g=4'b0101;
        #10 g=4'b0100;
        #10 g=4'b1101;
        #10 g=4'b1111;
        #10 g=4'b1110;
        #10 g=4'b1011;
    end
initial #100 $finish;
endmodule
