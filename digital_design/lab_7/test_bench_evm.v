`timescale 1ns / 1ps

module test_bench_evm();
parameter n = 4;
reg enable , voting_status, vote1, vote2;
wire [n-1:0] cand1, cand2;
//wire [6:0] led1, led2;
evm EVM(vote1, vote2, enable, cand1, cand2, voting_status);
initial
 begin
 voting_status = 1;
 enable = 0;
 vote1 = 0;
 vote2 = 0;
 
 #1 enable = 1;
 #1 vote1 = 1;
 
 #10 enable = 1;
 #5 vote1 = 1;
 
 #10 enable = 1;
 #1 vote2 = 1;
 
 #10 enable = 1;
 #5 vote2 = 1;
 
 #15 voting_status = 0;
 end
 
always @(negedge enable)
 begin
  vote1 = 0;
  vote2 = 0;
 end
 
always @(posedge vote1, posedge vote2)
 begin
  if(enable)
   #1 enable = 0;
  else
   begin
    #1 vote1 = 0; vote2 = 0;
   end
 end
 
always@ (*)
if(enable)
 begin
  #4 enable = 0;
 end
 
initial #50 $finish;
endmodule
