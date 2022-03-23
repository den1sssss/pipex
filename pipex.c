#include "pipex.h"
//pipe()
//fork()
//dub2()(int oldfd, int newfd);
//execve()



void printerror(char *str)
{
	perror(str);
	exit(0);
}

int get_next_line(char **line)
{
	int rd = 0;
	int i = 0;
	char *buffer = malloc(100000);
	*line = buffer;
	while((rd = read(0,&buffer[i], 1) > 0 && buffer[i] != '\n'))
		i++;
	buffer[i] = '\0';
	return (rd);
}


void executecommand(char *argv,char **env)
{

}
void child(char **argv,char **env,t_pipex pipex)
{
	int input;

	input = open(argv[1],O_RDONLY,S_IRWXU);
	if(input == -1)
		printerror("childerror\n");
	dup2(pipex.tube[1],STDOUT_FILENO);
	dup2(input,STDIN_FILENO);
	close(pipex.tube[0]);
	executecommand(argv[2],env);
}
void parent(char **argv,char **env,t_pipex pipex)
{
	int output;

	output = open(argv[4],O_RDONLY,S_IRWXU);
	if(output == -1)
		printerror("childerror\n");
	dup2(pipex.tube[0],STDOUT_FILENO);
	dup2(output,STDIN_FILENO);
	close(pipex.tube[1]);
	execute(argv[3],env);
}

int main(int argc, char **argv, char **env)
{
	t_pipex pipex;

	if (argc != 5)
		printerror("Incorrect input\n");
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		printerror("Incorrect infile\n");
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, S_IRWXU);   // 0000644);
	if (pipex.outfile < 0)
		printerror("Outfile error\n");
	if (pipe(pipex.tube) == -1)
		printerror("pipe error\n");
	pipex.pid=fork();
	if (pipex.pid == - 1)
		printerror("error\n");
	if (pipex.pid == 0)
		child(argv, env, pipex);
	waitpid(pipex.pid, NULL, 0);
	parent(argv, env, pipex);
	printf("end");
}