/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:00:44 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/17 16:51:15 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	my_mlx_pixel_put2(t_cube *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->test.so + (y * data->test.line_length + x * (data->test.bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

void	texture(t_cube *cube)
{
	cube->text[0].img = mlx_xpm_file_to_image(cube->mlx.mlx_ptr, "srcs/l.xpm", &cube->text[0].width, &cube->text[0].hight);
	//printf("width = %d hight = %d\n",cube->text[0].width ,cube->text[0].hight);
	cube->text[0].data = mlx_get_data_addr(cube->text[0].img, &cube->text[0].bits_per_pixel, &cube->text[0].line_length, &cube->text[0].endian);
	cube->text[1].img = mlx_xpm_file_to_image(cube->mlx.mlx_ptr, "srcs/r.xpm", &cube->text[1].width, &cube->text[1].hight);
	cube->text[1].data = mlx_get_data_addr(cube->text[1].img, &cube->text[1].bits_per_pixel, &cube->text[1].line_length, &cube->text[1].endian);
	cube->text[2].img = mlx_xpm_file_to_image(cube->mlx.mlx_ptr, "srcs/u.xpm", &cube->text[2].width, &cube->text[2].hight);
	cube->text[2].data = mlx_get_data_addr(cube->text[2].img, &cube->text[2].bits_per_pixel, &cube->text[2].line_length, &cube->text[2].endian);
	cube->text[3].img = mlx_xpm_file_to_image(cube->mlx.mlx_ptr, "srcs/d.xpm", &cube->text[3].width, &cube->text[3].hight);
	cube->text[3].data = mlx_get_data_addr(cube->text[3].img, &cube->text[3].bits_per_pixel, &cube->text[3].line_length, &cube->text[3].endian);
	return;	
}


int texture_color(t_cube *cube, int x, int y, int i)
{
	char *dst;
	int color;

	//printf("x = %d y = %d\n",cube->text[i].width ,cube->text[i].hight);
	if (x < 0 || y < 0 || x >= cube->text[i].width || y >= cube->text[i].hight)
		return (0);
	dst = cube->text[i].data + (y * cube->text[i].line_length + x * (cube->text[i].bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

int ft_stlen_v2(char **str,int y)
{
	int i;

	i = 0;
	while (str[y][i])
		i++;
	return (i);
}

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
				return ;
			}
		}
		y++;
	}
}

void	step_check(double angle,float *xstep,float *ystep)
{
	if (angle > 0 && angle < M_PI && *ystep < 0)
		*ystep *= -1;
	else if (angle < 2 * M_PI && angle > M_PI && *ystep > 0)
		*ystep *= -1;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2 && *xstep > 0)
		*xstep *= -1;
	else if (((angle < M_PI / 2 && angle < 0) || (angle > 3 * M_PI / 2 && angle < 2 * M_PI)) && *xstep < 0)
		*xstep *= -1;
}

void	horizintol_hit(t_cube *cube,double angle,t_hit *hit)
{
	float x;
	float y;
	float xstep;
	float ystep;
	
	// printf("test == %i\n",ft_stlen_v2(cube->map,18));
	// exit(0);
	if (angle == 0 || angle == M_PI || angle == 2 * M_PI)
		return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));
	y = floor(cube->player.y / TOLE) * TOLE;
	ystep = TOLE;
	if (angle < M_PI && angle > 0)
		y += TOLE;	
	else
		ystep = -TOLE;
	
	x = cube->player.x + ((y - cube->player.y) / tan(angle));
	
	xstep = TOLE / tan(angle);
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2 && xstep > 0)
		xstep *= -1;
	if (angle > M_PI && angle < 2 * M_PI)
		y--;
	if ((int)floor(y/TOLE) > (int)ft_double_strlen(cube->map) || (int)floor(y/TOLE) < 0)
		return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));
	if ((int)floor(x/TOLE) > (int)ft_stlen_v2(cube->map,(int)floor(y/TOLE)) || (int)floor(x/TOLE) < 0)
		return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));	
	step_check(angle,&xstep,&ystep);
	while (cube->map[(int)floor(y / TOLE)] && cube->map[(int)floor(y / TOLE)][(int)floor(x / TOLE)] && cube->map[(int)floor(y / TOLE)][(int)floor(x / TOLE)] != '1')
	{
		// if (x < TOLE && x + xstep < TOLE && xstep < 0)
		// 	return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));
		y += ystep;
		x += xstep;
		if ((int)floor(y/TOLE) > (int)ft_double_strlen(cube->map) || (int)floor(y/TOLE) < 0)
			return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));
		if ((int)floor(x/TOLE) > (int)ft_stlen_v2(cube->map,(int)floor(y/TOLE)) || (int)floor(x/TOLE) < 0)
			return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));
		//printf("i =%i\n",ft_strlen_x(cube->map));
		//printf("x = %f y = %f\n",x,y);
		//printf("x = %i y = %i\n",(int)floor(x / TOLE),(int)floor(y / TOLE));
		// printf("%c\n",cube->map[(int)floor(y / TOLE)][(int)floor(x / TOLE)]);
	}
	if (angle > M_PI && angle < 2 * M_PI)
		y++;
	hit->x = x;
	hit->y = y;
}

