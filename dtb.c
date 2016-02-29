#include <stdio.h>
#include "../jinUtility/utility.h"
#include "../jinUtility/number.h"
#include "../jinUtility/jinObject/mathEvaluator.h"

int main(int argc, char *argv[]) {
	cRaise(argc!=2, "inputs error.");
	printBinaty((long long)evaluate(argv[1]));
}