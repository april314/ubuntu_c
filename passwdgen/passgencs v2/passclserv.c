//this small guy is a server-client utility that automatically finds out what it is (a S or a C)
//a server creates passwords, a client gets them and prints them on terminal
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>	//S_IFIFO mknod()
#include <fcntl.h>
#include <signal.h>
#include "password.h"

int fd, server = 0;
char * newpass;
void intHandle();

int main(int argc, char * argv[])
{
	int passwdLength = 8;
	int numb;
	char * newpass;

	//try opening FIFO as CLIENT
	fd = open("pswrds", O_RDONLY);

	//if it does not exist, than you are a server and you are to create it
	if (fd == -1) {
		server = 1;	//set server-flag
		mknod("pswrds", S_IFIFO, 0);
		chmod("pswrds", 0660);
		fd = open("pswrds", O_RDWR);

		//and create password, writing it into FIFO
		while (1) {
		    //if pipe is empty
		    //if (read(fd, newpass, 0) == -1) {
			newpass = password(passwdLength);
			numb = write(fd, newpass, passwdLength);
			if (numb == -1)
			    perror("Writing pass");
			else
			    printf("Server's written %d-character pass\n", numb);
		    //}
			signal(SIGINT | SIGTERM, intHandle);
		    sleep(8);
		}
	}
	else {
		newpass = malloc(passwdLength);
	      	while (1) {
			numb = read(fd, newpass, passwdLength);
			if (numb == -1)
				perror("Reading pass");
			else
				printf("Client's got the password: %s\n", newpass);
			signal(SIGINT | SIGTERM, intHandle);
			sleep(5);
	      }
	}
	return 0;
}

void intHandle()
{
	free(newpass);
	close(fd);
	if (server) {
		unlink("pswrds");
	}
	exit(0);
}
