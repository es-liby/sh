#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <ft_fprintf.h>
# include <get_next_line.h>
# include <stdbool.h>
# include <structs.h>
# include <scanner.h>
# include <parser.h>
# include <symbols.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

# define ERROR -1
# define ALLOC_ERROR 2
# define SYN_ERROR 3

# define ON 1
# define OFF 0

/*				Grammar						*/

//	line	->	pipe line | redir line | NIL
//	pipe	->	cmd ("|" pipe)*
//	cmd		->	WORD args | envvar
//	args	->	WORD args | envvar | NIL
//	redir	->	("<" | "<<" | ">" | ">>") WORD
//	envvar	->	"$" (WORD | "?" | NIL)

/*	main.c	*/
void	prompt(void);
void	printlist(t_list *lst);
void	unlink_and_close_heredoc_file(t_pipeline *plist);
//void	treeprint(t_ptree *ptree);

/*	utils.c	*/
void	advance_pipeline(char **pipeline, int size);

/*	std.c	*/
int		ft_open(char *file, int flags);
void	ft_dup2(int fd1, int fd2);
void	ft_pipe(int *fd);
void	ft_close(int fd);

/*	getenvvar.c	*/
char	*getenvvar_value(const char *envvar);
char	*find_variable_and_get_value(char **ptr);
char	*find_variable(char **ptr);

/*	envcpy.c	*/
t_list	*envcpy(char *envp[]);

/*	clear.c	*/
void	clear_plist(t_pipeline **plist);

#endif