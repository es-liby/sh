#ifndef STRUCTS_H
# define STRUCTS_H

# include <symbols.h>
# include <libft.h>

typedef struct s_global
{
	int		exit_status;
	t_list	*envlist;
	t_list	*heredoc_files;
}	t_global;

extern t_global	g_gbl;

typedef	struct s_pipeline
{
	char				*cmd;
	char				*args;
	int					in_stream;
	int					out_stream;
	struct s_pipeline	*next;
}	t_pipeline;

typedef struct s_pipe
{
	int	**fds;
	int	n;
	int	pipe_counter;
}	t_fds;

#endif