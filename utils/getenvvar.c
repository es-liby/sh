#include <minishell.h>

static char	*find_value(const char *envvar);

char	*getenvvar_value(const char *envvar)
{
	char	*value;

	++envvar;
	if (*envvar == '?')
		return (ft_itoa(g_gbl.exit_status));
	if (*envvar == '\0' || ft_isblank(*envvar))
		return (ft_strdup("$"));
	value = find_value(envvar);
	if (value == NULL)
		return (NULL);
	return (ft_strdup(value));
}

static char	*find_value(const char *envvar)
{
	t_env	*tmp_ptr;

	tmp_ptr = g_gbl.envlist;
	while (tmp_ptr)
	{
		if (ft_strcmp(envvar, tmp_ptr->key) == 0)
			return (tmp_ptr->value);
		tmp_ptr = tmp_ptr->next;
	}
	return (NULL);
}
