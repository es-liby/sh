#include <minishell.h>

static int	set_args(t_pipeline **plist, t_list **tokens);
static void	args_after_cmd(t_pipeline **plist, t_list **tokens);
static int	search_and_set_args(t_pipeline **plist, t_list *tokens);
static void	set_pipe(t_pipeline **plist, t_fds *fds);

int	set_cmd_and_args(t_pipeline **plist, t_list **tokens, t_fds *fds)
{
	if ((*plist)->cmd == NULL)
	{
		(*plist)->cmd = ft_strdup((char *)(*tokens)->lexeme);
		advance(tokens);
	}
	if (set_args(plist, tokens) == EOF)
		return (EOF);
	if (fds != NULL)
		set_pipe(plist, fds);
	return (true);
}

static int	set_args(t_pipeline **plist, t_list **tokens)
{
	if (peek_type(*tokens) == WORD)
		args_after_cmd(plist, tokens);
	else if (search_and_set_args(plist, *tokens) == EOF)
		return (EOF);
	return (true);
}

static void	args_after_cmd(t_pipeline **plist, t_list **tokens)
{
	char	*args;

	args = NULL;
	while (peek_type(*tokens) == WORD)
	{
		args = ft_strjoin(args, (char *)(*tokens)->lexeme);
		args = ft_strjoin(args, " ");
		advance(tokens);
	}
	(*plist)->args = args;
}

static int	search_and_set_args(t_pipeline **plist, t_list *tokens)
{
	char	*args;

	args = NULL;
	while (peek_type(tokens) != NIL && peek_type(tokens) != PIPE)
	{
		if (is_redir_token(tokens))
		{
			advance(&tokens);
			if (p_match(&tokens, WORD) == false)
				return (syn_err(tokens), EOF);
			continue ;
		}
		args = ft_strjoin(args, (char *)tokens->lexeme);
		args = ft_strjoin(args, " ");
		advance(&tokens);
	}
	(*plist)->args = args;
	return (true);
}

static void	set_pipe(t_pipeline **plist, t_fds *fds)
{
	int	i;

	i = fds->pipe_counter;
	if (i == 0)
		(*plist)->out_stream = fds->fds[i][1];
	else if (i > 0 && i < fds->n)
	{
		(*plist)->in_stream = fds->fds[i - 1][0];
		(*plist)->out_stream = fds->fds[i][1];
	}
	if (i == fds->n)
		(*plist)->in_stream = fds->fds[i - 1][0];
}
