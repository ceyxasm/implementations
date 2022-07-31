`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 13.01.2022 23:41:34
// Design Name: 
// Module Name: test_fuller_adder
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


module test_fuller_adder;

wire s, cout;
reg a, b,c;

full_adder f1(a,b,c,s,cout);

initial 
    begin
        a=1'b0; b=1'b0; c=1'b0;
        #10 a=1'b1; 
        #10 a=1'b0; b=1'b1;
        #10 a=1'b1;
        #10 a=1'b0; b=1'b0; c=1'b1;
        #10 a=1'b1;
        #10 a=1'b0; b=1'b1;
        #10 a=1'b1;
    end
initial #100 $finish;
endmodule
