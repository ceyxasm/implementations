module test_multiplier;
reg [3:0] num;
wire [6:0] op;
multiplier uut(num,op);
initial
begin
$dumpfile("dump.vcd"); $dumpvars;
num = 5;
#10 num = 6;
#10 num = 4;
#10 num = 1;
#10 num = 2;
#10 num = 3;
#10 num = 9;
end
initial #100 $finish;
endmodule
