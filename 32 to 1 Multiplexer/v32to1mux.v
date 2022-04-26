// 32:1 MUX (Structural Model)
// completed by Ryan White

module v32to1mux (X, XS, XEN, XOUT);
  input [31:0] X;
  input [4:0] XS;
  input XEN ;
  output XOUT;
  wire [3:0] XO;
  wire [3:0] EN_L;
  
  _2to4decoder U1 (.A0(XS[3]), .A1(XS[4]), .EN(XEN), .Y0(EN_L[0]), .Y1(EN_L[1]), .Y2(EN_L[2]), .Y3(EN_L[3]));
  v8to1mux U2 (.D(X[31:24]), .S(XS[2:0]), .EN(EN_L[0]), .Y(XO[0]));
  v8to1mux U3 (.D(X[23:16]), .S(XS[2:0]), .EN(EN_L[1]), .Y(XO[1]));
  v8to1mux U4 (.D(X[15:8]), .S(XS[2:0]), .EN(EN_L[2]), .Y(XO[2]));
  v8to1mux U5 (.D(X[7:0]), .S(XS[2:0]), .EN(EN_L[3]), .Y(XO[3]));
  
  or(XOUT, XO[0], XO[1], XO[2], XO[3]);
		
endmodule
