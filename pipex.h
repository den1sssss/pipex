#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>
#include <sys/types.h>
#include <string.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	*cmd;
	char	*paths;
	int		tube[2];
	char	**cmd_path;
	char	**cmd_arg;;
	
}				t_pipex;

#endif