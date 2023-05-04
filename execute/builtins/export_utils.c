/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:27:26 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 16:55:10 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		update_existed_variable(t_env *envlist, char *key, char *value);
static t_env	*key_already_exists(char *key);

int	set_value_of_new_envvar(char *new_envvar, char **value, size_t len)
{
	size_t	size;

	if (new_envvar[len] == '\0')
		return (ADD);
	if (new_envvar[len] == '=' && new_envvar[len + 1] == '\0')
		*value = ft_strdup("\0");
	else if (new_envvar[len] == '+')
	{
		if (new_envvar[len + 2] == '\0')
			*value = ft_strdup("\0");
		else
		{
			size = ft_strlen(new_envvar) - (len + 2);
			*value = ft_substr(new_envvar, len + 2, size);
		}
		return (JOIN);
	}
	else
	{
		size = ft_strlen(new_envvar) - (len + 1);
		*value = ft_substr(new_envvar, len + 1, size);
	}
	return (ADD);
}

void	join_new_envvar(char *key, char *value)
{
	t_env	*envlist;
	char	*new_value;

	new_value = NULL;
	envlist = key_already_exists(key);
	if (envlist)
	{
		free(key);
		new_value = ft_strjoin(envlist->value, value);
		free(value);
		envlist->value = new_value;
		return ;
	}
	add_envvar(&g_glob.envlist, key, value);
}

void	add_new_envvar(char *key, char *value)
{
	t_env	*envlist;

	envlist = key_already_exists(key);
	if (envlist)
		update_existed_variable(envlist, key, value);
	else
		add_envvar(&g_glob.envlist, ft_strdup(key), value);
}

static void	update_existed_variable(t_env *envlist, char *key, char *value)
{
	(void)key;
	if (!value)
		return ;
	free(envlist->value);
	envlist->value = value;
}

static t_env	*key_already_exists(char *key)
{
	t_env	*envlist;

	envlist = g_glob.envlist;
	while (envlist)
	{
		if (ft_strcmp(envlist->key, key) == 0)
			return (envlist);
		envlist = envlist->next;
	}
	return (NULL);
}
