module test_mealy();
reg clk,rst;
wire [7:0] bits;
wire x; // newly generated input bit;
LFSR lfsr2(bits,clk,rst,x);
parameter n_states = 3;
parameter m = 2;
wire [m-1:0] curr;
wire y;
mealy mealy1(clk,rst,curr,x,y);
initial
begin
rst=0;
#2 rst=1; clk=1;
for (integer i = 0; i < 20; i = i + 1)
begin
#2 clk = clk ^ 1;
#2 clk = clk ^ 1;
end
end
initial #100 $finish;
endmodule
