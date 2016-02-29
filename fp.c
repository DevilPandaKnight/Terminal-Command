#include "../jinUtility.h"
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
void dir_scan(char *path, char *file, linklist* list)
{
	struct   stat   s;
	DIR           *dir;
	struct   dirent   *dt;

	vector *v = charVector();
	pushStringToVector(path, -1, v);
	char *dirname = v->value;
	
	if(lstat(file,   &s)   <   0){
		freeList(list);
		printf("file %s does not exists.\n",file);
		exit(0);
	}
	
	if(S_ISDIR(s.st_mode)){
		popCharFromVector(v);
		pushStringToVector(file, 0, v);
		pushStringToVector("/", -1, v);
		dirname = v->value;
		if((dir   =   opendir(file))   ==   NULL){
			freeVector(v);
			printf("opendir      error\n");
			exit(4);
		}
		if(chdir(file)   <   0)   {
			freeVector(v);
			printf("chdir   error\n");
			exit(5);
		}
		while((dt   =   readdir(dir))   !=   NULL){
			if(dt->d_name[0]   ==   '.'){
				continue;
			}
			
			dir_scan(dirname, dt->d_name,list);
		}
		if(chdir("..")   <   0){
			freeVector(v);
			printf("chdir   error\n");
			return;
			exit(6);
		}
	}else{
		if (list != NULL){
		char* string = malloc(sizeof(char)*(strlen(dirname)+strlen(file)+1));
		strcpy(string,dirname);
		strcat(string,file);
		appendToList(&string, list);
		}
		else{
			printf("%s%s\n", dirname,file);
		}
	}
	freeVector(v);
}


linklist* getFileAddress(char* dir){
	int len = (int)strlen(dir);
	char path[len+1];
	memset(path,'\0',len+1);
	strcpy(path,dir);
	linklist *list = stringlinklist();
	if (dir[len-1]=='/'){
		path[len-1]='\0';
	}
	dir_scan("", path,list);
	return list;
}


void file_scan(char* dir){
	int len = (int)strlen(dir);
	char path[len+1];
	memset(path,'\0',len+1);
	strcpy(path,dir);
	if (dir[len-1]=='/'){
		path[len-1]='\0';
	}
	dir_scan("", path,NULL);
}

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

int findStringInList(linklist* l,char* s){
	char* temp;
	for (int i = 0;i<l->length;i++) {
		//printf("list: %s, conmmand: %s\n",temp,s);
		getListValueAtIndex(&temp, i, l);
		if (strstr(temp, s)) {
			return i;
		}
	}
	return -1;
}

void printDoc(unsigned char* string,size_t len,int delay){
	for (size_t i = 0;i < len;i++) {
		printf("%c",string[i]);
		if (delay!=0) {
			fflush(stdout);
			usleep(delay);
		}
	}
}

void dumpDoc(unsigned char* string, size_t len,int delay){
	if (len > 0xffffffff) {
		printf("file too large, program terminated.\n");
		exit(0);
	}
	size_t tempLen = (len<15)? 0:len-15;
	size_t j,i=0;
	int count;
	char buf[200];
	for (i = 0;i<tempLen;i+=16) {
		count = sprintf(buf,"%.8zx: ",i);
		for (j = 0;j<16;j++) {
			count += sprintf(buf+count,"%.2x ",string[i+j]);
		}
		buf[count++] = '|';
		buf[count++] = ' ';
		for (j = 0;j<16;j++) {
			char c = string[i+j];
			buf[count++] = (c>31 && c<127)? c:'.';
		}
		buf[count++] = '\n';
		printDoc((unsigned char*)buf, count, delay);
	}
	if (i<len) {
		count = sprintf(buf,"%.8zx: ",i);
		for (j = i;j<len;j++) {
			count += sprintf(buf+count,"%.2x ",string[j]);
		}
		while (count<58) {
			buf[count++] = ' ';
		}
		buf[count++] = '|';
		buf[count++] = ' ';
		for (j = i;j<len;j++) {
			char c = string[j];
			buf[count++] = (c>31 && c<127)? c:'.';
		}
		buf[count++] = '\n';
		printDoc((unsigned char*)buf, count, delay);
	}
}


void doNoFlag(linklist* l,ArgParser *p){
	ArgParser parser = *p;
	char* tempName;
	if(l==NULL){printf("no input files or path.\n"); exit(0);}
	for (int j = 0;j<parser.argc;j++) {
		int index = findStringInList(l, parser.args[j]);
		while (index != -1) {
			popFromListAtIndex(&tempName,index, l);
			free(tempName);
			index = findStringInList(l, parser.args[j]);
		}
	}
}

