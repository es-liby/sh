/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:14:05 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/18 11:41:17 by iabkadri         ###   ########.fr       */
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

typedef struct s_global
{
	int				exit_status;
	t_list			*envlist;
	t_fds			*fds;
	char			*heredoc_file;
	unsigned int	sigint : 1;
}	t_global;

extern t_global	g_gbl;

typedef struct s_pipeline
{
	char				*cmd;
	char				**args;
	int					in_stream;
	int					out_stream;
	struct s_pipeline	*next;
}	t_pipeline;

#endif