#include <minishell.h>

int	cdcmd(char **args)
{
	if (args[1] != NULL)
		return (error("bash: cd: too many arguments\n"), EOF);
	if (chdir(args[0]) == -1)
	{
		ft_fprintf(2, "bash: %s: %s\n", args[0], strerror(errno));
		return (EOF);
	}
	return (true);
}

int	pwdcmd(char **args)
{
	char	cwdbuf[FILENAME_MAX];

	(void)args;
	if (getcwd(cwdbuf, FILENAME_MAX) == NULL)
	{
		ft_fprintf(2, "bash: %s\n", strerror(errno));
		return (EOF);
	}
	ft_fprintf(1, "%s\n", cwdbuf);
	return (true);
}
