/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenvvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:41:17 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/15 15:38:50 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*getval(const char *envvar, t_list *envlist);
static int	isfound(const char *envvar, const char *var_ptr);

char	*getenvvar_value(const char *envvar)
{
	t_list	*envlist;
	char	*entry_ptr;
	char	*val;

	++envvar;	//	skip the $ character
	if (*envvar == '?')
		return (ft_itoa(g_gbl.exit_status));
	if (*envvar == '\0' || ft_isblank(*envvar))
		return (ft_strdup("$"));
	envlist = g_gbl.envlist;
	while (envlist)
	{
		entry_ptr = (char *)(envlist->content);
		if (isfound(envvar, entry_ptr))
			break ;
		envlist = envlist->next;
	}
	if (envlist == NULL)
		return (NULL);
	val = getval(envvar, envlist);
	return (val);
}

static char	*getval(const char *envvar, t_list *envlist)
{
	char			*val;
	char			*key;
	size_t			len;
	unsigned int	start;

	key = (char *)(envlist->content);
	start = ft_strlen(envvar) + 1;
	len = ft_strlen(key) - start;
	val = ft_substr(key, start, len);
	return (val);
}

static int	isfound(const char *envvar, const char *entry_ptr)
{
	size_t	envvar_len;

	envvar_len = ft_strlen(envvar);
	if (ft_strncmp(envvar, entry_ptr, envvar_len) == 0
		&& entry_ptr[envvar_len] == '=')
		return (true);
	return (false);
}

char	*find_variable_and_get_value(char **ptr)
{
	char	*variable;
	char	*value;
	
	variable = find_variable(ptr);
	value = getenvvar_value(variable);
	free(variable);
	return (value);
}

int	is_valid_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*find_variable(char **ptr)
{
	char	*variable;
	size_t	len;

	len = 0;
	if ((*ptr)[len] == '$')
		len++;
	while (is_valid_variable_char((*ptr)[len]))
		len++;
	variable = ft_substr(*ptr, 0, len);
	*ptr += len;
	return (variable);
}
