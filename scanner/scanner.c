/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:03:44 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/11 22:57:09 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_tokentype	get_next_token(char **pipeline, char **lexeme);
static t_tokentype	gettype_of_token(char *s);
static void			fill_funcs(t_tokentype (*funcs[])(char **, char **));

void	scanner(t_list **tokens, char *pipeline)
{
	char		*lexeme;
	t_tokentype	type;

	if (check_for_syntax_error(pipeline) == EOF)
		return ;
	*tokens = NULL;
	type = get_next_token(&pipeline, &lexeme);
	while (type != NIL)
	{
		addtoken(tokens, lexeme, type);
		type = get_next_token(&pipeline, &lexeme);
	}
}

static t_tokentype	get_next_token(char **pipeline, char **lexeme)
{
	t_tokentype	(*funcs[3])(char **, char **);
	t_tokentype	type;

	if (**pipeline == '\0')
		return (NIL);
	while (**pipeline && ft_isblank(**pipeline) && !isopt(**pipeline))
		++*pipeline;
	fill_funcs(funcs);
	type = gettype_of_token(*pipeline);
	if (type != NIL)
		return ((funcs[type])(pipeline, lexeme));
	return (NIL);
}

static t_tokentype	gettype_of_token(char *s)
{
	if (isredir_opt(*s))
		return (REDIR);
	if (ispipe_opt(*s))
		return (PIPE);
	return (WORD);
}

int	operator_not_supported(char c)
{
	if (c != '&' && c != ';' && c != '(' && c != ')'
		&& c != '{' && c != '}')
		return (false);
	ft_fprintf(2, "Operator not supported: %c\n", c);
	return (true);
}

static void	fill_funcs(t_tokentype (*funcs[])(char **, char **))
{
	funcs[0] = getredir_token;
	funcs[1] = getpipe_token;
	funcs[2] = getword_token;
}
