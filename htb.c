#include <stdio.h>
#include "../jinUtility/utility.h"
#include "../jinUtility/number.h"
#include "../jinUtility/container.h"

static char hex[] = {'A','a','B','b','C','c','D','d','E','e','F','f'};

static bool inhex(char c){
	for (int i = 0,len = sizeof(hex);i<len;i++) {
		if (hex[i]==c) {
			return true;
		}
	}
	return false;
}

char* htb(char* hex){
	cRaise(hex==NULL,"NULL input.");
	size_t len = strlen(hex);
	char c;
	char* temp = NULL;
	vector *v = charVector();
	for (int i = 0; i < len; ++i)
	{
		c = hex[i];
		if (isalpha(c) && inhex(c))
		{	
			c=tolower(c);
			temp = tobinary2(c-87);
			pushStringToVector(temp+28,0,v);
			free(temp);
		}
		else if(isdigit(c)){
			temp = tobinary2(c-48);
			pushStringToVector(temp+28,0,v);
			free(temp);
		}
		else{
			printf("this is not a hex number.\n");
			freeVector(v);
			return 0;
		}
	}
	pushToVector('\0',v);
	int i =0;
	len = v->currentSize-1;
	for (; i <len ; ++i)
	{
		if (((char*)v->value)[i]=='1')
		{
			break;
		}
	}
	if (i==len){i--;}
	temp = strdup((char*)(v->value)+i);
	freeVector(v);
	return temp;
}



int main(int argc, char const *argv[])
{
	cRaise(argc!=2,"inputs error.");
	char* a = htb((char*)argv[1]);
	if (a!=NULL) {
		printf("%s\n",a);
		free(a);
	}
	return 0;
}