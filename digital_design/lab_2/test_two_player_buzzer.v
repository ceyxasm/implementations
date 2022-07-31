`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2022 22:21:21
// Design Name: 
// Module Name: test_two_player_buzzer
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


module test_two_player_buzzer;

wire led1, led2;
reg buzzer, control;
two_player_buzzer TPB1(led1, led2, control, buzzer);

initial
    begin
        control=1'b0; buzzer=1'b0;
        #10 buzzer=1'b1;
        #10 control=1'b1; ;
        #10 buzzer=1'b0;
    end
initial #40 $finish;
endmodule
