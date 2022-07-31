`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2022 12:20:05
// Design Name: 
// Module Name: test_binary_to_gray
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


module test_binary_to_gray;
wire [3:0] g;
reg [3:0] i;
binary_to_gray bg1(i, g);
initial
    begin
        i=4'b0001;
        #10 i=4'b0011;
        #10 i=4'b0101;
        #10 i=4'b0110;
        #10 i=4'b0111;
        #10 i=4'b1001;
        #10 i=4'b1010;
        #10 i=4'b1011;
        #10 i=4'b1101;
    end
initial #100 $finish;
endmodule
