/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:55:51 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/12 02:00:42 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	redirect(t_list **tokens);

int	perform_redirections(t_list **tokens)
{
	while (*tokens)
	{
		if (is_redir_token(*tokens))
			if (redirect(tokens) == EOF)
				return (EOF);
		advance(tokens);
	}
	return (true);
}

static int	redirect(t_list **tokens)
{
	t_tokentype	type;

	type = peek_type(*tokens);
	if (p_match(tokens, REDIR_IN))
		return (perform_redir_input(tokens));
	else if (p_match(tokens, REDIR_OUT) || p_match(tokens, REDIR_OUT_APPEND))
		return (perform_redir_output(tokens, type));
	advance(tokens);
	return (redir_heredoc(tokens));
}

void	print_syntax_error(t_list *tokens)
{
	char	*content;

	if (tokens == NULL)
	{
		ft_fprintf(2, "bash: syntax error near unexpected token `newline'");
		return ;
	}
	content = (char *)tokens->content;
	ft_fprintf(2, "bash: syntax error near unexpected token `%s'", content);
}
