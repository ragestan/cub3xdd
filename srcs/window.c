/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:00:44 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/06 11:11:13 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	find_player(t_cube *cube)
{
	int x;
	int y;

	y = 0;
	while(y < (int)ft_double_strlen(cube->map))
	{
		x = 0;
		while (x < (int)ft_strlen(cube->map[y]))
		{
			x++;
			if (cube->map[y][x] == 'N' || cube->map[y][x] == 'S' || cube->map[y][x] == 'E' || cube->map[y][x] == 'W')
			{
				cube->player.x = x * TOLE + TOLE / 2;
				cube->player.y = y * TOLE + TOLE / 2;
				//printf("player found at %d/%d\n",x,y);
				cube->player.posx = 0;
				cube->player.posy = 0;
				if (cube->map[y][x] == 'N')
					cube->player.angle = 3 * M_PI / 2;
				else if (cube->map[y][x] == 'S')
					cube->player.angle = M_PI / 2;
				else if (cube->map[y][x] == 'E')
					cube->player.angle = 0;
				else if (cube->map[y][x] == 'W')
					cube->player.angle = M_PI;
				//printf("player found at %d/%d\n",x,y);
				return ;
			}
		}
		y++;
	}
}

void draw_line(t_cube *cube)
{
	int i;
	int x;
	float	angle;

	i = 0;
	angle = -30;
	x = 0;
	while (angle <= 30)
	{
		i = 0;
		while (1)
		{
			//my_mlx_pixel_put(cube, ((cube->player.x) + i * cos(cube->player.angle - (angle * M_PI / 180))) * MINIMAP_SCALE , ((cube->player.y ) + i * sin(cube->player.angle - (angle * M_PI / 180))) * MINIMAP_SCALE, 0xFF0000);
			i++;
			if(cube->map[(int)(((cube->player.y) + i * (sin(cube->player.angle - (angle * M_PI / 180)))) / TOLE)][(int) ((((cube->player.x) + (i * cos(cube->player.angle - (angle * M_PI / 180)))) / TOLE))] == '1')
			{
				d_game(cube,i,x);
				break;
			}
		}
		x += WIDTH / 300;
		angle += 0.1;
	}
}

void	draw_down(t_cube *cube,int y,int tmp_x)
{
	int x;

	while(y < HIGHT)
	{
		x = tmp_x;
		while(x < WIDTH && x <= tmp_x + WIDTH/300)
		{
			my_mlx_pixel_put(cube,x,y,0x9BA4B5);
			x++;
		}
		y++;
	}
}

void	draw_up(t_cube *cube,int y,int tmp_x)
{
	int x;

	while(y > 0)
	{
		x = tmp_x;
		while(x < WIDTH && x <= tmp_x + WIDTH/300)
		{
			my_mlx_pixel_put(cube,x,y,0xF1F6F9);
			x++;
		}
		y--;
	}
}

void	draw_wall(t_cube *cube,int c,int tmp_x)
{
	int y;
	int x;

	y = HIGHT/2 - c/2;
	while(y < HIGHT && y <= HIGHT/2 + c/2)
	{
		x = tmp_x;
		while(x < WIDTH && x <= tmp_x + WIDTH/300)
		{
			my_mlx_pixel_put(cube,x,y,0x394867);
			x++;
		}
		y++;	
	}
	draw_up(cube,HIGHT/2 - c/2,tmp_x);
	draw_down(cube,HIGHT/2 + c/2,tmp_x);
}

void	d_game(t_cube *cube,int i,int x)
{
	float c;
	float tmp_x;

	tmp_x = (float)50/i;
	
	c = tmp_x * ((WIDTH/2) / tan(30 * M_PI / 180));
	if (c > HIGHT)
		c = HIGHT;
	draw_wall(cube,c,x);
	
}

int	close_pro(t_cube *cube)
{
	mlx_destroy_window(cube->mlx.mlx_ptr, cube->mlx.win_ptr);
	exit(0);
}

int	no_move(int keycode,t_cube *cube)
{
	if (keycode == 2)
		cube->player.lor = 0;
	if (keycode == 0)
		cube->player.lor = 0;
	if (keycode == 13)
		cube->player.uod = 0;
	if (keycode == 1)
		cube->player.uod = 0;
	return(0);
}

