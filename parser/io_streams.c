#include <minishell.h>

static int	set_input_stream(t_pipeline **plist, t_list **tokens, t_fds *fds,
	int i);
static int	set_output_stream(t_pipeline **plist, t_list **tokens, t_fds *fds,
	int i);
static int	set_heredoc_for_input(t_pipeline **plist, t_list **tokens,
	t_fds *fds, int i);

int	set_input_and_output_streams(t_pipeline **plist, t_list **tokens,
	t_fds *fds, int i)
{
	if (p_match(tokens, REDIR_IN))
		if (set_input_stream(plist, tokens, fds, i) == EOF)
			return (EOF);
	if (p_match(tokens, REDIR_OUT) || p_match(tokens, REDIR_OUT_APPEND))
		if (set_output_stream(plist, tokens, fds, i) == EOF)
			return (EOF);
	if (p_match(tokens, HEREDOC))
		if (set_heredoc_for_input(plist, tokens, fds, i) == EOF)
			return (EOF);
	return (true);
}

static int	set_input_stream(t_pipeline **plist, t_list **tokens, t_fds *fds,
	int i)
{
	if (redir_input(plist, tokens, fds, i) == EOF)
		return (EOF);
	if (peek_type(*tokens) == WORD)
		return (set_cmd_and_args(plist, tokens, fds, i));
	return (true);
}

static int	set_output_stream(t_pipeline **plist, t_list **tokens, t_fds *fds,
	int i)
{
	if (redir_output(plist, tokens, fds, i) == EOF)
		return (EOF);
	if (peek_type(*tokens) == WORD)
		return (set_cmd_and_args(plist, tokens, fds, i));
	return (true);
}

static int	set_heredoc_for_input(t_pipeline **plist, t_list **tokens,
	t_fds *fds, int i)
{
	if (redir_heredoc(plist, tokens) == EOF)
		return (EOF);
	if (peek_type(*tokens) == WORD)
		return (set_cmd_and_args(plist, tokens, fds, i));
	return (true);
}
