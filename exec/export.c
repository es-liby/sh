/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:03:38 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/18 10:40:11 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_export(t_env *e, char **env, char **new_variables)
{
	t_env	*new;
	int		i;

	e = NULL;
	i = -1;
	while (env[++i])
		ft_lstaddback_env(&e, ft_lstnew_env(env[i]));
	i = 0;
	if (new_variables)
	{
		while (new_variables[++i])
		{
			if (!check_the_variable_naming(new_variables[i]))
				return (0);
			new = ft_lstnew_env(new_variables[i]);
			if (already_exist(e, new->key, new->value, new) == 1)
			{
				free(new);
				continue ;
			}
			ft_lstaddback_env(&e, new);
		}
	}
	print_export(e);
	/*********** to test unset *********/
	// char word[] = "SHELL";
	// ft_unset(&e, word);
	// print_export(e);
	/***********************************/
	return (free_env(e), 1);
}

int	already_exist(t_env *e, char *key, char *value, t_env *new)
{
	char	*value_dup;

	if (!e || !key || !value)
		return (0);
	while (e && ft_strcmp(e->key, key))
	{
		e = e->next;
	}
	if (e == NULL)
		return (0);
	value_dup = ft_strdup(value);
	if (new->replace == 1)
		e->value = value_dup;
	else
		e->value = ft_strjoin(e->value, value_dup);
	free(value_dup);
	return (1);
}

void	print_export(t_env *e)
{
	t_env	*t;

	if (!e)
		return ;
	t = e;
	while (1)
	{
		if (t->key)
		{
			if (t->value)
				printf("declare -x %s=\"%s\"\n", t->key, t->value);
			else if (t->without_equal == 1)
				printf("declare -x %s\n", t->key);
			else
				printf("declare -x %s=\"\"\n", t->key);
			if (!t->next)
				break ;
		}
		t = t->next;
	}
}

int	check_the_variable_naming(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i])
			&& str[i] != '_' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

void	free_env(t_env *e)
{
	t_env	*tmp;

	while (e)
	{
		tmp = e;
		e = e->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}	