int move(int keycode,t_cube *cube)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 0) //d
	{
		cube->player.lor = -1;
		// cube->player.x += 5 * cos(cube->player.angle + (M_PI / 2));
		// cube->player.y += 5 * sin(cube->player.angle + (M_PI / 2));
		// if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x - 5) / TOLE )] == '1')
		// {
		// 	cube->player.x -= 5 * cos(cube->player.angle + (M_PI / 2));
		// 	cube->player.y -= 5 * sin(cube->player.angle + (M_PI / 2));	
		// }
		// cube->player.posx = 1;
	}
	if (keycode == 2) //a
	{
		cube->player.lor = 1;
		// cube->player.x += 5 * cos(cube->player.angle - (M_PI / 2));
		// cube->player.y += 5 * sin(cube->player.angle - (M_PI / 2));
		// if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] == '1')
		// {
		// 	cube->player.x -= 5 * cos(cube->player.angle - (M_PI / 2));
		// 	cube->player.y -= 5 * sin(cube->player.angle - (M_PI / 2));
		// }
		// cube->player.posx = 1;
	}
	if (keycode == 13) //w
	{
		cube->player.uod = -1;
		// cube->player.x += 5 * cos(cube->player.angle);
		// cube->player.y += 5 * sin(cube->player.angle);
		// if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x - 5) / TOLE )] == '1')
		// {
		// 	cube->player.x -= 5 * cos(cube->player.angle);
		// 	cube->player.y -= 5 * sin(cube->player.angle);
		// }
		// cube->player.posy = 1;
	}
	if (keycode == 1) //s
	{
		 cube->player.uod = 1;
		// cube->player.x -= 5 * cos(cube->player.angle);
		// cube->player.y -= 5 * sin(cube->player.angle);
		// if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] == '1')
		// {
		// 	cube->player.x += 5 * cos(cube->player.angle);
		// 	cube->player.y += 5 * sin(cube->player.angle);
		// }
		// cube->player.posy = 1;
	}
	if (keycode == 124)
		cube->player.angle -= 0.01 * M_PI;
	if (keycode == 123)
		cube->player.angle += 0.01 * M_PI;
	if (cube->player.angle > 2 * M_PI)
		cube->player.angle -= 2 * M_PI;
	if (cube->player.angle < 0)
		cube->player.angle += 2 * M_PI;
	return(0);
}

void	draw_square(t_cube *cube,int x,int y,int f)
{
	int z;
	int k;

	z = 0;
	k = 0;
	while(z < TOLE)
	{
		k = 0;
		if (f == cube->cc && z == TOLE - 1)
		{
				z++;
				continue;
		}
		while(k < TOLE)
		{
			if (f == cube->cc && k == TOLE - 1)
			{
				k++;
				continue;
			}
			my_mlx_pixel_put(cube, x + z, y + k, f);
			k++;
		}
		z++;
	}
}

void	draw_player(t_cube *cube,float x,float y)
{
	int z;
	int k;
	(void)x;
	(void)y;
	
	z = 0;
	k = 0;
	//printf("x = %f,y = %f\n",cube->player.x,cube->player.y);
	
	while(z < PLAYER_S)
	{
		
		k = 0;
		if (z == TOLE - 1)
		{
			z++;
			continue;
		}
		while(k < PLAYER_S)
		{
			if (k == TOLE - 1)
			{
				k++;
				continue;
			}
			my_mlx_pixel_put(cube, (int)((cube->player.x  + z - PLAYER_S / 2) * MINIMAP_SCALE ), (int)((cube->player.y + k - PLAYER_S / 2) * MINIMAP_SCALE), 0xffff00);
			k++;
		}
		z++;
	}
}

// void	check(t_cube *cube)
// {
// 	if (cube->player.posx >= TOLE/2)
// 	{
// 		cube->map[cube->player.y][cube->player.x] = '0';
// 		cube->player.x++;
// 	}
// 	if (cube->player.posx <= -TOLE/2)
// 	{
// 		cube->map[cube->player.y][cube->player.x] = '0';
// 		cube->player.x--;
// 	}
// 	if (cube->player.posy >= TOLE/2)
// 	{
// 		cube->map[cube->player.y][cube->player.x] = '0';
// 		cube->player.y++;
// 	}
// 	if (cube->player.posy <= -TOLE/2)
// 	{
// 		cube->map[cube->player.y][cube->player.x] = '0';
// 		cube->player.y--;
// 	}
// }

