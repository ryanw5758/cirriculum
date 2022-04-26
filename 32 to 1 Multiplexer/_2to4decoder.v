//Lecture 4 Behavioral Model
//Ryan White

module _2to4decoder(A0, A1, EN, Y0, Y1, Y2, Y3);
	input A0, A1, EN;
	output Y0, Y1, Y2, Y3;
	reg Y0, Y1, Y2, Y3;
	
always @ (A0, A1, EN)
	if (EN == 1'b0)
		{Y3,Y2,Y1,Y0} = 4'B1111;
		
	else
		case ({A1, A0})
		2'B00: {Y3,Y2,Y1,Y0} = 4'B1000;
		2'B01: {Y3,Y2,Y1,Y0} = 4'B1101;
		2'B10: {Y3,Y2,Y1,Y0} = 4'B1011;
		2'B11: {Y3,Y2,Y1,Y0} = 4'B0111;
		default: {Y3,Y2,Y1,Y0} = 4'B1111;
		endcase
		
endmodule