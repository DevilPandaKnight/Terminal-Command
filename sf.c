#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../jinUtility/container/stack.h"
#define MAXARG 10
typedef struct 
{
	int argc;
	char* commnd;
	char* args[MAXARG];
}ArgParser;

//take argc,argv(do not modify argc and argv from main) from main
//return the number of command read(the form of -p or -p= or direct input)
//store the parsed command along with the args in Parser array  
int argParser(int argc, char* argv[],ArgParser Parser[]){
	int count = -1;
	int argcCount = 0;
	bool hascommand = false;
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0]=='-')
		{
			count++;
			Parser[count].commnd = argv[i];
			Parser[count].argc = 0;
			argcCount = 0;
			hascommand = true;
		}
		else{
			if (argcCount == MAXARG)
			{
				printf("too many args, the max args is 10.\n");
				continue;
			}
			if (!hascommand)
			{
				count++;
				Parser[count].commnd = "";
				hascommand = true;
			}
			Parser[count].args[argcCount] = argv[i];
			argcCount++;
			Parser[count].argc = argcCount;
		}
	}
	return count+1;
} 

typedef enum{
	s_c=0,
	s_l,
	s_u
}commnd;
typedef struct 
{
	unsigned char bitset[32];
	unsigned char numberOfBitToSet;
	unsigned char bitclear[32];
	unsigned char numberOfBitToClear;
}bitOperArg;

#define setbit(b,n) {b|=(1U<<n);}
#define clearbit(b,n) {b&=~(1U<<n);}

void bitOper(bitOperArg arg,unsigned int* mask){
	unsigned oldMask = *mask;
	for (int i = 0; i < arg.numberOfBitToSet; ++i)
	{
		setbit(oldMask,arg.bitset[i]);
	}
	for (int i = 0; i < arg.numberOfBitToClear; ++i)
	{
		clearbit(oldMask,arg.bitclear[i]);
	}
	*mask = oldMask;
}

typedef struct
{
	char* command;
	unsigned int mask;
}commandMask;

commandMask cm[]={
	{"c",0x00000001},
	{"u",0x00000002},
	{"l",0x00000004},

};


void setMask(char* commnd,unsigned int* mask){
	unsigned int oldMask = *mask;
	if (strcmp(commnd,"-c")==0){
		
	}
	else if(strcmp(commnd,"-l")==0){

	}
	else if(strcmp(commnd,"-u")==0){
		
	}
	*mask = oldMask;
}




int main(int argc, char *argv[]) {
	FILE* fp = NULL;
	if (argc==1)
	{
			printf("Print string in a formatted manner. Made By Jin.\n\t-c capitalize the first character.\n\t-l all lower case.\n\t-u all upper case.\n");
		return 0;
	}
	ArgParser Parser[argc];
	int count = argParser(argc,argv,Parser);
	/*for (int i = 0;i<count;i++) {
		printf("command: %s, args: ",Parser[i].commnd);
		for (int j = 0;j<Parser[i].argc;j++) {
			printf("%s ",Parser[i].args[j]);
		}
		printf("\n");
	}*/
	unsigned int mask = 0;
	char* string = NULL;
	for (int i = 0; i < count; ++i)
	{
		//setMask(Parser[i].commnd,&mask);
		if (strcmp(Parser[i].commnd,"-c")==0){
			for (int j = 0;j<Parser[i].argc;j++) {
				string = Parser[i].args[j];
				for (int k = 1,len = strlen(string);k<len;k++) {
					string[k] = tolower(string[k]);
				}
				string[0] = toupper(string[0]);
				printf("%s ",string);
			}
			printf("\n");
		}
		else if(strcmp(Parser[i].commnd,"-l")==0){
			for (int j = 0;j<Parser[i].argc;j++) {
				string = Parser[i].args[j];
				for (int k = 0,len = strlen(string);k<len;k++) {
					string[k] = tolower(string[k]);
				}
				printf("%s ",string);
			}
			printf("\n");
		}
		else if(strcmp(Parser[i].commnd,"-u")==0){
			for (int j = 0;j<Parser[i].argc;j++) {
				string = Parser[i].args[j];
				for (int k = 0,len = strlen(string);k<len;k++) {
					string[k] = toupper(string[k]);
				}
				printf("%s ",string);
			}
			printf("\n");
		}
		else {
			printf("no command %s was found.\n",Parser[i].commnd);
		}
	}
	exit(0);
}
