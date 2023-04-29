/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_plist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:07:51 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/29 07:51:37 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		update_cmd_and_args(t_pipeline *token, char **new_args,
					char *new_cmd);

void	split_plist(t_pipeline *tmp_ptr)
{
	char		**cmd_sp;

	cmd_sp = ft_split(tmp_ptr->cmd, ' ');
	if (cmd_sp[1] != NULL)
		update_cmd_and_args(tmp_ptr, cmd_sp, ft_strdup(cmd_sp[0]));
	else
		free_tab(cmd_sp);
}

static void	update_cmd_and_args(t_pipeline *token, char **new_args,
				char *new_cmd)
{
	free(token->cmd);
	token->cmd = new_cmd;
	free(token->args);
	token->args = new_args;
}
