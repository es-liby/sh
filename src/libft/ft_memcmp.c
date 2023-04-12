/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:00:39 by iabkadri          #+#    #+#             */
/*   Updated: 2022/10/19 17:45:13 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	cs1;
	unsigned char	cs2;

	while (n > 0)
	{
		cs1 = *(unsigned char *)s1++;
		cs2 = *(unsigned char *)s2++;
		if (cs1 != cs2)
			return (cs1 - cs2);
		n--;
	}
	return (0);
}
