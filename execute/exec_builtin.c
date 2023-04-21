#include <minishell.h>

static void	fill_cmd_funcs(int (*cmd_funcs[7])(char **));

void	execute_builtin_cmd(char **args, t_builtin cmdtype)
{
	int		(*cmd_funcs[7])(char **);

	fill_cmd_funcs(cmd_funcs);
	if ((cmd_funcs[cmdtype])(args + 1) == EOF)
		exit(g_gbl.exit_status);
	exit(EXIT_SUCCESS);
}

static void	fill_cmd_funcs(int (*cmd_funcs[7])(char **))
{
	cmd_funcs[0] = echocmd;
	cmd_funcs[1] = cdcmd;
	cmd_funcs[2] = pwdcmd;
	cmd_funcs[3] = exportcmd;
	cmd_funcs[4] = unsetcmd;
	cmd_funcs[5] = envcmd;
	cmd_funcs[6] = exitcmd;
}

t_builtin	is_a_builtin_cmd(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd, "env"))
		return (ENV);
	if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (NONE);
}
