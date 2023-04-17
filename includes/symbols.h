#ifndef SYMBOLS_H
# define SYMBOLS_H

typedef enum e_tokentype
{
	REDIR,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	HEREDOC,
	ENVVAR,
	END,
	NIL
}	t_tokentype;

#endif