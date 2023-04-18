/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fns2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:50:35 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/18 10:07:33 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_env	*handle_simple_assignement(char *str)
{
	t_env	*e;
	char	**splited;

	e = ft_calloc(1, sizeof(t_env));
	splited = ft_split(str, '=');
	e->key = ft_strdup(splited[0]);
	e->value = ft_strdup(splited[1]);
	e->next = NULL;
	e->without_equal = 0;
	e->printed = 1;
	e->replace = 1;
	freestr(splited);
	return (e);
}

t_env	*handle_equal_at_the_end(char *str)
{
	t_env	*e;
	char	**splited;

	e = ft_calloc(1, sizeof(t_env));
	splited = ft_split(str, '=');
	e->key = ft_strdup(splited[0]);
	e->value = NULL;
	e->printed = 1;
	e->without_equal = 0;
	freestr(splited);
	return (e);
}

t_env	*handle_ls_colors_variable(char *str)
{
	t_env	*e;
	int		i;

	e = ft_calloc(1, sizeof(t_env));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
	}
	e->key = ft_substr(str, 0, i);
	e->value = ft_substr(str, i + 1, ft_strlen(str) - 1);
	e->next = NULL;
	e->without_equal = 0;
	e->printed = 1;
	return (e);
}

t_env	*handle_the_rest(char *str)
{
	t_env	*e;

	e = ft_calloc(1, sizeof(t_env));
	e->key = ft_strdup(str);
	e->value = NULL;
	e->next = NULL;
	e->printed = 0;
	e->without_equal = 1;
	return (e);
}

void	print_env(t_env *e)
{
	t_env	*t;

	if (!e)
		return ;
	t = e;
	while (1)
	{
		if (t->printed == 1)
			printf("%s=%s\n", t->key, t->value);
		if (!t->next)
			break ;
		t = t->next;
	}
}
