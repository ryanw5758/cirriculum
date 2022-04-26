`timescale 1 ns / 100 ps

module traffic_light_tb ();
	 reg clk, flash, reset;
    wire NSG, NSY, NSR, EWG, EWY, EWR;
	 
	 wire [5:0] lights;
	 integer i, errors ;
	 	

	 
	 
	 
  task displayerror;
    begin
      errors = errors+1;
      $display("Error at time %d", $time);
    end
  endtask
 //
 
  traffic_light UUT ( .clk(clk), .flash(flash), .reset(reset), .NSG(NSG), .NSY(NSY), .NSR(NSR), .EWG(EWG), .EWY(EWY), .EWR(EWR));

 assign lights = {NSG, NSY, NSR, EWG, EWY, EWR};
 
 initial begin
	clk = 1;
	reset = 0;
	errors = 0;
	flash = 0;
	#10
	reset = 1;
	#10
	reset = 0;
	
	for (i=20; i<301; i = i+20) begin // 20 clock cycles
	#10
	clk = ~clk;
	#10
	clk = ~clk;
	
	end
	
	$display("Test done, after %d ns, %d errors\n",$time, errors);
 end
 
 
 always @(lights) begin
 
	case(i)
	20 : if (lights != 6'b001001) displayerror;
	40 : if (lights != 6'b100001) displayerror;
	60 : if (lights != 6'b010001) displayerror;
	80:  if (lights != 6'b001001) displayerror;
	100: if (lights != 6'b001100) displayerror;
	120: if (lights != 6'b001010) displayerror;
	140: if (lights != 6'b001001) displayerror;
	160: if (lights != 6'b100001) displayerror;
	180: if (lights != 6'b010001) displayerror;
	200: if (lights != 6'b001001) displayerror;
	220: if (lights != 6'b001001) displayerror;
	240: if (lights != 6'b000000) displayerror;
	260: if (lights != 6'b001001) displayerror;
	280: if (lights != 6'b000000) displayerror;
	300: if (lights != 6'b001001) displayerror;
	
	
	endcase
	end
	
 
 initial begin
   
 	flash = 0;
	#200;
	flash =1;
	
 
	
 end
 
 
  
 

endmodule
