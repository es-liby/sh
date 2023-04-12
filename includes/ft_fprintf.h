/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:26:23 by iabkadri          #+#    #+#             */
/*   Updated: 2023/02/10 15:26:24 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdarg.h>
# include <unistd.h>

void	ft_fprintf(int fd, const char *format, ...);
void	ft_handle(int fd, char spc, va_list ap);
void	ft_putchar(int fd, char c);
void	ft_putstr(int fd, char *s);
void	ft_putnbr(int fd, long nbr);

#endif
