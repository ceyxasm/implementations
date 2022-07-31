module mux(i1,i2,i3,i4,op,control);
input i1,i2,i3,i4;
input [1:0] control;
output reg op;
always @*
begin
case(control)
2'b00: op = i1;
2'b01: op = i2;
2'b10: op = i3;
2'b11: op = i4;
default : op=1'bz;
endcase
end
endmodule
module barrel_shifter(w,s,y);
input [3:0] w;
input [1:0] s;
output [3:0] y;
mux m1(w[3],w[0],w[1],w[2],y[3],s);
mux m2(w[2],w[3],w[0],w[1],y[2],s);
mux m3(w[1],w[2],w[3],w[0],y[1],s);
mux m4(w[0],w[1],w[2],w[3],y[0],s);
endmodule
