/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:41:21 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/05 07:41:22 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <ft_fprintf.h>
# include <stdbool.h>
# include <fcntl.h>
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

# define ON 1
# define OFF 0

# define USG_ERR_MSG "\e[1m\x1B[31mUsage:\x1B[0m\e[m"

/*	main.c	*/
void	runprompt(void);

/*	std.c	*/
int		ft_open(char *file, int flags);
int		ft_dup2(int fd1, int fd2);
int		ft_pipe(int *fd);
int		ft_close(int fd);
int		ft_fork(void);

/*	getenvvar.c	*/
char	*getenvvar_value(const char *envvar);
void	update_shell_level(void);

/*	getenvvar_utils.c	*/
char	*find_variable_and_get_value(char **ptr);
char	*find_variable(char **ptr);
t_env	*get_key_node(const char *key);

/*	handle_signals.c	*/
void	handle_signals(void);
void	handle_signals_for_cmds(void);

/*	envcpy.c	*/
t_env	*envcpy(char *envp[]);
void	add_envvar(t_env **env, char *key, char *value);
char	**get_envp(void);

/*	key_value.c	*/
char	*getkey(char *envp);
char	*getvalue(char *envp);
char	*join_key_and_value(t_env *env_ptr);

/*	clear.c	*/
void	cleanup(t_pipeline **plist, t_list **tokens);
void	clear_plist(t_pipeline **plist);
void	clearenv(t_env *envlist);
void	free_tab(char **tab);
void	unlink_heredoc_file(void);

/*	error.c	*/
void	fatal(char *msg);
void	exit_with_errmsg(char *err_src, int errno_val, int exit_status);
void	exit_usage_err(void);
void	cmd_notfound(char *cmd);
void	no_such_file_or_dir(char *cmd);

#endif