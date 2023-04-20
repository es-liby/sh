/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:50:48 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/09 11:53:08 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_list	*new_envvar(const char *envp);

t_list	*envcpy(char *envp[])
{
	t_list	*envlist;
	t_list	*new;
	int		i;

	envlist = NULL;
	i = -1;
	while (envp[++i])
	{
		new = new_envvar(envp[i]);
		ft_lstadd_back(&envlist, new);
	}
	return (envlist);
}

static t_list	*new_envvar(const char *envp)
{
	t_list	*new;
	char	*cpy;

	cpy = ft_strdup(envp);
	new = ft_lstnew(cpy, ENVVAR);
	return (new);
}

char	**get_envp(void)
{
	char	**envlist;
	t_list	*env_ptr;
	size_t	size;
	int		indx;

	env_ptr = g_gbl.envlist;
	size = ft_lstsize(env_ptr);
	envlist = ft_calloc(size + 1, sizeof(char *));
	indx = -1;
	while (env_ptr)
	{
		envlist[++indx] = ft_strdup((char *)env_ptr->lexeme);
		advance(&env_ptr);
	}
	envlist[indx] = NULL;
	return (envlist);
}
