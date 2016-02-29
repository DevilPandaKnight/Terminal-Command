#include <stdio.h>
#include "../jinUtility/jinObject/mathEvaluator.h"
#include "../jinUtility/container.h"
#include "../jinUtility/jinMath.h"
#include "../jinUtility/utility.h"
#include "../jinUtility/number.h"
#include "../jinUtility/jinString.h"


void setPrecision(char printLabel[],char* num){
	char* temp = strstr(num, "=");
	if (temp==NULL) {
		return;
	}
	temp=temp+1;
	if (temp[0]=='\0') {
		return;
	}
	int i= 0;
	if (strlen(temp)>3) {
		printf("can't set precision to be greater than 16.\n");
		return;
	}
	while (temp[i]!='\0') {
		if (!isdigit(temp[i])) {
			return;
		}
		i++;
	}
	i = atoi(temp);
	if (i>16) {
		printf("can't set precision to be greater than 16.\n");
		return;
	}
	sprintf(printLabel,"%%.%dg\n",i);
	return;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Math program made by Jin.\n-p set precision.\n\tex. -p=2 sqrt(2)=1.4\n-e or type math expression will evaluate the expression.\n\tex. \"sin(pi)\" will give the result 0.\n-s will sum the expression.\n\tex. \"1/n 1 10\" will sum 1/n from 1 to 10\n-bs will sum binary expression.\n\tex. \"m*2^i 1000 0 3\" will convert 1000b to 8 in decimal.\n-i will do inverting sum.\n\tex. \"1 2 3\" will have result 1/(1/1+1/2+1/3)\n-sr will evaluate the root(s) of a second polynomial ax^2+bx+c=0\n\tex. \"1 -1 0\" is corresponding a=1,b=-1,c=0 and the roots is 1 and 0\n");
		return 0;
	}
	char* flag[argc-1];
	char* equation[argc-1];
	int f_count = 0;
	int e_count = 0;
	char printLabel[10] = "%f\n";
	for (int i = 1;i<argc;i++) {
		if (argv[i][0] == '-' && isalpha(argv[i][1])) {
			if (strstr(argv[i],"-p=")) {
				setPrecision(printLabel, argv[i]);
				continue;
			}
			flag[f_count++] = argv[i];
		}
		else {
			equation[e_count++] = argv[i];
		}
	}
	if (f_count > 1) {
		printf("can only have one flag per input except -p\n");
		return 0;
	}
	if (e_count<1) {
		printf("error in inputs.\n");
		return 0;
	}
	if (f_count == 0 && e_count != 0) {
		printf(printLabel,evaluate(equation[0]));
		return 0;
	}
	if (strcmp(flag[0],"-e")==0) {
		char* expression = equation[0];
		double r = evaluate(equation[0]);
		printf(printLabel,r);
		while (1) {
			printf(">> ");
			expression = getstring();
			if (expression == NULL) {
				continue;
			}
			if (strcmp(expression, "q")==0 || strcmp(expression, "quit")==0) {
				free(expression);
				return 0;
			}
			else if (strcmp(expression, "cl")==0 || strcmp(expression, "clear")==0) {
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				free(expression);
				continue;
			}
			r = evaluate(expression);
			printf(printLabel,r);
			free(expression);
		}
	}
	else if (strcmp(flag[0],"-s")==0) {
		int a,b;
		sscanf(equation[1], "%d",&a);
		sscanf(equation[2], "%d",&b);
		printf(printLabel,summation(equation[0], a, b));
	}
	else if (strcmp(flag[0],"-bs")==0) {
		cRaise(e_count!=4, "inputs not correct.");
		int a,b;
		sscanf(equation[2], "%d",&a);
		sscanf(equation[3], "%d",&b);
		printf(printLabel,binarySummation(equation[0],equation[1], a, b));
	}
	else if (strcmp(flag[0],"-sr")==0) {
	cRaise(e_count!=3, "inputs not correct.");
	double a,b,c;
	double root1,root2;
	sscanf(equation[0], "%lf",&a);
	sscanf(equation[1], "%lf",&b);
	sscanf(equation[2], "%lf",&c);
	dataType t = secondPolyRoot(a,b,c,&root1,&root2);
	char tstr[1024];
	printLabel[strlen(printLabel)-1]='\0';
	(t==complexType)? sprintf(tstr,"root1 = %s+%si\nroot2 = %s-%si\n",printLabel,printLabel,printLabel,printLabel):sprintf(tstr,"root1 = %s\nroot2 = %s\n",printLabel,printLabel);
	(t==complexType)? printf(tstr,root1,root2,root1,root2):printf(tstr,root1,root2);
	
	}
	else if (strcmp(flag[0],"-i")==0) {
		cRaise(e_count<1, "not enough arguments.");
		vector *v = charVector();
		pushStringToVector("1/(", 0, v);
		for (int i = 0;i<e_count;i++) {
			pushStringToVector("(1/", 0, v);
			pushStringToVector(equation[i], 0, v);
			pushStringToVector(")+", 0, v);
		}
		popCharFromVector(v);
		pushStringToVector(")", -1, v);
		printf(printLabel,evaluate(v->value));
		freeVector(v);
	}
}