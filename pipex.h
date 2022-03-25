/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirely <dshirely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:38:30 by dshirely          #+#    #+#             */
/*   Updated: 2022/03/25 14:27:35 by dshirely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <string.h>

typedef struct s_pipex
{
	int		input;
	int		output;
	int		tube[2];
	pid_t	pid;
}				t_pipex;

void	printerror(char *str);
void	freee(char **str);
char	*find_path(char *cmd, char **envp);
void	executecommand(char *argv, char **env);
void	child(char **argv, char **env, t_pipex pipex);
void	parent(char **argv, char **env, t_pipex pipex);

#endif