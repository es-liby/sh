/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:07 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/24 12:00:08 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	fill_cmd_funcs(int (*cmd_funcs[7])(char **));

void	execute_builtin_cmd(t_pipeline *plist, t_builtin cmdtype)
{
	int		(*cmd_funcs[7])(char **);
	int		stdin_dup;
	int		stdout_dup;
	char	**args;

	dup_streams(plist, &stdin_dup, &stdout_dup);
	fill_cmd_funcs(cmd_funcs);
	args = plist->args;
	(cmd_funcs[cmdtype])(args + 1);
	getback_io_streams(plist, stdin_dup, stdout_dup);
}

static void	fill_cmd_funcs(int (*cmd_funcs[7])(char **))
{
	cmd_funcs[0] = echocmd;
	cmd_funcs[1] = cdcmd;
	cmd_funcs[2] = pwdcmd;
	cmd_funcs[3] = exportcmd;
	cmd_funcs[4] = unsetcmd;
	cmd_funcs[5] = envcmd;
	cmd_funcs[6] = exitcmd;
}

t_builtin	is_a_builtin_cmd(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd, "env"))
		return (ENV);
	if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (NONE);
}
