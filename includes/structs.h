/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:41:36 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:41:37 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <symbols.h>
# include <libft.h>

typedef struct s_fds
{
	int	**fds;
	int	n;
	int	pipe_counter;
}	t_fds;

typedef struct s_ids
{
	pid_t			pid;
	struct s_ids	*next_id;
}	t_ids;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_global
{
	int				exit_status;
	t_env			*envlist;
	char			**envp;
	t_fds			*fds;
	char			*heredoc_file;
	unsigned int	sigint : 1;
}	t_global;

extern t_global	g_glob;

typedef struct s_pipeline
{
	char				*cmd;
	char				**args;
	int					in_stream;
	int					out_stream;
	struct s_pipeline	*next;
}	t_pipeline;

#endif