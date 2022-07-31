`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/06/2022 04:04:06 PM
// Design Name: 
// Module Name: multiplier
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


module threebitadder(a2,a1,a0,b2,b1,b0,cin,s2,s1,s0,cout);
input a0,a1,a2,b0,b1,b2,cin;
output s0,s1,s2,cout;

full_adder F1(a0,b0,cin,s0,c1);  

full_adder F2(a1,b1,c1,s1,c2);

full_adder F4(a2,b2,c2,s2,cout);
endmodule



module sixbitadder(a5,a4,a3,a2,a1,a0,b,cin,sum,cout);
    
input a0,a1,a2,a3,a4,a5;
input [5:0] b;
input cin;
output [5:0]sum;
output cout;
wire [5:0]c;
assign c[0] = cin;
full_adder F1(a0,b[0],cin,sum[0],c[1]);
full_adder F2(a1,b[1],c[1],sum[1],c[2]);
full_adder F3(a2,b[2],c[2],sum[2],c[3]);
full_adder F4(a3,b[3],c[3],sum[3],c[4]);
full_adder F5(a4,b[4],c[4],sum[4],c[5]);
full_adder F6(a5,b[5],c[5],sum[5],cout);

endmodule



module bcd_to_7seg(
    input  [3:0]hex,
    output reg [6:0]led
    );

always @*
begin
    case(hex)
        4'b0000 : led=7'b1111110;
        4'b0001 : led=7'b0110000;
        4'b0010 : led=7'b1101101;
        4'b0011 : led=7'b1111001;
        4'b0100 : led=7'b0110011;
        4'b0101 : led=7'b1011011;
        4'b0110 : led=7'b1011111;
        4'b0111 : led=7'b1110000;
        4'b1000 : led=7'b1111111;
        4'b1001 : led=7'b1111011;
        default : led=7'b0000000;
    endcase
end
endmodule




module multiplier(a2,a1,a0,b2,b1,b0,led_ten,led_one, ten, one);

input a0, a1, a2, b0, b1, b2;
wire p0,p1,p2,p3,p4,p5;
wire [2:0] stage0, stage1, stage2;
wire [2:0] sum1,sum2;
wire [5:0] sum_bcd;
reg [5:0] add, ayo;
reg w1, w2, w3, w4;
wire cout1, cout2;
output [6:0] led_ten, led_one;
output [3:0] ten, one;

// AND Gates
assign stage0[0] = a0&b0;
assign stage0[1] = a0&b1;
assign stage0[2] = a0&b2;
assign stage1[0] = a1&b0;
assign stage1[1] = a1&b1;
assign stage1[2] = a1&b2;
assign stage2[0] = a2&b0;
assign stage2[1] = a2&b1;
assign stage2[2] = a2&b2;

// Partial sums
threebitadder three1(1'b0, stage0[2],stage0[1],stage1[2],stage1[1],stage1[0],1'b0,sum1[2],sum1[1],sum1[0],cout1);
threebitadder three2(cout1,sum1[2],sum1[1],stage2[2],stage2[1],stage2[0],1'b0,sum2[2],sum2[1],sum2[0],cout2);

// Final Product
assign p0 = stage0[0];
assign p1 = sum1[0];
assign p2 = sum2[0];
assign p3 = sum2[1];
assign p4 = sum2[2];
assign p5 = cout2;

// Adding 6/12/18/24 depending on value of product (for BCD Conversion)
sixbitadder six1(p5,p4,p3,p2,p1,p0,add,1'b0,sum_bcd,cout);

reg [3:0] tenz;
reg [3:0] onez;
reg [5:0] idk;
reg Cout;

bcd_to_7seg bcd1(tenz, led_ten);
bcd_to_7seg bcd2(onez, led_one);

assign ten = tenz;
assign one = onez;

always @(p0,p1,p2,p3,p4,p5,sum_bcd, cout) begin
    w1= (~p5 & ~p4 & p3 & p1) | (~p5 & ~p4 & p3 & p2) | (~p5 & p4 & ~p3 & ~p2);             // 10 to 19
    w2 = (~p5 & p4 & ~p3 & p2) | (~p5 & p4 & p3 & ~p2) | (~p5 & p4 & p3 & p2 & ~p1);        // 20 to 29
    w3 = (~p5 & p4 & p3 & p2 & p1) | (p5 & ~p4 & ~p3);                                      // 30 to 39
    w4 = (p5 & p3) | (p5 & p4);                                                             // 40 to 49
        
    add = w4?6'b011000:(w3?6'b010010:(w2?6'b001100:(w1?6'b000110:6'b000000)));              // number to be added
    
    idk = sum_bcd;
    Cout = cout;
    tenz[1:0] = idk[5:4];       // ten's digit
    tenz[2] = Cout;             // in case of ten's digit = 4
    tenz[3] = 1'b0;             // always 0 since ten's digit <= 4
    onez = idk[3:0];            // one's digit
    
end

endmodule
