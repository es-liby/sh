/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenvvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:16:10 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/01 12:01:59 by iabkadri         ###   ########.fr       */
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

	tmp_ptr = g_glob.envlist;
	while (tmp_ptr)
	{
		if (ft_strcmp(envvar, tmp_ptr->key) == 0)
			return (tmp_ptr->value);
		tmp_ptr = tmp_ptr->next;
	}
	return (NULL);
}

void	update_shell_level(void)
{
	t_env	*envlist;
	char	*new_val;
	int		shlvl_val;

	envlist = g_glob.envlist;
	while (envlist)
	{
		if (!ft_strcmp(envlist->key, "SHLVL"))
			break ;
		envlist = envlist->next;
	}
	if (envlist == NULL)
		return ;
	shlvl_val = ft_atoi(envlist->value);
	new_val = ft_itoa(++shlvl_val);
	free(envlist->value);
	envlist->value = new_val;
}
