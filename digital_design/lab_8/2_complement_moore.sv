module moore(clk,rst,curr,x,y);
input x,clk,rst;
output reg [1:0] curr;
output reg y;
always @(negedge rst,negedge clk)
begin
if(!rst)
curr = 0; // starting state
else
begin
if(curr == 0)
curr = x ? 1 : 0;
else if(curr == 1)
curr = x ? 2 : 1;
else if (curr == 2)
curr = x ? 2 : 1;
// error handling
else
curr = 0;
case(curr)
0: y = 0;
1: y = 1;
2: y = 0;
default: y = 0;
endcase
end
end
endmodule
