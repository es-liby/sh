/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:55:44 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/10 02:27:56 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	size;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	size = len + 1;
	slen = ft_strlen_gnl(s);
	if (size > slen)
		size = slen + 1;
	if (slen <= start)
		size = 1;
	substr = malloc(size);
	if (substr == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy_gnl(substr, s + start, size);
	return (substr);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*p;

	p = malloc(ft_strlen_gnl(s) + 1);
	if (p == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy_gnl(p, s, ft_strlen_gnl(s) + 1);
	return (p);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;

	slen = ft_strlen_gnl(src);
	if (dstsize != 0)
	{
		while (*src != '\0' && --dstsize > 0)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (slen);
}

size_t	ft_strlcat_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;

	slen = ft_strlen_gnl(src);
	if (dst == NULL && dstsize == 0)
		return (slen);
	dlen = ft_strlen_gnl(dst);
	if (dlen >= dstsize)
		return (slen + dstsize);
	while (*dst != '\0')
		dst++;
	while (*src != '\0' && dstsize-- > dlen + 1)
		*dst++ = *src++;
	*dst = '\0';
	return (dlen + slen);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
