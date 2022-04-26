module traffic_light (		
    input clk, flash, reset,
    output reg NSG, NSY, NSR, EWG, EWY, EWR
    );
	
	// NOTE: In retrospect, I find creating multiple cases for the same state makes better sense intuitively, but is inefficient in the ways of implementation.
	// If I revisited this project, I would change the logic to use one sole case for the state of both lights red.

	// Logic adapted from: https://www.fpga4student.com/2016/11/verilog-code-for-traffic-light-system.html
	// Created more states in order to simplify: one bit for each light

	localparam NSG_EWR = 6'b001100; // green NS, red EW
	localparam NSY_EWR = 6'b010100; // yellow NS, red EW
	localparam NSR_EWR = 6'b100100; // red NS, red EW
	localparam NSR_EWY = 6'b100010; // red NS, yellow EW
	localparam NSR_EWG = 6'b100001; // red NS, green EW
	localparam endState = 6'b100100; // both red, but next state will start next loop
	localparam flashRed = 6'b100100; // lights both red for flash state
	localparam flashOff = 6'b000000; // lights all off during flash sequence
	reg[5:0] currState, nextState;
	
	always @ (posedge clk or negedge reset)
	begin
			if (~reset)
				currState <= endState;
			else
				currState <= nextState;
			end
		always @ (*)
		begin
			case(currState)
				NSG_EWR: begin
					NSR = 1'b0;
					NSY = 1'b0;
					NSG = 1'b1;
					EWR = 1'b1;
					EWY = 1'b0;
					EWG = 1'b0;
					if (flash)
						nextState <= flashRed;
					else
						nextState <= NSY_EWR;
				end
				NSY_EWR: begin
					NSR = 1'b0;
					NSY = 1'b1;
					NSG = 1'b0;
					EWR = 1'b1;
					EWY = 1'b0;
					EWG = 1'b0;
					if (flash)
						nextState <= flashRed;
					else
						nextState <= NSR_EWR;
				end
				NSR_EWR: begin
					NSR = 1'b1;
					NSY = 1'b0;
					NSG = 1'b0;
					EWR = 1'b1;
					EWY = 1'b0;
					EWG = 1'b0;
					if (flash)
						nextState <= flashRed;
					else
						nextState <= NSR_EWG;
				end
				NSR_EWG: begin
					NSR = 1'b1;
					NSY = 1'b0;
					NSG = 1'b0;
					EWR = 1'b0;
					EWY = 1'b0;
					EWG = 1'b1;
					if (flash)
						nextState <= flashRed;
					else
						nextState <= NSR_EWY;
				end
				NSR_EWY: begin
					NSR = 1'b1;
					NSY = 1'b0;
					NSG = 1'b0;
					EWR = 1'b0;
					EWY = 1'b1;
					EWG = 1'b0;
					if (flash)
						nextState <= flashRed;
					else
						nextState <= endState;
				end
				endState: begin
					NSR = 1'b1;
					NSY = 1'b0;
					NSG = 1'b0;
					EWR = 1'b1;
					EWY = 1'b0;
					EWG = 1'b0;
					if (flash)
						nextState <= flashRed;
					else
						nextState <= NSG_EWR;
				end
				flashRed: begin
					NSR = 1'b1;
					NSY = 1'b0;
					NSG = 1'b0;
					EWR = 1'b1;
					EWY = 1'b0;
					EWG = 1'b0;
					if (flash)
						nextState <= flashOff;
					else
						nextState <= endState;
				end
				flashOff: begin
					NSR = 1'b0;
					NSY = 1'b0;
					NSG = 1'b0;
					EWR = 1'b0;
					EWY = 1'b0;
					EWG = 1'b0;
					if (flash)
						nextState <= flashRed;
					else
						nextState <= endState;
				end
			default: nextState <= endState;
			endcase
			end


endmodule
