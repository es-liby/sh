#include <minishell.h>

static int	display_exported_variables(void);
static int	export_new_envvar(char *new_envvar);
static bool	is_not_a_valid_envvar(char *envvar);

int	exportcmd(char **args)
{
	int	i;

	if (args[0] == NULL)
		return (display_exported_variables());
	i = -1;
	while (args[++i])
	{
		if (export_new_envvar(args[i]) == EOF)
			return (EOF);
	}
	return (true);
}

static int	display_exported_variables(void)
{
	t_env	*envlist;

	envlist = g_gbl.envlist;
	while (envlist)
	{
		printf("declare -x %s", envlist->key);
		if (envlist->key != NULL)
			printf("=\"%s\"", envlist->value);
		printf("\n");
		envlist = envlist->next;
	}
	return (true);
}

static int	export_new_envvar(char *new_envvar)
{
	char	*key;
	char	*value;
	size_t	len;

	if (is_not_a_valid_envvar(new_envvar))
		return (EOF);
	len = 0;
	while (new_envvar[len] && new_envvar[len] != '=' && new_envvar[len] != '+')
		len++;
	key = ft_substr(new_envvar, 0, len);
	value = NULL;
	if (set_value_of_new_envvar(new_envvar, &value, len) == ADD)
		add_new_envvar(new_envvar, key, value);
	else
		join_new_envvar(new_envvar, key, value);
	return (true);
}

static bool	is_not_a_valid_envvar(char *envvar)
{
	int	i;

	if (!ft_isalpha(envvar[0]))
	{
		ft_fprintf(2, "bash: export: `%s': not a valid identifier", envvar);
		return (true);
	}
	i = 1;
	while (envvar[i] && envvar[i] != '=')
	{
		if (!ft_isalnum(envvar[i]) && envvar[i] != '_' && envvar[i] != '+')
		{
			ft_fprintf(2, "bash: export: `%s': not a valid identifier", envvar);
			return (true);
		}
		if (envvar[i] == '+' && envvar[i + 1] != '=')
		{
			ft_fprintf(2, "bash: export: `%s': not a valid identifier", envvar);
			return (true);
		}
		i++;
	}
	return (false);
}
