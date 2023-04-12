/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:24:12 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/11 22:58:23 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid_envvar_char(char c);
static int	is_not_valid_variable(char c);

t_tokentype	getenvvar_token(char **pipeline, char **lexeme)
{
	char	*ptr;
	size_t	len;

	ptr = *pipeline;
	len = 1;	//	skip the '$' character
	if (is_not_valid_variable(ptr[len]))
	{
		ft_fprintf(2, "Invalid character: %c\n", ptr[len]);
		return (NIL);
	}
	while (ptr[len] && is_valid_envvar_char(ptr[len]))
		len++;
	*lexeme = ft_substr(ptr, 0, len);
	*pipeline += len;
	return (ENVVAR);
}

int	isenvvar_opt(char c)
{
	return (c == '$');
}

static int	is_valid_envvar_char(char c)
{
	return (!isredir_opt(c) && !ispipe_opt(c) && !isquote_opt(c)
		&& !ft_isspace(c));
}

static int	is_not_valid_variable(char c)
{
	return (!ft_isalpha(c) && c != '_' && c != '?');
}
