#include "pipex.h"
//pipe()
//fork()
//dub2()
//execve()



void printerror(char *str)
{
	perror(str);
	exit(0);
}

int main(int argc, char **argv)
{
	t_pipex pipex;

	if(argc == 5)
		printerror("Incorrect input\n");
	pipex.infile = open(argv[1],O_RDONLY);
	if(!pipex.infile)
		printerror("Incorrect infile\n");
	
}