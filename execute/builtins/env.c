/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:00:28 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/02 16:24:02 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	display_current_environment(void);

int	envcmd(char **args)
{
	(void)args;
	display_current_environment();
	update_exit_status(0);
	return (true);
}

static void	display_current_environment(void)
{
	t_env	*envlist;

	envlist = g_glob.envlist;
	while (envlist)
	{
		ft_fprintf(1, "%s", envlist->key);
		if (envlist->value != NULL)
			ft_fprintf(1, "=%s", envlist->value);
		ft_fprintf(1, "\n");
		envlist = envlist->next;
	}
}
