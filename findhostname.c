#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("usage: hostname ip optional[+short]\n");
		printf("find the hostname under same network.\n");
		return 0;
	}
	if (argc == 2) {
		execlp("dig", "dig","-x",argv[1],"-p","5353","@224.0.0.251",NULL);
	}
	else {
		execlp("dig", "dig","-x",argv[1],"-p","5353","@224.0.0.251",argv[2],NULL);
	}
}