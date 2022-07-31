`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2022 14:08:33
// Design Name: 
// Module Name: two_player_buzzer
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module two_player_buzzer(led1, led2, control, buzzer);
input buzzer, control; //buzzer 0 means first person, buzzer 1 means second person
output reg led1, led2;

bufif1(led, buzzer, control); //if control is 0, led=Z else led=buzzer

always @*
    begin
        led1=0;
        led2=0;
        if (led== 1'b0)begin
            led1=1;
            led2=1'bZ;
            end
        else if (led==1'b1) begin
            led2=1;
            led1=1'bZ;
            end
    end
endmodule
