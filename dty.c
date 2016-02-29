#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Input:\n\tR_a:resistor between node b and c\n\tR_b:resistor between node a and c\n\tR_c:resistor between node a and b\n");
		printf("Output:\n\tR1:the node a to middle\n\tR2:the node b to middle\n\tR3:the node c to middle\n");
		return 0;
	}
	if (argc != 4) {
		printf("input error.\n");
		return 0;
	}
	double ra = atof(argv[1]);
	double rb = atof(argv[2]);
	double rc = atof(argv[3]);
	double r1,r2,r3;
	double temp = ra+rb+rc;
	printf("R1 = %g ohm\nR2 = %g ohm\nR3 = %g ohm\n",(rb*rc)/temp,(rc*ra)/temp,(ra*rb)/temp);
}