linklist* doInFlag(linklist* l,ArgParser* p){
	ArgParser parser = *p;
	char* tempName;
	if(l==NULL){printf("no input files or path.\n"); exit(0);}
	linklist* tempList = stringlinklist();
	for (int j = 0;j<parser.argc;j++) {
		int index = findStringInList(l, parser.args[j]);
		while (index != -1) {
			popFromListAtIndex(&tempName,index, l);
			appendToList(&tempName, tempList);
			index = findStringInList(l, parser.args[j]);
		}
	}
	freeList(l);
	if (tempList->length==0) {
		printf("no matched files.\n");
		free(tempList);
		exit(0);
	}
	return tempList;
}

#define MAXSPEED 20

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("File printing. Made By Jin.\n\t-no     --to exclude the files.\n\t-in\t--to only print the files you specified.\n\t-speed= --to set the printing speed, the default is 20.\n\t-d	--to dump the file in raw format.\n\t-name\t--print all the file names recursively under the folder.\n");
		return 0;
	}
	ArgParser parser[argc];
	int delay = 0;
	int count = argParser(argc, argv, parser);
	linklist* l = NULL;
	bool dumpFlag = false;
	bool nFlag = false;
	unsigned char in_no_flag = 0,in_no_index[2];
	for (int i = 0;i<count;i++) {
		if (strcmp(parser[i].commnd,"") == 0) {
			l = getFileAddress(argv[1]);
			if (l->length == 0) {exit(0);}
		}
		else if (strcmp(parser[i].commnd, "-no")==0) {
			if (in_no_flag == 0) {in_no_flag = 1;}
			else if(in_no_flag == 2){in_no_flag = 4;}
			in_no_index[0] = i;
		}
		else if (strcmp(parser[i].commnd, "-in")==0) {
			if (in_no_flag == 0) {in_no_flag = 2;}
			else if(in_no_flag == 1){in_no_flag = 3;}
			in_no_index[1] = i;
		}
		else if (strcmp(parser[i].commnd, "-d")==0) {
			dumpFlag = true;
			if (parser[i].argc != 0) {
				if(l!=NULL) freeList(l);
				l = getFileAddress(parser[i].args[0]);
				if (l->length == 0) {exit(0);}
			}
		}
		else if (strcmp(parser[i].commnd, "-name")==0) {
			nFlag = true;
			if (parser[i].argc != 0) {
				if(l!=NULL) freeList(l);
				l = getFileAddress(parser[i].args[0]);
				if (l->length == 0) {exit(0);}
			}
		}
		else if (strstr(parser[i].commnd, "-speed=")) {
			int speed = atoi(&(parser[i].commnd[7]));
			if (speed <= 0 || speed > MAXSPEED) {speed = MAXSPEED;}
			delay = (speed==MAXSPEED)? 0:80000/speed;
			if (parser[i].argc != 0) {
				if(l!=NULL) freeList(l);
				l = getFileAddress(parser[i].args[0]);
				if (l->length == 0) {freeList(l);l=NULL;}
			}
		}
		else{
			printf("no command named %s\n",parser[i].commnd);
			(l==NULL)? 0:freeList(l);
			exit(0);
		}
	}
	if (in_no_flag) {
		switch (in_no_flag) {
			case 1://only no
				doNoFlag(l, &parser[in_no_index[0]]);
				break;
			case 2://only in
				l = doInFlag(l, &parser[in_no_index[1]]);
				break;
			case 3://no first, in second
				doNoFlag(l, &parser[in_no_index[0]]);
				l = doInFlag(l, &parser[in_no_index[1]]);
				break;
			case 4://in first, no second
				l = doInFlag(l, &parser[in_no_index[1]]);
				doNoFlag(l, &parser[in_no_index[0]]);
				break;
			default:
				break;
		}
	}
	
	
	unsigned char* a;
	char* s;
	cRaise(l==NULL, "no input files or path.");
	while (!listEmpty(l)) {
		popListFront(&s,l);
		if (nFlag) {
			printDoc((unsigned char*)s, strlen(s), delay);
			printf("\n");
		}
		else {
			size_t len = readFromFile(s, "r", &a);
			len != 0? printf("\n/***** printing %s *****/\n\n",s):0;
			dumpFlag? dumpDoc(a, len, delay):printDoc(a, len, delay);
			(len==0)? 0:free(a);
		}
		free(s);
	}
	freeList(l);
	printf("\n");
	return 0;
}