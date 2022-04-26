// Test bench for 32:1 MUX with active-high enable
//Ryan White

`timescale 1 ns / 100 ps
module v32to1mux_tb ();
  reg EN;
 reg [4:0] SEL; 
  reg [31:0] IN;
  wire  Y;
  integer i,k, errors;

  task displayerror;
    begin
      errors = errors+1;
      $display("Error: EN=%b, sel =%b, inputs = %b, XOUT=%b", EN, SEL, IN, Y);
    end
  endtask
 
  v32to1mux UUT ( .XEN(EN), .XS(SEL), .X(IN[31:0]), .XOUT(Y) );
  
  initial begin
    errors = 0;
    
	 for (k=0; k<25000; k=k+1) begin
	 for (i=0; i<32; i=i+1) begin
      EN = 0; SEL = i; #10 ;
      if (Y !== 0) displayerror;
      
		
      EN = 1; 
		IN = $random;
      #10
		if (Y !== IN[SEL[2:0]]) displayerror;
		
		end
 end
      $display("Test done, ran %d times, %d errors\n",k*i, errors);
		$display("completed by R. White");
    
  $stop(1);
  end
endmodule