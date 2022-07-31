module test_barrel_shifter;
wire [3:0] y;
reg [3:0] w;
reg [1:0] s;
barrel_shifter bs(w,s,y);
initial
begin
w=5;s=0;
#50 w=5; s = 1;
#50 w=5; s = 2;
#50 w=5; s = 3;
#50 w=7; s = 0;
#50 w=7; s = 1;
#50 w=7; s = 2;
#50 w=7; s = 3;
end
endmodule