module test_bcd_adder_substractor;
wire [4:0] out;
wire negative;
reg [3:0] a,b;
reg operation;
bcd_adder_substractor uut(a,b,operation,out,negative);
initial
begin
$dumpfile("dump.vcd"); $dumpvars;
a = 5;b=7;operation = 1;
#20 a = 3;b=9;operation = 1;
#20 a = 12;b=9;operation = 0;
#20 a = 5; b = 2; operation = 1;
end
initial #100 $finish;
endmodule