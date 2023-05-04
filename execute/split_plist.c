/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_plist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:07:51 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 16:31:51 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		update_cmd_and_args(t_pipeline *token, char *new_cmd);

void	split_plist(t_pipeline *tmp_ptr)
{
	char	**cmd_sp;

	cmd_sp = ft_split(tmp_ptr->cmd, ' ');
	if (cmd_sp[1])
		update_cmd_and_args(tmp_ptr, ft_strdup(cmd_sp[0]));
	free_tab(cmd_sp);
}

static void	update_cmd_and_args(t_pipeline *token, char *new_cmd)
{
	char	**old_args;

	free(token->cmd);
	token->cmd = new_cmd;
	old_args = split_args(token->args);
	free_tab(token->args);
	token->args = old_args;
}

size_t	getsp_size(char **args)
{
	size_t	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}
