/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gopars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:25:04 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/06 12:30:04 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	first_elem(t_pars *g)
{
	char	*tmp;

	tmp = g->line;
	while (*tmp == 32)
		tmp++;
	if (!ft_strncmp(tmp, "NO ", 3) && g->hash[0] != 'd')
		return (g->l++, 0);
	else if (!ft_strncmp(tmp, "WE ", 3) && g->hash[1] != 'd')
		return (g->l++, 1);
	else if (!ft_strncmp(tmp, "EA ", 3) && g->hash[2] != 'd')
		return (g->l++, 2);
	else if (!ft_strncmp(tmp, "SO ", 3) && g->hash[3] != 'd')
		return (g->l++, 3);
	else if (!ft_strncmp(tmp, "F ", 2) && g->hash[4] != 'd')
		return (g->l++, 4);
	else if (!ft_strncmp(tmp, "C ", 2) && g->hash[5] != 'd')
		return (g->l++, 5);
	return (-1);
}

int	second_elem(t_pars *g, char *s, int n)
{
	char	*sub;
	int		fd;
	int		start;

	start = 0;
	while (s[start] == 32)
		start++;
	start += 2;
	while (s[start] == 32)
		start++;
	sub = ft_substr(s, start, ft_strlen2(s) - start);
	if (n == 0)
		g->no = sub;
	else if (n == 1)
		g->we = sub;
	else if (n == 2)
		g->ea = sub;
	else if (n == 3)
		g->so = sub;
	fd = open(sub, O_RDWR);
	if (fd < 0)
		return (0);
	return (1);
}

void	valid_rgb(t_pars *g)
{
	char	*tmp;
	char	c;
	int 	i;

	tmp = g->line;
	while (*tmp == 32)
		tmp++;
	c = *tmp;
	tmp += 1;
	while (*tmp == 32)
		tmp++;
	i = 0;
	if (count_char(tmp, ',') != 2)
		write_error("More or less than 2 comma");
	while (tmp[i] != '\n')
	{
		if (tmp[i] != ',' && (tmp[i] < '0' || tmp[i] > '9'))
			write_error("Not valid RGB");
		i++;
	}
	g->rgb = ft_split(tmp, ',');
	if (ft_double_strlen(g->rgb) != 3)
		write_error("Not valid RGB");
	check_rgb(g, c);
}

void	check_rgb(t_pars *g, char c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (g->rgb[i])
	{
		num = ft_atoi(g->rgb[i]);
		if (num < 0 || num > 255)
			write_error("Not valid RGB");
		i++;
	}
	if (c == 'F')
		g->f = (ft_atoi(g->rgb[0]) * 65536) + (ft_atoi(g->rgb[1]) * 256) + ft_atoi(g->rgb[2]);
	else if (c == 'C')
		g->c = (ft_atoi(g->rgb[0]) * 65536) + (ft_atoi(g->rgb[1]) * 256) + ft_atoi(g->rgb[2]);
	free_splited(g->rgb);
}

int	valid_line (t_pars *g)
{
	int		ret;
	int		i;

	i = 0;
	while (g->line[i] == 32)
		i++;
	if (g->line[i] == '\n')
		return (-2);
	ret = first_elem(g);
	if (ret >= 0 && ret <= 3)
	{
		if (!second_elem(g, g->line, ret))
			write_error("Texture not valid");
		return (ret);
	}
	else if (ret == 4 || ret == 5)
	{
		valid_rgb(g);
		return (ret);
	}
	return (-1);
}
