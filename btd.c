#include <stdio.h>
#include "../jinUtility/utility.h"
#include "../jinUtility/jinObject/mathEvaluator.h"

int main(int argc, char *argv[]) {
	cRaise(argc!=2, "inputs error.");
	printf("%.0f\n",binarySummation("m*2^i",argv[1], 0, -1));
}