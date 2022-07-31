module four_to_two_for(d,out,v);
input [3:0] d;
output reg v;
output reg [1:0] out;
integer k;
always @(d)
begin
out=2'bxx;
v = 1'b0;
for(k = 0;k <4;k= k+1)
begin
if (d[k])
begin
out=k;
v=1'b1;
end
end
end
endmodule