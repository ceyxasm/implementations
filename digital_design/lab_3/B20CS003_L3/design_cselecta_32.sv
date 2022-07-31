module half_adder(a,b,s,c);
  input a,b;
  output s,c;
  assign #10 s = a^b;
  assign #5 c =a&b;
endmodule
module full_adder(a,b,c,s,c1);
  input a,b,c;
  output s,c1;
  reg w,x,y,z;
  half_adder H1(a,b,w,x);
  half_adder H2(w,c,s,z);
  half_adder H3(z,x,c1,y);
endmodule
/*
* a) Carry Look Ahead Adder
*b) Carry Skip Adder
*c) Carry Select Adder
*/
module csea(
        input [3:0] a,
        input [3:0]b,
        input cin,
        output [3:0]s,
        output cout);
wire c0,c1,c2,s20,s30,s21,s31,c20,c21,c30,c31;
assign c0=cin;
full_adder l1(a[0],b[0],c0,s[0],c1);
full_adder l2(a[1],b[1],c1,s[1],c2);
full_adder u02(a[2],b[2],1'b0,s20,c20);
full_adder u03(a[3],b[3],c20,s30,c30);
full_adder u12(a[2],b[2],1'b1,s21,c21);
full_adder u13(a[3],b[3],c21,s31,c31);
assign s[2]= (!c2?s20:s21);
assign s[3]= (!c2?s30:s31);
assign cout= (!c2?c30:c31);
endmodule


module csea_32bit_implementation(input [31:0]a,
       input [31:0]b,
       output [31:0]s,
       cout);
wire [0:7] c;
assign c[0]=0;
csea csea_block_number_1(a[3:0],b[3:0],c[0],s[3:0],c[1]);
csea csea_block_number_2(a[7:4],b[7:4],c[1],s[7:4],c[2]);
csea csea_block_number_3(a[11:8],b[11:8],c[2],s[11:8],c[3]);
csea csea_block_number_4(a[15:12],b[15:12],c[3],s[15:12],c[4]);
csea csea_block_number_5(a[19:16],b[19:16],c[4],s[19:16],c[5]);
csea csea_block_number_6(a[23:20],b[23:20],c[5],s[23:20],c[6]);
csea csea_block_number_7(a[27:24],b[27:24],c[6],s[27:24],c[7]);
csea csea_block_number_8(a[31:28],b[31:28],c[7],s[31:28],cout);
endmodule

