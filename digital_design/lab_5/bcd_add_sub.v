
module bcd_adder_substractor(a,b,operation,out,negative);
input [3:0] a,b;
input operation;
output reg [4:0] out;
output reg negative;
always @(operation)
begin
if(operation)
begin
out = a+b;
negative = 0;
end
else
begin
if(a>=b)
begin
out = a-b;
negative = 0;
end
else
begin
out = b-a;
negative = 1;
end
end
end
endmodule
