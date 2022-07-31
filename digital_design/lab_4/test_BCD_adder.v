`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/05/2022 10:22:57 PM
// Design Name: 
// Module Name: TB_bcdAdder
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


module TB_bcdAdder();

reg [3:0] a,b;
reg cin;
wire [3:0] sum;
wire cout;

bcdAdder blaaa(a,b,cin,sum,cout);

initial 
    begin
        a = 4'b0000; b = 4'b0101; cin = 1'b0;
        #10 a = 4'b1001;
        #10 b = 4'b1001;
        #10 cin = 1'b1;
        #10 a = 4'b0100;
        #10 b = 4'b0111;
    end
    
initial #50 $finish;

endmodule
