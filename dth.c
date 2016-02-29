#include <stdio.h>
#include "../jinUtility/utility.h"
#include "../jinUtility/jinObject/mathEvaluator.h"

int main(int argc, char *argv[]) {
	cRaise(argc!=2, "inputs error.");
	unsigned long a = (unsigned long)evaluate(argv[1]);
	printf("%lX\n",a);
}