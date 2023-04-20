#include <minishell.h>

static void		add_envvar(t_env **env, char *key, char *value);
static size_t	getsize_of_envlist(t_env *env);

t_env	*envcpy(char *envp[])
{
	t_env	*env;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	i = -1;
	while (envp[++i])
	{
		key = getkey(envp[i]);
		value = getvalue(envp[i]);
		add_envvar(&env, key, value);
	}
	return (env);
}

static void	add_envvar(t_env **env, char *key, char *value)
{
	t_env	*tmp_ptr;

	if (*env == NULL)
	{
		*env = ft_calloc(1, sizeof(t_env));
		(*env)->key = key;
		(*env)->value = value;
		(*env)->next = NULL;
		return ;
	}
	tmp_ptr = *env;
	while (tmp_ptr && tmp_ptr->next)
		tmp_ptr = tmp_ptr->next;
	tmp_ptr->next = ft_calloc(1, sizeof(t_env));
	tmp_ptr->next->key = key;
	tmp_ptr->next->value = value;
	tmp_ptr->next->next = NULL;
}

char	**get_envp(void)
{
	char	**envp;
	t_env	*env_ptr;
	size_t	size;
	size_t	indx;

	env_ptr = g_gbl.env;
	size = getsize_of_envlist(env_ptr);
	envp = ft_calloc(size + 1, sizeof(char *));
	indx = -1;
	while (++indx < size)
	{
		envp[indx] = join_key_and_value(env_ptr);
		env_ptr = env_ptr->next;
	}
	envp[indx] = NULL;
	// for (int i = 0; envp[i]; i++)
	// 	printf("%s\n", envp[i]);
	return (envp);
}

static size_t	getsize_of_envlist(t_env *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		++size;
		env = env->next;
	}
	return (size);
}
