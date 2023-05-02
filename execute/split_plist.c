/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_plist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:33:25 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/05/01 16:32:42 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		args_add_front(t_pipeline *token, char **cmd_sp);
static void		update_cmd_and_args(t_pipeline *token, char **new_args,
					char *new_cmd);

void	split_plist(t_pipeline *tmp_ptr)
{
	char		**cmd_sp;

	cmd_sp = ft_split(tmp_ptr->cmd, ' ');
	if (cmd_sp[1] != NULL)
		args_add_front(tmp_ptr, cmd_sp);
	free_tab(cmd_sp);
}

static void	args_add_front(t_pipeline *token, char **cmd_sp)
{
	char	**new_args;
	char	*new_cmd;
	size_t	size;
	size_t	i;

	size = getsp_size(cmd_sp);
	new_args = ft_calloc(size + 1, sizeof(char *));
	i = -1;
	while (cmd_sp[++i])
		new_args[i] = ft_strdup(cmd_sp[i]);
	new_args[i] = NULL;
	new_cmd = ft_strdup(cmd_sp[0]);
	update_cmd_and_args(token, new_args, new_cmd);
}

static void	update_cmd_and_args(t_pipeline *token, char **new_args,
				char *new_cmd)
{
	free(token->cmd);
	token->cmd = new_cmd;
	free(token->args);
	token->args = new_args;
}

size_t	getsp_size(char **sp)
{
	size_t	size;

	size = 0;
	while (sp[size])
		size++;
	return (size);
}
