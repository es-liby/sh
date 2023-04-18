/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:47:22 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/04/17 15:09:33 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	size_t			i;
	unsigned int	ss;

	if (!s)
		return (NULL);
	ss = ft_strlen((char *)s);
	if (start > ss)
		len = 0;
	i = 0;
	ss = start;
	while (s[ss] && i < len)
	{
		i++;
		ss++;
	}
	p = (char *)malloc((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	ss = start;
	while (s[ss] && i < len)
		p[i++] = s[ss++];
	p[i] = '\0';
	return (p);
}

void	ft_putstr(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		write(1, &s[i], 1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	p = b;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void *ft_calloc(size_t count, size_t size)
{
	void *p;

	if (size != 0 && count * size / size != count)
		return (NULL);
	p = malloc(size * count);
	if (!p)
		exit(EXIT_FAILURE);
	ft_memset(p, 0, size * count);
	return (p);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

char *ft_strdup(const char *s1)
{
	int i;
	char *p;

	i = 0;
	while (s1[i])
		i++;
	p = (char *)ft_calloc(sizeof(char), i + 1);
	if (!p)
		return (NULL);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*l;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	l = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!l)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		l[++j] = s1[i];
	i = -1;
	while (s2[++i])
		l[++j] = s2[i];
	l[++j] = '\0';
	return (l);
}

int ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
