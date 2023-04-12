/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:18:34 by iabkadri          #+#    #+#             */
/*   Updated: 2022/10/19 17:56:43 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*pd;
	const char	*ps;

	pd = dst;
	ps = src;
	if (pd == NULL && ps == NULL)
		return (NULL);
	while (n-- > 0)
		*pd++ = *ps++;
	return (dst);
}
