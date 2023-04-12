#ifndef SCANNER_H
# define SCANNER_H

# include <symbols.h>
# include <libft.h>

/*	scanner.c	*/
void			scanner(t_list **tokens, char *cmdline);
int				operator_not_supported(char c);

/*	redir_token.c	*/
t_tokentype	getredir_token(char **pipeline, char **token);
int			isredir_opt(char c);

/*	pipe_token.c	*/
t_tokentype	getpipe_token(char **pipeline, char **token);
int			ispipe_opt(char c);

/*	quote_token.c	*/
t_tokentype	getquote_token(char **pipeline, char **token);
char		*del_quotes(char *ptr, char c);
int			is_not_surronded_by_quotes(char *tmp_ptr, char c);
int			isquote_opt(char c);

/*	quote.c	*/
char		*quote(char **ptr, char c);

/*	envvar_token.c	*/
t_tokentype	getenvvar_token(char **pipeline, char **token);
int			isenvvar_opt(char c);
/*	braces.c	*/
t_tokentype	surronded_by_braces(char *ptre);

/*	word_token.c	*/
t_tokentype	getword_token(char **pipeline, char **token);
int			is_not_end_of_sequence(char c);

/*	sequence.c	*/
char		*get_sequence(char **ptr, char **lexeme);

/*	scanner_utils.c	*/
void		addtoken(t_list **tokens, char *token, t_tokentype type);
int			s_match(char **ptr, char c);
int			isopt(char c);
int			ft_isblank(char c);
int			check_for_syntax_error(char *pipeline);

#endif