/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirely <dshirely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:38:24 by dshirely          #+#    #+#             */
/*   Updated: 2022/03/25 14:24:19 by dshirely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//pipe()
//fork()
//dub2()(int oldfd, int newfd);
//execve()

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
	freee(paths);
	return (0);
}

void	executecommand(char *argv, char **env)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], env);
	if (!path)
	{
		freee(cmd);
		printerror("path error\n");
	}
	if (execve(path, cmd, env) == -1)
		printerror("execve error\n");
}

void	child(char **argv, char **env, t_pipex pipex)
{
	pipex.input = open(argv[1], O_RDONLY, S_IRWXU);
	if (pipex.input == -1)
		printerror("childerror\n");
	dup2(pipex.tube[1], STDOUT_FILENO);
	dup2(pipex.input, STDIN_FILENO);
	close(pipex.tube[0]);
	executecommand(argv[2], env);
}

void	parent(char **argv, char **env, t_pipex pipex)
{
	pipex.output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (pipex.output == -1)
		printerror("parenterror\n");
	dup2(pipex.tube[0], STDIN_FILENO);
	dup2(pipex.output, STDOUT_FILENO);
	close(pipex.tube[1]);
	executecommand(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		printerror("Incorrect input\n");
	if (pipe(pipex.tube) == -1)
		printerror("pipe error\n");
	pipex.pid = fork();
	if (pipex.pid == -1)
		printerror("fork error\n");
	if (pipex.pid == 0)
		child(argv, env, pipex);
	waitpid(pipex.pid, NULL, 0);
	parent(argv, env, pipex);
	return (0);
}
