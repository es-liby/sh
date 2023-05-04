/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenvvar_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:47:19 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 19:45:07 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid_variable_char(char c);

char	*find_variable_and_get_value(char **ptr)
{
	char	*variable;
	char	*value;

	variable = find_variable(ptr);
	if (variable == NULL)
		return (NULL);
	value = getenvvar_value(variable);
	free(variable);
	return (value);
}

char	*find_variable(char **ptr)
{
	char	*variable;
	size_t	len;

	len = 0;
	if ((*ptr)[len] == '$')
		len++;
	if ((*ptr)[len] == '\'' || (*ptr)[len] == '"')
		return (*ptr += len, NULL);
	if (ft_isdigit((*ptr)[len]))
		return (*ptr += (len + 1), NULL);
	if ((*ptr)[len] == '?')
		return (*ptr += (len + 1), ft_strdup("$?"));
	while (is_valid_variable_char((*ptr)[len]))
		len++;
	variable = ft_substr(*ptr, 0, len);
	*ptr += len;
	return (variable);
}

static int	is_valid_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
