#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../jinUtility/utility.h"

static char hex[] = {'A','a','B','b','C','c','D','d','E','e','F','f'};

bool inhex(char c){
	for (int i = 0,len = sizeof(hex);i<len;i++) {
		if (hex[i]==c) {
			return true;
		}
	}
	return false;
}

double htd(char* str){
	size_t len = strlen(str);
	double result = 0;
	size_t count = len-1;
	int num;
	char c;
	for (int i = 0;i<len;i++) {
		c = str[count];
		if (isalpha(c) && inhex(c)) {
			c = tolower(c);
			num = c - 87;
		}
		else if(isdigit(c)){
			num = c-48;
		}
		else {
			cRaise(true, "input is not a hex number.");
			return 0;
		}
		result += num*pow(16, i);
		count--;
	}
	return result;
}

int main(int argc, char *argv[]) {
	cRaise(argc!=2, "inputs error.");
	printf("%.0f\n",htd(argv[1]));
}