void	vertical_hit(t_cube *cube,double angle,t_hit *hit)
{
	float x;
	float y;
	float xstep;
	float ystep;
	
	if (cube->map[(int)floor(cube->player.y / TOLE)][(int)floor(cube->player.x / TOLE)] == '1')
		return;
	if (angle == 3 * M_PI / 2 || angle == M_PI / 2)
		return;
	x = floor(cube->player.x / TOLE) * TOLE;
	xstep = TOLE;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		xstep = -TOLE;
	else
		x += TOLE;
	y = cube->player.y + ((x - cube->player.x) * tan(angle));
	ystep = TOLE * tan(angle);
	if (angle > M_PI && angle < 2*M_PI && ystep > 0)
		ystep *= -1;
	if ((int)floor(y/TOLE) >= (int)ft_double_strlen(cube->map) || (int)floor(y/TOLE) < 0)
			return;
	if ((int)floor(x/TOLE) >= (int)ft_stlen_v2(cube->map,(int)floor(y/TOLE)) || (int)floor(x/TOLE) < 0)
			return;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		x--;
	step_check(angle,&xstep,&ystep);
	while (cube->map[(int)floor(y / TOLE)] && cube->map[(int)floor(y / TOLE)][(int)floor(x / TOLE)] && cube->map[(int)floor(y / TOLE)][(int)floor(x / TOLE)] != '1')
	{
		
		y += ystep;
		x += xstep;
		if ((int)floor(y/TOLE) >= (int)ft_double_strlen(cube->map) || (int)floor(y/TOLE) < 0)
			return;
		if ((int)floor(x/TOLE) >= (int)ft_stlen_v2(cube->map,(int)floor(y/TOLE)) || (int)floor(x/TOLE) < 0)
			return;
	}
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		x++;
	hit->vertical= 0;
	hit->angle = angle;
	if (sqrt(pow(hit->x - cube->player.x,2) + pow(hit->y - cube->player.y,2)) > sqrt(pow(x - cube->player.x,2) + pow(y - cube->player.y,2)))
	{
		hit->x = x;
		hit->y = y;
		hit->vertical = 1;
	}
}

void draw_line(t_cube *cube)
{
	t_hit x;
	double	angle;
	int i = 0;
	int y;
	

	y = 0;
	x.x = 0;
	x.y = 0;
	angle = cube->player.angle - 30 * M_PI/180;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	while (i < WIDTH)
	{
		horizintol_hit(cube,angle,&x);
		vertical_hit(cube,angle,&x);
		// int f;
		// int z;
		// f = x.x;
		// //printf("%f,%f\n",x.x,x.y);	
		// if (x.x != DBL_MAX && x.y != DBL_MAX)
		// {
		// 	while( f < x.x + 5)
		// 	{
		// 		z = x.y;
		// 		while(z < x.y + 5)
		// 		{
			
		// 			if (z < 0 || f < 0 || z > 1400 || f > 720)
		// 				break;
		// 			if (x.x < 20 && angle > M_PI / 2 && angle < 3 * M_PI / 2)
		// 			//printf(" x = %d,%f,%f,%f,%f\n",f,cube->player.x,cube->player.y,x.z,x.f);
		// 			my_mlx_pixel_put(cube, (f +  cos(angle)) * MINIMAP_SCALE , (z + sin(angle)) * MINIMAP_SCALE, 0xffffff);
		// 			z++;
		// 		}
		// 		if (z < 0 || f < 0 || z > 1400 || f > 720)
		// 				break;
		// 		f++;
		// 	}
		// }
		//  my_mlx_pixel_put(cube, ((x.x) +  sin(angle)) * MINIMAP_SCALE , ((x.y) + cos(angle)) * MINIMAP_SCALE, 0x9BA4B5);
		//printf("%f--->%f\n",x.x,x.y);
		//exit(0);
		d_game(cube,sqrt(pow(x.x - cube->player.x, 2) + pow(x.y - cube->player.y, 2)),y,x);
		//printf("%f\n",sqrt(pow(x.x - cube->player.x, 2) + pow(x.y - cube->player.y, 2)));
		y++;
		i++;
		//printf("%i\n",y);
		angle += (60 * M_PI / 180 ) / (WIDTH);
		if (angle > 2 * M_PI)
			angle -= 2 * M_PI;
		if (angle < 0)
			angle += 2 * M_PI;
	}
	//exit(1);
}

