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
module four_bit_adder(a,b,c,d,w,x,y,z,c3,c2,c1,c0,s);
        input a,b,c,d,w,x,y,z;
        output s,c0,c1,c2,c3;
        reg temp1,temp2,temp3;
        half_adder D1(d,z,s,temp1);
        full_adder D2(temp1,y,c,c0,temp2);
        full_adder D3(temp2,x,b,c1,temp3);
        full_adder D4(temp3,a,w,c2,c3);
endmodule
module cla_4_bit(input [3:0] a, 
        input [3:0] b,
        input cin, 
        output[3:0] s, 
        output cout);

        wire [3:0]c;
        wire [3:0]g;
        wire [3:0]p;
        half_adder ha1(a[0],b[0],p[0],g[0]);
        half_adder ha2(a[1],b[1],p[1],g[1]);
        half_adder ha3(a[2],b[2],p[2],g[2]);
        half_adder ha4(a[3],b[3],p[3],g[3]);
        assign c[0]=cin;
        assign #5 c[1]=g[0] | (p[0]&&c[0]);
        assign #5 c[2]=g[1] | (p[1]&&g[0]) | (p[1]&&p[0]&&c[0]);
        assign #5 c[3]=g[2] | (p[2]&&g[1]) | (p[2]&&p[1]&&g[0]) | (p[2]&&p[1]&&p[0]&&c[0]);
        assign #5 cout=g[3] | (p[3]&&g[2]) | (p[3]&&p[2]&&g[1]) | (p[3]&&p[2]&&p[1]&&g[0]) | (p[3]&&p[2]&&p[1]&&p[0]&&c[0]);
        assign #10 s[0]=p[0]^c[0];
        assign #10 s[1]=p[1]^c[1];
        assign #10 s[2]=p[2]^c[2];
        assign #10 s[3]=p[3]^c[3];
endmodule

module cla_32bit_implementation(
        input [31:0]a,
        input [31:0]b,
        output [31:0]s,
        output cout);
wire [0:7] c;
assign c[0]=0;
cla_4_bit cla1(a[3:0],b[3:0],c[0],s[3:0],c[1]);
cla_4_bit cla2(a[7:4],b[7:4],c[1],s[7:4],c[2]);
cla_4_bit cla3(s[11:8],c[3],a[11:8],b[11:8],c[2]);
cla_4_bit cla4(a[15:12],b[15:12],c[3],s[15:12],c[4]);
cla_4_bit cla5(a[19:16],b[19:16],c[4],s[19:16],c[5]);
cla_4_bit cla6(a[23:20],b[23:20],c[5],s[23:20],c[6]);
cla_4_bit cla7(a[27:24],b[27:24],c[6],s[27:24],c[7]);
cla_4_bit cla8(a[31:28],b[31:28],c[7],s[31:28],cout);
endmodule
