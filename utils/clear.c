/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:51:08 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/23 08:31:08 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear_plist(t_pipeline **plist)
{
	t_pipeline	*tmp;

	while (*plist)
	{
		tmp = *plist;
		*plist = (*plist)->next;
		free(tmp->cmd);
		free_tab(tmp->args);
		free(tmp);
	}
}

void	clear_gbl(void)
{
	clearenv(g_gbl.envlist);
	//clear_pipes(g_gbl.fds);
	free_tab(g_gbl.envp);
}

void	clearenv(t_env *envlist)
{
	t_env	*tmp_ptr;

	while (envlist)
	{
		tmp_ptr = envlist;
		envlist = envlist->next;
		free(tmp_ptr->key);
		free(tmp_ptr->value);
		free(tmp_ptr);
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
