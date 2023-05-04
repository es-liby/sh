/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:27:34 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 21:25:02 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	display_exported_variables(void);
static int	export_new_envvar(char *new_envvar);
static bool	is_not_a_valid_envvar(char *envvar);
static void	invalid_identifier(char *identifier);

void	exportcmd(char **args)
{
	int	i;

	if (!args[0])
	{
		display_exported_variables();
		return ;
	}
	i = -1;
	while (args[++i])
	{
		if (export_new_envvar(args[i]) == -1)
			return ;
	}
	g_glob.exit_status = 0;
}

static void	display_exported_variables(void)
{
	t_env	*envlist;

	envlist = g_glob.envlist;
	while (envlist)
	{
		if (ft_strcmp(envlist->key, "_") == 0)
		{
			envlist = envlist->next;
			continue ;
		}
		printf("declare -x %s", envlist->key);
		if (envlist->value)
			printf("=\"%s\"", envlist->value);
		printf("\n");
		envlist = envlist->next;
	}
}

static int	export_new_envvar(char *new_envvar)
{
	char	*key;
	char	*value;
	size_t	len;

	if (is_not_a_valid_envvar(new_envvar))
		return (-1);
	len = 0;
	while (new_envvar[len] && new_envvar[len] != '=' && new_envvar[len] != '+')
		len++;
	key = ft_substr(new_envvar, 0, len);
	value = NULL;
	if (set_value_of_new_envvar(new_envvar, &value, len) == ADD)
		add_new_envvar(key, value);
	else
		join_new_envvar(key, value);
	free(key);
	return (true);
}

static bool	is_not_a_valid_envvar(char *envvar)
{
	int	i;

	if (!ft_isalpha(envvar[0]) && envvar[0] != '_')
		return (invalid_identifier(envvar), 1);
	i = 1;
	while (envvar[i] && envvar[i] != '=')
	{
		if (!ft_isalnum(envvar[i]) && envvar[i] != '_' && envvar[i] != '+')
			return (invalid_identifier(envvar), 1);
		if (envvar[i] == '+' && envvar[i + 1] != '=')
			return (invalid_identifier(envvar), 1);
		i++;
	}
	return (0);
}

static void	invalid_identifier(char *identifier)
{
	ft_fprintf(2, "sh: export: `%s': not a valid identifier\n", identifier);
	g_glob.exit_status = 1;
}
