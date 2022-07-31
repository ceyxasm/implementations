`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/05/2022 11:21:28 PM
// Design Name: 
// Module Name: tb_bcdsub
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


module tb_bcdsub(

    );
reg [3:0] a,b;
wire [3:0] diff;
wire sign;

bcd_subtractor blaaa(a,b,diff,sign);

initial 
    begin
        a = 4'b0000; b = 4'b0101;
        #10 a = 4'b0110;
        #10 a = 4'b1001;
        #10 b = 4'b1001;
        #10 a = 4'b0100;
        #10 b = 4'b0111;
        #10 b = 4'b1000;
        #10 a = 4'b0001;
    end
    
initial #100 $finish;
    
    
    
  
endmodule
