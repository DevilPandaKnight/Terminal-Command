#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Input:\n\tR1:the node a to middle\n\tR2:the node b to middle\n\tR3:the node c to middle\n");
		printf("Output:\n\tR_a:resistor between node b and c\n\tR_b:resistor between node a and c\n\tR_c:resistor between node a and b\n");
		return 0;
	}
	if (argc != 4) {
		printf("input error.\n");
		return 0;
	}
	double r1 = atof(argv[1]);
	double r2 = atof(argv[2]);
	double r3 = atof(argv[3]);
	double ra,rb,rc;
	double temp = r1*r2+r2*r3+r3*r1;
	printf("R_a = %g ohm\nR_b = %g ohm\nR_c = %g ohm\n",temp/r1,temp/r2,temp/r3);
}