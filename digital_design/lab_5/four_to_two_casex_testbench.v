module test_four_to_two_casex;
wire [1:0]out;
wire v;
reg [3:0] d;
four_to_two_casex uut(d,out,v);
initial
begin
  $dumpfile("dump.vcd"); $dumpvars;
d=5;
#10 d = 7;
#10 d = 10;
#10 d = 12;
#10 d = 6;
#10 d = 2;
#10 d = 14;
end
initial #100 $finish;
endmodule