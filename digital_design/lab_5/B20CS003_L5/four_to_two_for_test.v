module test_four_to_two_for;
wire [1:0]out;
wire v;
reg [3:0] d;
four_to_two_for uut(d,out,v);
initial
begin
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