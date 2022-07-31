module test_alu;
wire [31:0] out;
reg [31:0] a,b;
reg [2:0] op;
alu uut(a,b,op,out);
initial
begin
$dumpfile("dump.vcd"); $dumpvars;  
a = 5; b = 3; op = 0;
#50 a = 5; b = 3; op = 1;
#50 a = 5; b = 3; op = 2;
#50 a = 5; b = 3; op = 3;
#50 a = 5; b = 3; op = 4;
#50 a = 5; b = 3; op = 5;
#50 a = 5; b = 3; op = 6;
#50 a = 5; b = 3; op = 7;
end
initial #500 $finish;
endmodule