int	draw(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	draw_line(cube);
	while (i < (int)ft_double_strlen(cube->map))
	{
		j = 0;
		while (j < (int)ft_strlen(cube->map[i]))
		{
			if (cube->map[i][j] == '1')
				draw_square(cube, j * TOLE * MINIMAP_SCALE, i * TOLE * MINIMAP_SCALE,cube->fc);
			else if (cube->map[i][j] == '0')
				draw_square(cube, j * TOLE * MINIMAP_SCALE, i * TOLE * MINIMAP_SCALE,cube->cc);	
			if (cube->map[i][j] == 'S' || cube->map[i][j] == 'N' || cube->map[i][j] == 'W' || cube->map[i][j] == 'E')
				draw_square(cube, j * TOLE * MINIMAP_SCALE, i * TOLE *MINIMAP_SCALE,cube->cc);
			j++;
		}
		i++;
	}
	draw_player(cube, cube->player.x * MINIMAP_SCALE , cube->player.y * MINIMAP_SCALE);
	i = 0;
	while (i < 50)
	{
		my_mlx_pixel_put(cube, ((cube->player.x) + i * cos(cube->player.angle)) * MINIMAP_SCALE , ((cube->player.y ) + i * sin(cube->player.angle)) * MINIMAP_SCALE, 0xFF0000);
		i++;
	}
	
	
	return (0);
}

void	my_mlx_pixel_put(t_cube *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.data + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int update_player(t_cube *cube)
{
	if (cube->player.lor == -1)
	{
		cube->player.x += 5 * cos(cube->player.angle + (M_PI / 2));
		cube->player.y += 5 * sin(cube->player.angle + (M_PI / 2));
		if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x - 5) / TOLE )] == '1')
		{
			cube->player.x -= 5 * cos(cube->player.angle + (M_PI / 2));
			cube->player.y -= 5 * sin(cube->player.angle + (M_PI / 2));	
		}
		cube->player.posx = 1;
	}
	if (cube->player.lor == 1)
	{
		cube->player.x += 5 * cos(cube->player.angle - (M_PI / 2));
		cube->player.y += 5 * sin(cube->player.angle - (M_PI / 2));
		if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] == '1')
		{
			cube->player.x -= 5 * cos(cube->player.angle - (M_PI / 2));
			cube->player.y -= 5 * sin(cube->player.angle - (M_PI / 2));
		}
		cube->player.posx = 1;
	}
	if (cube->player.uod == -1)
	{
		cube->player.x += 5 * cos(cube->player.angle);
		cube->player.y += 5 * sin(cube->player.angle);
		if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x - 5) / TOLE )] == '1')
		{
			cube->player.x -= 5 * cos(cube->player.angle);
			cube->player.y -= 5 * sin(cube->player.angle);
		}
		cube->player.posy = 1;
	}
	if (cube->player.uod == 1)
	{
		cube->player.x -= 5 * cos(cube->player.angle);
		cube->player.y -= 5 * sin(cube->player.angle);
		if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] == '1')
		{
			cube->player.x += 5 * cos(cube->player.angle);
			cube->player.y += 5 * sin(cube->player.angle);
		}
		cube->player.posy = 1;
	}
	return (0);
}

int	update(t_cube *cube)
{
	mlx_clear_window(cube->mlx.mlx_ptr, cube->mlx.win_ptr);
	cube->mlx.img = mlx_new_image(cube->mlx.mlx_ptr, WIDTH, HIGHT);
	cube->mlx.data = mlx_get_data_addr(cube->mlx.img, &cube->mlx.bits_per_pixel, &cube->mlx.line_length, &cube->mlx.endian);
	update_player(cube);
	draw(cube);
	mlx_put_image_to_window(cube->mlx.mlx_ptr, cube->mlx.win_ptr, cube->mlx.img, 0, 0);
	mlx_destroy_image(cube->mlx.mlx_ptr, cube->mlx.img);
	return (0);
}

int	rotation(int x,int y ,t_cube *cube)
{
	(void)y;
	
	if (x > WIDTH / 2 && x < WIDTH)
		cube->player.angle -= 0.1;
	else if (x < WIDTH / 2 && x > 0)
		cube->player.angle += 0.1;
	return (1);
}

void	start(t_pars *g)
{
	t_cube cube;
	
	cube.map = g->rgb;
	cube.fc = g->f;
	cube.cc = g->c;
	find_player(&cube);
	cube.mlx.mlx_ptr = mlx_init();
	cube.mlx.win_ptr = mlx_new_window(cube.mlx.mlx_ptr, WIDTH, HIGHT, "cub3d");
	mlx_hook(cube.mlx.win_ptr, 17, 0, close_pro, &cube);
	mlx_hook(cube.mlx.win_ptr, 2, 0, move, &cube);
	mlx_hook(cube.mlx.win_ptr, 6, 0, rotation, &cube);
	mlx_hook(cube.mlx.win_ptr, 3, 0, no_move, &cube);
	//draw(&cube);
	mlx_loop_hook(cube.mlx.mlx_ptr, update, &cube);
	mlx_loop(cube.mlx.mlx_ptr);
}
