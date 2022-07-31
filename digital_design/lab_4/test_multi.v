`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/06/2022 04:36:12 PM
// Design Name: 
// Module Name: tb_multiplier
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


module tb_multiplier();

reg [2:0] a,b;
//wire [5:0] p;
//wire [5:0] bcd;
//wire [3:0] w;
wire [6:0] led_ten, led_one;
wire [3:0] ten, one;
multiplier mp(a[2],a[1],a[0],b[2],b[1],b[0],led_ten,led_one, ten, one);


initial
    begin
        a = 3'b000; b = 3'b000;
        #10 a = 3'b111;
        #10 b = 3'b111;
        #10 a = 3'b010;
        #10 b = 3'b101;
        #10 a = 3'b001;
        #10 a = 3'b101;
    end
initial #100 $finish;
endmodule
