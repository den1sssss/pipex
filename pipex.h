#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>

typedef struct s_pipex
{
	int infile;
	int outfile;
	char *cmd;
	char *paths;
	
}				t_pipex
#endif