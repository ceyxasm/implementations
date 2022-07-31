module four_to_two_casex(d,out,v);
input [3:0] d;
output reg v;
output reg [1:0] out;
always@(d)
begin
casex(d)
4'b1xxx: out = 2'b11;
4'b01xx: out = 2'b10;
4'b001x: out = 2'b01;
4'b0001: out = 2'b00;
default: out = 2'bzz;
endcase
if(d==4'b0000)
begin
assign v = 1'b0;
end
else
begin
assign v = 1'b1;
end
end
endmodule
