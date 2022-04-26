// 8:1 MUX with active-low enable
// completed by Ryan White

module v8to1mux (D, S, EN, Y);
  input [7:0] D;
  input [2:0] S;
  input EN;
  output reg Y;
  
  always @ (*)
  begin
  if(EN == 1'b0)
  begin
  if (S == 0)
		Y = D[0];
  if (S == 1)
		Y = D[1];
  if (S == 2)
		Y = D[2];
  if (S == 3)
		Y = D[3];
  if (S == 4)
		Y = D[4];
  if (S == 5)
		Y = D[5];
  if (S == 6)
		Y = D[6];
  if (S == 7)
		Y = D[7];

  /*case (S[0] & S[1] & S[2])
  3'b000: Y = D[0];
  3'b001: Y = D[1];
  3'b010: Y = D[2];
  3'b011: Y = D[3];
  3'b100: Y = D[4];
  3'b101: Y = D[5];
  3'b110: Y = D[6];
  3'b111: Y = D[7];
  default: Y = 1'b0;
  endcase*/
  
  end else begin
  Y = 1'b0;
  end
  end
endmodule
