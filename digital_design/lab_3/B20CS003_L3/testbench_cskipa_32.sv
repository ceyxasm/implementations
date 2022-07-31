module test_csa_32_bit;
wire [31:0]s;
wire cout;
reg [31:0]a;
reg [31:0]b;
cskipa_32bit_implementation cskipa32(a,b,s,cout);
initial
    begin
    $dumpfile("dump.vcd"); $dumpvars;
    a=32'b00000000000000000000000000000000;
    b=32'b00000000000000000000000000000000;
    end
  always #100 b = b+ 1'b1;
  always #100 a = a+ 2'b11;
initial #6000 $finish;
endmodule
