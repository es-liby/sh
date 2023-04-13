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

static int	set_redirections(t_pipeline **plist, t_list **tokens, t_fds *fds,
		int i);

int	perform_redirections(t_pipeline **plist, t_list **tokens)
{
	t_fds	*fds;
	int		i;

	fds = NULL;
	if (there_is_pipe_token(*tokens))
		fds = count_and_open_pipes(*tokens);
	i = 0;
	*plist = new_plist();
	while (*tokens)
	{
		if (set_redirections(plist, tokens, fds, i) == EOF)
			return ;
		i++;
	}
	close_pipes(fds->fds, fds->n);
	clear_pipes(fds);
}

static int	set_redirections(t_pipeline **plist, t_list **tokens, t_fds *fds,
		int i)
{
	if (is_not_valid_pipeline(*tokens))
		return (print_syntax_error(*tokens), EOF);
	if (peek_type(tokens) == WORD)
		if (set_cmd_and_args(plist, tokens, fds, i) == EOF)
			return (EOF);
	if (is_redir_token(*tokens))
		if (set_input_and_output_streams(plist, tokens, fds, i) == EOF)
			return (EOF);
	go_to_next_cmd(tokens);
	*plist = (*plist)->next;
	
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
