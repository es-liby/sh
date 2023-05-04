/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:16:06 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 18:14:18 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_env	*lastenv(t_env *envlist);
static size_t	getsize_of_envlist(t_env *env);

t_env	*envcpy(char *envp[])
{
	t_env	*env;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	i = -1;
	while (envp[++i])
	{
		key = getkey(envp[i]);
		value = getvalue(envp[i]);
		add_envvar(&env, key, value);
	}
	return (env);
}

void	add_envvar(t_env **envlist, char *key, char *value)
{
	t_env	*tmp_ptr;

	if (*envlist == NULL)
	{
		*envlist = ft_calloc(1, sizeof(t_env));
		(*envlist)->key = key;
		(*envlist)->value = value;
		(*envlist)->next = NULL;
		return ;
	}
	tmp_ptr = lastenv(*envlist);
	tmp_ptr->next = ft_calloc(1, sizeof(t_env));
	tmp_ptr->next->key = key;
	tmp_ptr->next->value = value;
	tmp_ptr->next->next = NULL;
}

char	**get_envp(void)
{
	char	**envp;
	t_env	*envlist;
	size_t	size;
	size_t	indx;

	envlist = g_glob.envlist;
	size = getsize_of_envlist(envlist);
	envp = ft_calloc(size + 1, sizeof(char *));
	indx = -1;
	while (++indx < size)
	{
		envp[indx] = join_key_and_value(envlist);
		envlist = envlist->next;
	}
	envp[indx] = NULL;
	return (envp);
}

static size_t	getsize_of_envlist(t_env *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		++size;
		env = env->next;
	}
	return (size);
}

static t_env	*lastenv(t_env *envlist)
{
	while (envlist && envlist->next)
		envlist = envlist->next;
	return (envlist);
}
