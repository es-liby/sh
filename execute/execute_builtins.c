/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:04:21 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 18:18:12 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_builtin(t_pipeline **plist)
{
	int	stdin_dup;
	int	stdout_dup;

	if (dup_streams(*plist, &stdin_dup, &stdout_dup) == -1)
		return (*plist = (*plist)->next, 1);
	if (!ft_strcmp((*plist)->cmd, "pwd"))
		pwdcmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "export"))
		exportcmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "echo"))
		echocmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "cd"))
		cdcmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "env"))
		envcmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "exit"))
		exitcmd((*plist)->args + 1);
	else if (!ft_strcmp((*plist)->cmd, "unset"))
		unsetcmd((*plist)->args + 1);
	else
		return (getback_io_streams(*plist, stdin_dup, stdout_dup), 0);
	getback_io_streams(*plist, stdin_dup, stdout_dup);
	*plist = (*plist)->next;
	return (1);
}

bool	check_if_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

bool	if_builtin_execute(t_pipeline **plist)
{
	if (!check_if_builtin((*plist)->cmd))
		return (0);
	return (execute_builtin(plist));
}
