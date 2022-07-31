module multiplier(num,op);
input [3:0] num;
output [6:0] op;
assign op = ((num<<1)<<1) + num;
endmodule