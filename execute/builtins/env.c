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
		ft_fprintf(1, "%s", envlist->key);
		if (envlist->value != NULL)
			ft_fprintf(1, "=%s", envlist->value);
		ft_fprintf(1, "\n");
		envlist = envlist->next;
	}
}
