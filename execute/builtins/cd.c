#include <minishell.h>

int	cdcmd(char **args)
{
	if (args[1] != NULL)
		return (error("Invalid path!\n"), EOF);
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

	if (args[1] != NULL)
		return (error("error: pwd does not accept any option: %s\n", args[1]));
	if (getcwd(cwdbuf, FILENAME_MAX) == NULL)
	{
		ft_fprintf(2, "bash: %s\n", strerror(errno));
		return (EOF);
	}
	ft_fprintf(1, "%s\n", cwdbuf);
	return (true);
}
