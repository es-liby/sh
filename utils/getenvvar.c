/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenvvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:16:10 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/27 10:20:02 by iabkadri         ###   ########.fr       */
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
