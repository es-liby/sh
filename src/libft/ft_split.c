/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:51:12 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/10 02:29:01 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	count_word(const char *s, char c);
static size_t	get_len(const char *s, char c);
static int		check_sp(char **sp, int i);

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;

	if (s == NULL)
		return (NULL);
	str = ft_calloc(count_word(s, c), sizeof(char *));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0' && *s != c)
		{
			str[i] = ft_substr(s, 0, get_len(s, c));
			if (check_sp(str, i) == 0)
				return (NULL);
			i++;
		}
		while (*s != '\0' && *s != c)
			s++;
	}
	str[i] = NULL;
	return (str);
}

static int	check_sp(char **sp, int i)
{
	int	j;

	if (sp[i] != NULL)
		return (1);
	j = 0;
	while (j <= i)
		free(sp[j++]);
	free(sp);
	return (0);
}

static size_t	count_word(const char *s, char c)
{
	size_t	cnt;

	cnt = 1;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0' && *s != c)
			cnt++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (cnt);
}

static size_t	get_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}
