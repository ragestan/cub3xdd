/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:54:05 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/11 18:09:58 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	write_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit (1);
}

void	check_ext(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len <= 4 || (str[len - 1] != 'b'
		|| str[len - 2] != 'u'
		|| str[len - 3] != 'c'
		|| str[len - 4] != '.'))
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd("Not valid extension\n", 2);
		exit (1);
	}
}

void	loopars(t_pars *g)
{
	int	j;

	while (1)
	{
		if (g->l == 6)
			break;
		g->line = get_next_line(g->fd);
		if (!g->line)
			break;
		j = valid_line(g);
		if (j == -1)
			write_error("Not a valid identifier");
		free(g->line);
		if (j == -2)
			continue;
		if (j >= 0 || j <= 5)
			g->hash[j] = 'd';
	}
	if (g->l < 6)
		write_error("Missing data");
}

void	g_init(t_pars *g)
{
	int	i;

	i = 0;
	g->rgb = NULL;
	g->hash = NULL;
	g->line = NULL;
	g->l = 0;
	g->l1 = 0;
	g->f = 0;
	g->c = 0;
	g->hash = malloc (7);
	g->hash[6] = '\0';
	while (i++ < 6)
		g->hash[i] = 'x';
}

int	this_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] == 32)
		i++;
	if (s[i] == '\0')
		return (0);
	else if (s[i] == '1')
	{
		while (s[i])
		{
			if (s[i] != '1' && s[i] != 32)
				write_error ("Up or down invalid wall"); // dont forget to free the slaves
			i++;
		}
	}
	return (1);
}

void	check_first_last_wall(t_pars *g, int n)
{
	if (n == -1)
	{
		g->l = n;
		while (g->rgb[++g->l])
		{
			if (this_line(g->rgb[g->l]))
				break;
		}
	}
	else
	{
		g->l1 = n;
		while (g->rgb[g->l1])
		{
			if (this_line(g->rgb[g->l1]))
				break;
			g->l1--;
		}
	}
}

void	check_middle(t_pars *g)
{
	int	len;
	int	i;

	g->l++;
	while (g->l < g->l1)
	{
		i = 0;
		len = ft_strlen(g->rgb[g->l]) - 1;
		while (g->rgb[g->l][len] == 32)
			len--;
		while (g->rgb[g->l][i] == 32)
			i++;
		if (g->rgb[g->l][i] != '1' || g->rgb[g->l][len] != '1')
			write_error("Left or right wall broken");
		while (++i < len)
		{
			if (g->rgb[g->l][i] == '0'
			|| g->rgb[g->l][i] == 'E'
			|| g->rgb[g->l][i] == 'W'
			|| g->rgb[g->l][i] == 'N'
			|| g->rgb[g->l][i] == 'S')
				if (g->rgb[g->l - 1][i] == 32
				|| g->rgb[g->l + 1][i] == 32
				|| g->rgb[g->l][i - 1] == 32
				|| g->rgb[g->l][i + 1] == 32)
					write_error("Map invalid middle");
		}
		g->l++;
	}
}

void	check_map_char(char *s)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	j = ft_strlen(s) - 1;
	d = 0;
	while (s[i] != '1' && s[i])
		i++;
	while (s[j] != '1' && j > 0)
		j--;
	if (s[i] == '\0')
		write_error("Invalid map");
	while (i <= j)
	{
		if (s[i] == 'N' || s[i] == 'S'
		|| s[i] == 'E' || s[i] == 'W')
		{
			if (d == 0)
				d++;
			else
				write_error("Player char repeated");
		}
		else if (s[i] != '0' && s[i] != 32 && s[i] != '1' && s[i] != '\n')
			write_error("Wrong char in map");
		else if (s[i] == '\n' && s[i + 1] == '\n')
			write_error("Double endl");
		i++;
	}
	if (!d)
		write_error("Player missing");
}

void	mapars(t_pars *g)
{
	free(g->hash);
	g->hash = NULL;
	while (1)
	{
		g->line = get_next_line(g->fd);
		if (!g->line)
			break;
		g->hash = gnl_strjoin(g->hash, g->line);
		free(g->line);
	}
	// allocation : map + joined
	check_map_char(g->hash);
	g->rgb = ft_split(g->hash, '\n');
	check_first_last_wall(g, -1);
	check_first_last_wall(g, ft_double_strlen(g->rgb) - 1);
	check_middle(g);
}

int main(int ac, char **av)
{
	t_pars	g;

	if (ac != 2)
		(ft_putstr_fd("Error\nNot valid ARGS\n", 2), exit(1));
	check_ext(av[1]);
	g_init(&g);
	g.fd = open (av[1], O_RDWR);
	if (g.fd < 0)
		write_error("Wrong map path");
	loopars(&g);
	mapars(&g);
	printf("done getting lines\n");
	start(&g);
}