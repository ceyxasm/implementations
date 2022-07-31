`timescale 1ns / 1ps
module evm(vote1,vote2,enable,cand1,cand2,voting_status);
parameter n = 4;
input vote1,vote2,enable,voting_status;
output reg [n-1:0] cand1, cand2;
wire enable;
initial
 begin
   cand1 = 0;
   cand2 = 0;
 end
always @(*)
begin
 if(enable)
  begin
   $display("Please press the button to caste your vote");
   if(vote1)
     begin
       $display("You have voted");
       cand1 = cand1 + 1;
     end
   
   else if(vote2)
     begin
       $display("You have voted");
       cand2 = cand2 + 1;
     end
   else
      $display("Please vote properly");
 end
 else
   begin
     $display("Permission denied");
   end
end
always @(*)
 begin
  if(voting_status)
   $display("Voting still on");
  else
    begin
      $display("Votes for first candidate %d" , cand1);
      $display("Votes for second candidate %d" , cand2);
    end
end     
endmodule
