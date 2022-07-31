// Code your testbench here
// or browse Examples
module test_LFSR();
reg clk,rst;
wire [7:0]bits;
wire out;
LFSR lfsr1(bits,clk,rst,out);
initial
begin
rst = 0;
#2 rst = 1 ; clk=1;
for (integer i=0 ; i<20 ; i=i+1)
begin
#2 clk = clk^1;
#2 clk = clk^1 ;
end
end
initial #50 $finish;
endmodule
