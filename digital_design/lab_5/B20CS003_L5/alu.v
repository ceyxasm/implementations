module alu(a,b,op,out);
input [31:0] a,b;
input [2:0] op;
output reg [31:0] out;
always @*
begin
case(op)
0: out = 0;
1: out = a+b;
2: out = a-b;
3: out = a << 1;
4: out = a >> 1;
5: out = a & b;
6: out = a|b;
7: out = a^b;
endcase
end
endmodule