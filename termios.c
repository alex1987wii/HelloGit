#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(void)
{
	struct termios term;
	if(!isatty(STDIN_FILENO))
	{
		perror("open failed");
		exit(0);
	}
	tcgetattr(STDIN_FILENO,&term);
	switch(term.c_cflag & CSIZE)
	{
		case CS5:
			printf("cs5\n");
		break;
		case CS6:
		printf("CS6\n");
		break;
		case CS7:
		printf("CS7\n");
		break;
		case CS8:
		printf("CS8\n");
		break;
	}

}
