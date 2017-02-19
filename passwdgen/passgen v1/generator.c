#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "password.h"

int passwdLength = 8;    //global for PASSWORD.C as well

int main(int argc, char * argv[])
{
	char * pass_write;
	char pass_read[passwdLength];
	int pid;
	int w_fifo, r_fifo;	//FIFO descriptors

	unlink("pswrds");
	if(mkfifo("pswrds", O_RDWR) == -1) {
		printf("Cannot create FIFO\n");
		exit(1);
	}
	chmod("pswrds", 0660);
	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}
	else if (pid > 0) {	//parent - client
		if ((r_fifo = open("pswrds", O_RDONLY)) == -1) {
			perror("fifo open");
			exit(1);
		}
		while (wait(NULL) != pid)
			;
		read(r_fifo, pass_read, passwdLength);
		printf("New password is %s\n", pass_read);
		close(r_fifo);
	}
	else if (pid == 0) {	//child - server
		if ((w_fifo = open("pswrds", O_WRONLY)) == -1) {
                        perror("fifo open");
                        exit(1);
                }
		pass_write = password();
		write(w_fifo, pass_write, passwdLength);
		close(w_fifo);
		exit(0);
	}

	return 0;
}
