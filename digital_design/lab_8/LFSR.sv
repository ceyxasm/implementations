// Code your design here
module LFSR(bits, clk, rst, out);
input clk,rst;
output reg [7:0] bits;
output reg out;
always @(negedge rst,negedge clk)
begin
if (!rst)
bits = 170;
else
begin
out = bits[0];
bits = bits >> 1;
bits[7] = bits[4] ^ bits[3] ^ bits [2] ^ bits[0];
end
end
endmodule