// Test bench for 8:1 MUX with active-low enable

`timescale 1 ns / 100 ps
module v8to1mux_tb ();
  reg EN;
 reg [2:0] SEL; 
  reg [7:0] IN;
  wire  Y;
  integer i,k, errors;

  task displayerror;
    begin
      errors = errors+1;
      $display("Error: EN=%b, sel =%b, inputs = %b, Y=%b", EN, SEL, IN, Y);
    end
  endtask
 
  v8to1mux UUT ( .EN(~EN), .S(SEL), .D(IN), .Y(Y) );
  
  initial begin
    errors = 0;
    
	 for (k=0; k<25000; k=k+1) begin
	 for (i=0; i<8; i=i+1) begin
      EN = 0; SEL = i; #10 ;
      if (Y !== 0) displayerror;
      
		
      EN = 1; 
		IN = $random % 256;
      #10
		if (Y !== IN[SEL]) displayerror;
		
		end
 end
      $display("Test done, ran %d times, %d errors\n",k*i, errors);
    
  $stop(1);
  end
endmodule