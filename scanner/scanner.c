/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:03:44 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/16 03:03:35 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_tokentype	get_next_token(char **pipeline, char **lexeme);
static t_tokentype	gettype_of_token(char c);
static void			fill_funcs(t_tokentype (*funcs[])(char **, char **));

int	scanner(t_list **tokens, char *pipeline)
{
	char		*lexeme;
	t_tokentype	type;

	*tokens = NULL;
	type = get_next_token(&pipeline, &lexeme);
	while (type != END && type != NIL)
	{
		addtoken(tokens, lexeme, type);
		type = get_next_token(&pipeline, &lexeme);
	}
	if (type == NIL)
		return (ft_lstclear(tokens, free), NIL);
	return (type);
} 

static t_tokentype	get_next_token(char **pipeline, char **lexeme)
{
	t_tokentype	(*funcs[3])(char **, char **);
	t_tokentype	type;

	if (**pipeline == '\0')
		return (END);
	while (**pipeline && ft_isblank(**pipeline) && !isopt(**pipeline))
		++*pipeline;
	fill_funcs(funcs);
	type = gettype_of_token(**pipeline);
	if (type == END)
		return (END);
	return ((funcs[type])(pipeline, lexeme));
}

static t_tokentype	gettype_of_token(char c)
{
	if (c == '\0' || c == '#')
		return (END);
	if (isredir_opt(c))
		return (REDIR);
	if (ispipe_opt(c))
		return (PIPE);
	return (WORD);
}

int	operator_not_supported(char c)
{
	if (c != '&' && c != ';' && c != '(' && c != ')'
		&& c != '{' && c != '}' && c != '\\')
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
