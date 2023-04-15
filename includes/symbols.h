#ifndef SYMBOLS_H
# define SYMBOLS_H

typedef enum e_tokentype
{
	REDIR,
	PIPE,
	WORD,
	ENVVAR,
	DQUOTE,
	SQUOTE,
	CMD,
	TREE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	HEREDOC,
	ARGS,
	END,
	NIL
}	t_tokentype;

#endif