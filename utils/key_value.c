/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:16:54 by iabkadri          #+#    #+#             */
/*   Updated: 2023/05/04 16:53:20 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*getkey(char *envp)
{
	char	*key;
	size_t	len;

	len = 0;
	while (envp[len] && envp[len] != '=')
		len++;
	key = ft_substr(envp, 0, len);
	return (key);
}

char	*getvalue(char *envp)
{
	char	*value;
	size_t	len;

	while (*envp && *envp != '=')
		++envp;
	if (*envp == '\0')
		return (NULL);
	++envp;
	if (*envp == '\0')
		return (NULL);
	len = 0;
	while (envp[len])
		len++;
	value = ft_substr(envp, 0, len);
	return (value);
}

char	*join_key_and_value(t_env *env_ptr)
{
	char	*envp;
	char	*tmp_key;

	tmp_key = ft_strdup(env_ptr->key);
	envp = ft_strjoin(tmp_key, "=");
	if (env_ptr->value != NULL)
		envp = ft_strjoin(envp, env_ptr->value);
	return (envp);
}
