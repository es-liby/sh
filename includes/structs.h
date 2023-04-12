#ifndef STRUCTS_H
# define STRUCTS_H

# include <symbols.h>
# include <libft.h>

typedef struct s_global
{
	int				exit_status;
	t_list			*envlist;
}	t_global;

extern t_global	e_gbl;

typedef	struct s_pipeline
{
	const char			*cmd;
	const char			*args;
	int					in_stream;
	int					out_stream;
	struct s_pipeline	*next;
}	t_pipeline;

#endif