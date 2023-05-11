/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:00:44 by zbentalh          #+#    #+#             */
/*   Updated: 2023/05/11 18:53:49 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_cube *cube,int x,int y,int f)
{
	int z;
	int k;

	z = 0;
	k = 0;
	while(z < TOLE)
	{
		k = 0;
		while(k < TOLE)
		{
			mlx_pixel_put(cube->mlx.mlx_ptr, cube->mlx.win_ptr, x + z, y + k, f);
			k++;
		}
		z++;
	}
}

int	draw(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while (i < (int)ft_double_strlen(cube->map))
	{
		j = 0;
		while (j < (int)ft_strlen(cube->map[i]))
		{
			if (cube->map[i][j] == '1')
				draw_square(cube, j * TOLE, i * TOLE,cube->fc);
			else if (cube->map[i][j] == '0')
				draw_square(cube, j * TOLE, i * TOLE,cube->cc);
			j++;
		}
		i++;
	}
	return (0);
}

void	start(t_pars *g)
{
	t_cube cube;
	
	cube.map = g->rgb;
	cube.fc = g->f;
	cube.cc = g->c;
	
	cube.mlx.mlx_ptr = mlx_init();
	cube.mlx.win_ptr = mlx_new_window(cube.mlx.mlx_ptr, WIDTH, HIGHT, "cub3d");
	mlx_loop_hook(cube.mlx.mlx_ptr, draw, &cube);
	mlx_loop(cube.mlx.mlx_ptr);
}
