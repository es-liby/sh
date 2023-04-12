/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:40:26 by iabkadri          #+#    #+#             */
/*   Updated: 2022/10/19 11:41:40 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;

	p = s;
	while (*p != '\0')
		p++;
	while (p > s && *p != (char)c)
		p--;
	if (*p == (char)c)
		return ((char *)p);
	return (NULL);
}
