/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabkadri <iabkadri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:30:57 by iabkadri          #+#    #+#             */
/*   Updated: 2023/04/10 02:28:12 by iabkadri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

static int	ft_fillbuf(int fd, char **line, char **stock, char **buf);
static char	*join(char *stock, char *buf);
static char	*ft_getline(char **stock, int indx);
static int	getindex(char *stock);

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*buf;
	char		*line;
	int			indx;
	int			i;

	indx = getindex(stock);
	while (indx == -1)
	{
		i = ft_fillbuf(fd, &line, &stock, &buf);
		if (i == 0)
			return (line);
		else if (i == -1)
		{
			free(stock);
			return (NULL);
		}
		stock = join(stock, buf);
		free(buf);
		indx = getindex(stock);
	}
	line = ft_getline(&stock, ++indx);
	return (line);
}

static int	ft_fillbuf(int fd, char **line, char **stock, char **buf)
{
	int	i;

	*buf = malloc(BUFFER_SIZE + 1);
	if (*buf == NULL)
		exit(EXIT_FAILURE);
	i = read(fd, *buf, BUFFER_SIZE);
	if (i <= 0)
	{
		free(*buf);
		*buf = NULL;
		if (*stock != NULL && **stock != '\0' && i == 0)
		{
			*line = ft_strdup_gnl(*stock);
			free(*stock);
			*stock = NULL;
			return (0);
		}
		free(*stock);
		*stock = NULL;
		return (-1);
	}
	(*buf)[i] = '\0';
	return (i);
}

static char	*join(char *stock, char *buf)
{
	char	*strjoin;
	size_t	size;

	if (stock == NULL)
		return (ft_strdup_gnl(buf));
	size = ft_strlen_gnl(stock) + ft_strlen_gnl(buf) + 1;
	strjoin = malloc(size);
	if (strjoin == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy_gnl(strjoin, stock, size);
	ft_strlcat_gnl(strjoin, buf, size);
	free(stock);
	return (strjoin);
}

static char	*ft_getline(char **stock, int indx)
{
	char	*line;
	char	*rest;

	rest = ft_strdup_gnl(*stock + indx);
	line = ft_substr_gnl(*stock, 0, indx);
	free(*stock);
	*stock = rest;
	return (line);
}

static int	getindex(char *stock)
{
	int	i;

	if (stock == NULL)
		return (-1);
	i = 0;
	while (stock[i] != '\0' && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		return (i);
	return (-1);
}
