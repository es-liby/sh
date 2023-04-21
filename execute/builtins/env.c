#include <minishell.h>

static void	display_current_environment(void);

int	envcmd(char **args)
{
	if (args[0] != NULL)
	{
		ft_fprintf(2, "env: `%s': No such file or a directory\n", args[1]);
		return (EOF);
	}
	display_current_environment();
	return (true);
}

static void	display_current_environment(void)
{
	t_env	*envlist;

	envlist = g_gbl.envlist;
	while (envlist)
	{
		printf("%s=%s\n", envlist->key, envlist->value);
		envlist = envlist->next;
	}
}
