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

int main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	if (argc != 5)
		printerror("Incorrect input\n");
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		printerror("Incorrect infile\n");
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile < 0)
		printerror("Outfile error\n");
	
	
}