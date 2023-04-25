/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_plist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:56:37 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/25 13:59:35 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	args_add_front(t_pipeline *token, char **cmd_sp);
static void	update_cmd_and_args(t_pipeline *token, char **new_args, char *new_cmd);
static size_t	get_sp_size(char **sp);

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

	size = get_sp_size(cmd_sp);
	new_args = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (cmd_sp[i])
	{
		new_args[i] = ft_strdup(cmd_sp[i]);
		i++;
	}
	new_args[i] = NULL;
	new_cmd = ft_strdup(cmd_sp[0]);
	update_cmd_and_args(token, new_args, new_cmd);
}

static void	update_cmd_and_args(t_pipeline *token, char **new_args, char *new_cmd)
{
	free(token->cmd);
	token->cmd = new_cmd;
	free(token->args);
	token->args = new_args;
}

static size_t	get_sp_size(char **sp)
{
	size_t	size;

	size = 0;
	while (sp[size])
		size++;
	return (size);
}
