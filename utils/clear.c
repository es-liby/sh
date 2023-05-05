/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:51:08 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 08:03:10 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cleanup(t_pipeline **plist, t_list **tokens)
{
	unlink_heredoc_file();
	clear_pipes(g_glob.fds);
	free_tab(g_glob.envp);
	clear_plist(plist);
	ft_lstclear(tokens, free);
	g_glob.sigint = OFF;
}

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
	g_glob.envlist = NULL;
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

void	unlink_heredoc_file(void)
{
	if (g_glob.heredoc_file == NULL)
		return ;
	if (unlink(g_glob.heredoc_file) == -1)
	{
		free(g_glob.heredoc_file);
		perror("unlink");
		return ;
	}
	free(g_glob.heredoc_file);
	g_glob.heredoc_file = NULL;
}
