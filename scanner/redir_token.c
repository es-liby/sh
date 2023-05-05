/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:40:49 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:40:50 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_tokentype	redir_input(char **pipeline, char **lexeme);
static t_tokentype	redir_output(char **pipeline, char **lexeme);

t_tokentype	getredir_token(char **pipeline, char **lexeme)
{
	t_tokentype	type;

	type = NIL;
	if (s_match(pipeline, '<'))
		type = redir_input(pipeline, lexeme);
	else if (s_match(pipeline, '>'))
		type = redir_output(pipeline, lexeme);
	return (type);
}

static t_tokentype	redir_input(char **pipeline, char **lexeme)
{
	t_tokentype	type;

	type = REDIR_IN;
	if (s_match(pipeline, '<'))
	{
		*lexeme = ft_strdup("<<");
		type = HEREDOC;
	}
	else
		*lexeme = ft_strdup("<");
	return (type);
}

static t_tokentype	redir_output(char **pipeline, char **lexeme)
{
	t_tokentype	type;

	type = REDIR_OUT;
	if (s_match(pipeline, '>'))
	{
		*lexeme = ft_strdup(">>");
		type = REDIR_OUT_APPEND;
	}
		*lexeme = ft_strdup(">");
	return (type);
}

int	isredir_opt(char c)
{
	return (c == '<' || c == '>');
}