void	draw_down(t_cube *cube,int y,int tmp_x)
{
	(void)cube;
	while(y < HIGHT)
	{
		my_mlx_pixel_put(cube,tmp_x,y,cube->cc);
		y++;
	}
}

void	draw_up(t_cube *cube,int y,int tmp_x)
{
	(void)cube;
	while(y > 0)
	{
		my_mlx_pixel_put(cube,tmp_x,y,cube->fc);
		y--;
	}
}

void	draw_wall(t_cube *cube,int c,int tmp_x,t_hit hit)
{
	int y;
	int z;
	int l;
	y = HIGHT/2 - c/2;
	z = (hit.x / TOLE - (int)(hit.x / TOLE)) * TOLE;
	l = (hit.y / TOLE - (int)(hit.y / TOLE)) * TOLE;
	while(y < HIGHT && y <= HIGHT/2 + c/2)
	{
		if (hit.vertical == 1)
		{
			if (hit.angle > M_PI / 2 && hit.angle < 3 * M_PI / 2)
			{
				//printf("up\n");
				my_mlx_pixel_put(cube,tmp_x,y,texture_color(cube,z,l,0));//khdr
				//printf("down\n");
			}
			else
				my_mlx_pixel_put(cube,tmp_x,y,texture_color(cube,z,l,1));//rose
		}
		else
			if (hit.angle > 0 && hit.angle < M_PI)
				my_mlx_pixel_put(cube,tmp_x,y,texture_color(cube,z,l,2));//zr9
			else
				my_mlx_pixel_put(cube,tmp_x,y,texture_color(cube,z,l,3)); //sfr
		y++;	
	}
	draw_up(cube,HIGHT/2 - c/2,tmp_x);
	draw_down(cube,HIGHT/2 + c/2,tmp_x);
}

void	d_game(t_cube *cube,float i,int x,t_hit hit)
{
	float c;
	float tmp_x;

	tmp_x = (float)TOLE/i;
	c = tmp_x * ((WIDTH/2) / tan(30 * M_PI / 180));
	if (c > HIGHT)
		c = HIGHT;
	draw_wall(cube,c,x,hit);
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
	if (keycode == 2) //d
		cube->player.lor = -1;
	if (keycode == 0) //a
		cube->player.lor = 1;
	if (keycode == 13) //w
		cube->player.uod = -1;
	if (keycode == 1) //s
		 cube->player.uod = 1;
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
	(void)x, (void)y;
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
			//printf("x = %i y = %i\n",x + z,y + k);
			// if (cube->map[(int)floor(y + k/ TOLE)][(int)floor(x + z/ TOLE)] != ' ')
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
		
	// && cube->map[(int)floor( i * sin(cube->player.angle)/ TOLE)][(int)floor(((cube->player.x) + i * cos(cube->player.angle)) / TOLE)] != '1'
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
	static int tmp;

	if (x > WIDTH / 2 && x < WIDTH && tmp == 0)
	{
		cube->player.angle -= 0.03;
		tmp = x;
	}
	else if (x < WIDTH / 2 && x > 0 && tmp == 0)
	{
		cube->player.angle += 0.03;
		tmp = x;
	}
	else if (x < tmp)
	{
		cube->player.angle += 0.03;
		tmp = x;
	}
	else if (x > tmp)
	{
		cube->player.angle -= 0.03;
		tmp = x;
	}
	if (tmp < 0)
		tmp++;
	if (tmp > WIDTH)
		tmp--;
	if (cube->player.angle > 2 * M_PI)
		cube->player.angle -= 2 * M_PI;
	if (cube->player.angle < 0)
		cube->player.angle += 2 * M_PI;
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
	texture(&cube);
	mlx_hook(cube.mlx.win_ptr, 17, 0, close_pro, &cube);
	mlx_hook(cube.mlx.win_ptr, 2, 0, move, &cube);
	mlx_hook(cube.mlx.win_ptr, 6, 0, rotation, &cube);
	mlx_hook(cube.mlx.win_ptr, 3, 0, no_move, &cube);
	mlx_loop_hook(cube.mlx.mlx_ptr, update, &cube);
	mlx_loop(cube.mlx.mlx_ptr);
}
