/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:43:43 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/17 18:18:10 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <ft_fprintf.h>
# include <get_next_line.h>
# include <stdbool.h>
# include <structs.h>
# include <scanner.h>
# include <parser.h>
# include <execute.h>
# include <symbols.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>
# include <signal.h>

# define ERROR -1
# define ALLOC_ERROR 2
# define SYN_ERROR 3

# define ON 1
# define OFF 0

# define STOP 0
# define CONT 1

/*	main.c	*/
void	prompt(char *envp[]);
void	unlink_heredoc_file(void);

/*	debug.c	*/
void	printplist(t_pipeline *plist);
void	print_args(char **args);
void	printlist(t_list *tokens);
void	testprint(t_list *tokens);
void	printenvvar(void);

/*	utils.c	*/
void	advance_pipeline(char **pipeline, int size);

/*	std.c	*/
int		ft_open(char *file, int flags);
int		ft_dup2(int fd1, int fd2);
int		ft_pipe(int *fd);
int		ft_close(int fd);
int		ft_fork(void);

/*	getenvvar.c	*/
char	*getenvvar_value(const char *envvar);

/*	getenvvar_utils.c	*/
char	*find_variable_and_get_value(char **ptr);
char	*find_variable(char **ptr);

/*	handle_signals.c	*/
void	handle_signals(void);

/*	envcpy.c	*/
t_env	*envcpy(char *envp[]);
void	add_envvar(t_env **env, char *key, char *value);
char	**get_envp(void);

/*	key_value.c	*/
char	*getkey(char *envp);
char	*getvalue(char *envp);
char	*join_key_and_value(t_env *env_ptr);

/*	clear.c	*/
void	clear_plist(t_pipeline **plist);
void	free_tab(char **tab);


#endif