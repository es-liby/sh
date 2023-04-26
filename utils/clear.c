/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:51:08 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/26 09:43:31 by iabkadri         ###   ########.fr       */
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
	free_tab(g_gbl.envp);
}

void	clearenv(t_env *envlist)
{
	t_env	*tmp_ptr;

	if (envlist == NULL)
		return ;
	while (envlist)
	{
		tmp_ptr = envlist;
		envlist = envlist->next;
		free(tmp_ptr->key);
		free(tmp_ptr->value);
		free(tmp_ptr);
	}
	g_gbl.envlist = NULL;
}

void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
