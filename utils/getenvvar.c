/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenvvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:16:10 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 18:14:29 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*find_value(const char *envvar);

char	*getenvvar_value(const char *envvar)
{
	char	*value;

	++envvar;
	if (*envvar == '?')
		return (ft_itoa(g_glob.exit_status));
	if (*envvar == '\0' || ft_isblank(*envvar))
		return (ft_strdup("$"));
	value = find_value(envvar);
	if (value == NULL)
		return (NULL);
	return (ft_strdup(value));
}

static char	*find_value(const char *envvar)
{
	t_env	*tmp_ptr;

	tmp_ptr = get_key_node(envvar);
	if (tmp_ptr == NULL)
		return (NULL);
	return (tmp_ptr->value);
}

t_env	*get_key_node(const char *key)
{
	t_env	*envlist;

	envlist = g_glob.envlist;
	while (envlist)
	{
		if (!ft_strcmp(envlist->key, key))
			break ;
		envlist = envlist->next;
	}
	return (envlist);
}

void	update_shell_level(void)
{
	t_env	*envlist;
	char	*new_val;
	int		shlvl_val;

	envlist = get_key_node("SHLVL");
	if (envlist == NULL)
		return ;
	shlvl_val = ft_atoi(envlist->value);
	new_val = ft_itoa(++shlvl_val);
	free(envlist->value);
	envlist->value = new_val;
}
