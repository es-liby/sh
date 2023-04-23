#ifndef EXECUTE_H
# define EXECUTE_H

# include <libft.h>
# include <ft_fprintf.h>
# include <structs.h>

# define JOIN 2
# define ADD 1

/*	exec.c	*/
int			execute(t_pipeline *plist);
void		error(char *msg);

/*	close_streams.c	*/
int			close_streams(t_pipeline *plist);
int			close_write_end(int i);
int			close_read_ends(t_fds *fds);
bool		is_not_pipe_fd(int fd);

/*	search_path.c	*/
int			search_and_set_path_for_cmds(t_pipeline *plist);

/*	builtins.c	*/
int			cdcmd(char **args);
int			pwdcmd(char **args);
int			echocmd(char **args);
int			envcmd(char **args);
int			exitcmd(char **args);
int			exportcmd(char **args);
int			set_value_of_new_envvar(char *new_envvar, char **value, size_t len);
void		join_new_envvar(char *key, char *value);
void		add_new_envvar(char *new_envvar, char *key, char *value);
int			unsetcmd(char **args);

/*	exec_builtin.c	*/
int			execute_builtin_cmd(t_pipeline *plist, t_builtin cmdtype);
t_builtin	is_a_builtin_cmd(char *cmd);

/*	dup_streams.c	*/
int			dup_streams(t_pipeline *plist, int *stdin_dup, int *stdout_dup);
int			getback_io_streams(t_pipeline *plist, int stdin_dup, int stdout_dup);

#endif
