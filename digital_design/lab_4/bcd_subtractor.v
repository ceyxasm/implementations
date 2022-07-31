`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/05/2022 10:50:03 PM
// Design Name: 
// Module Name: bcd_subtractor
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


//////bcd adder start


module half_adder(a,b,s,c);
input a,b;
output s,c;

assign s = a^b;
assign c = a&b;
endmodule



module full_adder(a,b,cin,s,cout);
input a,b,cin;
output s,cout;

half_adder H1(a,b,s1,c1);
half_adder H2(s1,cin,s,c2);
assign cout = c1|c2;
endmodule



module fourbitadder(a,b,c0,s,Cout);

input [3:0] a;  // vector for 4 bit input a
input [3:0] b;  // vector for 4 bit input b
input c0;       // the first carry input which is constant (= 0)
output [3:0] s; // final 4 bit sum output
output Cout;    // final carry output


full_adder F1(a[0],b[0],c0,s[0],c1);  
full_adder F2(a[1],b[1],c1,s[1],c2);
full_adder F3(a[2],b[2],c2,s[2],c3);
full_adder F4(a[3],b[3],c3,s[3],Cout);

endmodule

module bcdAdder(a,b,cin,sum,cout);

input [3:0] a,b;
input cin;
output [3:0] sum;
output cout;

wire [3:0] s1, temp;
wire c1;

fourbitadder four(a,b,cin,s1,c1);

assign c2 = c1 | s1[3]&s1[2] | s1[3]&s1[1];
assign temp[3] = 1'b0;
assign temp[0] = 1'b0;
assign temp[1] = c2;
assign temp[2] = c2;

assign cout = c2;

fourbitadder fourr(s1,temp,1'b0,sum,useless_carry);

endmodule

/////bcd adder end


/////adder substractor start


module adder_subtractor(a,b,m,sum,cout,v);
input [3:0] a,b;
input m;
output [3:0] sum;
output cout,v;

assign b0 = b[0]^m;
assign b1 = b[1]^m;
assign b2 = b[2]^m;
assign b3 = b[3]^m;

full_adder f0(a[0],b0,m,sum[0],c1);
full_adder f1(a[1],b1,c1,sum[1],c2);
full_adder f2(a[2],b2,c2,sum[2],c3);
full_adder f3(a[3],b3,c3,sum[3],cout);
assign v = cout^c3;                     // overflow

endmodule

/////adder substractor end

////tens complement start

module tens_complement(a,tenA, control);

input [3:0] a;
output [3:0] tenA;
input control;

reg [3:0] ten;
reg m;
always @(control)
begin
    if (control)begin
        ten = 4'b1010;
        m = 1'b1;
        end
    else
    begin
        ten = 4'b0000;
        m = 1'b0;
        end
end

adder_subtractor asub(ten, a, m, tenA, something);

endmodule


////tens complement end

module bcd_subtractor(a,b,diff,sign);

input [3:0] a,b;
output [3:0] diff;
output sign;

wire [3:0] tenB;
wire [3:0] df;

tens_complement tc(b,tenB,1'b1);

bcdAdder bla(a,tenB,1'b0,df,c1);

// logic to take 10's complement of final output based on sign of output

assign sign = ~c1;
tens_complement tcc(df, diff, sign);	

endmodule
