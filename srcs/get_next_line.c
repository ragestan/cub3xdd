/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:06:45 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/04 14:40:35 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*fill_stock(int fd, char *stock)
{
	char	*buf;
	int		rd;

	buf = malloc(BUFFER_SIZE * sizeof (char) + 1);
	if (!buf)
		return (NULL);
	rd = 1;
	while (ft_strchr((stock), '\n') == 0 && rd != 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buf);
			free(stock);
			return (NULL);
		}
		buf[rd] = '\0';
		stock = gnl_strjoin(stock, buf);
	}
	free(buf);
	return (stock);
}

char	*one_line(char	*stock)
{
	int		i;
	char	*line;

	i = 0;
	if (!stock[i])
		return (NULL);
	while (stock[i] != '\n' && stock[i])
		i++;
	line = malloc((i * sizeof (char)) + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] != '\n' && stock[i])
	{
		line[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_rest(char	*stock)
{
	char	*rest;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	if (!stock[i++])
	{
		free(stock);
		return (NULL);
	}
	rest = malloc((ft_strlen(stock) - i) * sizeof (char) + 1);
	if (!rest)
		return (NULL);
	while (stock[i] != '\0')
	{
		rest[j] = stock[i];
		i++;
		j++;
	}
	rest[j] = '\0';
	free(stock);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock = fill_stock(fd, stock);
	if (!stock)
		return (NULL);
	line = one_line(stock);
	stock = get_rest(stock);
	return (line);
}
