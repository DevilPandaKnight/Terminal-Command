#include <stdio.h>
#include "../jinUtility/jinObject/mathEvaluator.h"

long gcd(long a,long b){
	if (a < b) {
		long temp = a;
		a = b;
		b = temp;
	}
	if (a % b == 0) {
		return b;
	}
	else {
		return gcd(b, a%b);
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Arguments should be 2.\n");
		return 0;
	}
	long a = (long)evaluate(argv[1]);
	long b = (long)evaluate(argv[2]);
	printf("gcd(%ld,%ld)=%ld\n",a,b,gcd(abs(a),abs(b)));
	return 0;
}