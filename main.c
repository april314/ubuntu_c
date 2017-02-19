//this (probably) opens a file , the name is read from stdin
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/file.h>
#include <stdlib.h>

main(int argc, char * argv[])
{
	int fd, i;
	char * filename;
	if (argc > 1) {
		filename = malloc(strlen(argv[1]+1));
		for (i = 0; argv[1][i] != '\0'; i++) {
			filename[i] = argv[1][i];
		}
		filename[i] = '\0';
		fd = open(filename, O_RDONLY);
		if (fd == -1) {
			printf("Error %d\n\n", errno);
			perror("main");
		}
		else {
			printf("File exixts, its FD = %d\n\n", fd);
			close(filename);
		}
	}
	else {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
}
