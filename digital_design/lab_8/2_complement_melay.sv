module mealy(clk,rst,curr,x,y);
input clk,rst,x;
output reg [1:0] curr;
output reg y;
always @(negedge rst,negedge clk)
begin
if(!rst)
curr = 0;
else
begin
if (curr == 0)
begin
if(x == 0)
begin
curr = 0;
y = 0;
end
else
begin
curr = 1;
y = 1;
end
end
else if(curr == 1)
begin
if(x == 0)
begin
curr = 1;
y = 1;
end
else
begin
curr = 1;
y = 0;
end
end
else
curr = 0;
end
end
endmodule
