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
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void executecommand(char *argv,char **env)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], env);
	if (!path)	
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		printerror("kek");
	}
	if (execve(path, cmd, env) == -1)
		printerror("kek");
}

void child(char **argv,char **env,t_pipex pipex)
{
	// int input;

	pipex.input = open(argv[1],O_RDONLY,0777);//S_IRWXU);
	if(pipex.input == -1)
		printerror("childerror\n");
	dup2(pipex.tube[1],STDOUT_FILENO);
	dup2(pipex.input,STDIN_FILENO);
	close(pipex.tube[0]);
	executecommand(argv[2],env);
}
void parent(char **argv,char **env,t_pipex pipex)
{
	// int output;

	pipex.output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);//O_RDONLY,S_IRWXU);
	if(pipex.output == -1)
		printerror("parenterror\n");
	dup2(pipex.tube[0],STDIN_FILENO);
	dup2(pipex.output,STDOUT_FILENO);
	close(pipex.tube[1]);
	executecommand(argv[3],env);
}

int main(int argc, char **argv, char **env)
{
	t_pipex pipex;
	// int tube[2];//
	// pid_t pid;//
	if (argc != 5)
		printerror("Incorrect input\n");


	// pipex.infile = open(argv[1], O_RDONLY);
	// if (pipex.infile < 0)
	// 	printerror("Incorrect infile\n");
	// pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, S_IRWXU);   // 0000644);
	// if (pipex.outfile < 0)
		// printerror("Outfile error\n");

	if (pipe(pipex.tube) == -1)
		printerror("pipe error\n");
	pipex.pid=fork();//fork nepravilno
	if (pipex.pid == - 1)
		printerror("error\n");
	if (pipex.pid == 0)
		child(argv, env, pipex);
	waitpid(pipex.pid, NULL, 0);
	parent(argv, env, pipex);
	printf("end");
	printf("aboba");
	return (0);
}