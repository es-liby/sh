/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:28 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 21:22:45 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	display_current_environment(void);

void	envcmd(char **args)
{
	if (args[0])
	{
		ft_fprintf(2, "env: %s: No such file or directory\n", args[0]);
		g_glob.exit_status = 127;
		return ;
	}
	display_current_environment();
	g_glob.exit_status = 0;
}

static void	display_current_environment(void)
{
	t_env	*envlist;

	envlist = g_glob.envlist;
	while (envlist)
	{
		ft_fprintf(1, "%s", envlist->key);
		if (envlist->value)
			ft_fprintf(1, "=%s", envlist->value);
		ft_fprintf(1, "\n");
		envlist = envlist->next;
	}
}
