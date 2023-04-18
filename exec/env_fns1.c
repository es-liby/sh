/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fns1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:36:22 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/18 10:19:04 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	more_than_equal(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=')
			j++;
		i++;
	}
	return (j);
}

t_env	*handle_more_than_equal(char *str)
{
	int		i;
	t_env	*e;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '+')
			break ;
	}
	e = ft_calloc(1, sizeof(t_env));
	e->key = ft_substr(str, 0, i);
	e->value = ft_substr(str, i + 2, ft_strlen(str) - 1);
	e->next = NULL;
	e->without_equal = 0;
	e->printed = 1;
	return (e);
}

t_env	*handle_plus_equal_and_equal_at_end(char *str)
{
	t_env	*e;
	char	**splited;

	e = ft_calloc(1, sizeof(t_env));
	splited = ft_split(str, '+');
	e->key = ft_strdup(splited[0]);
	freestr(splited);
	splited = ft_split(str, '=');
	e->value = ft_strdup("");
	e->next = NULL;
	e->without_equal = 0;
	e->printed = 1;
	freestr(splited);
	return (e);
}

t_env	*handle_plus_equal_and_equal_not_at_the_end(char *str)
{
	t_env	*e;
	char	**splited;

	e = ft_calloc(1, sizeof(t_env));
	splited = ft_split(str, '+');
	e->key = ft_strdup(splited[0]);
	freestr(splited);
	splited = ft_split(str, '=');
	e->value = ft_strdup(splited[1]);
	e->next = NULL;
	e->without_equal = 0;
	e->printed = 1;
	freestr(splited);
	return (e);
}
