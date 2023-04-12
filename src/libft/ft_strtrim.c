/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:53:07 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/10 02:29:26 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*_getbeg(const char *s, const char *set);
static char	*_getend(const char *s, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	char	*p;
	char	*t;
	size_t	size;

	if (s1 == NULL)
		return (NULL);
	if (*s1 == '\0' || set == NULL || *set == '\0')
		return (ft_strdup(s1));
	p = _getbeg(s1, set);
	if (*p == '\0')
		return (ft_strdup(p));
	t = _getend(p, set);
	size = t - p + 1;
	trimmed = ft_calloc(size + 1, sizeof(char));
	ft_strlcpy(trimmed, p, size + 1);
	return (trimmed);
}

static char	*_getbeg(const char *s, const char *set)
{
	while (*s != '\0')
	{
		if (ft_strchr(set, *s) != NULL)
			s++;
		else
			return ((char *)s);
	}
	return ((char *)s);
}

static char	*_getend(const char *s, const char *set)
{
	const char	*p;

	p = s;
	while (*p != '\0')
		p++;
	while (--p > s)
		if (ft_strchr(set, *p) == NULL)
			return ((char *)p);
	return ((char *)p);
}
