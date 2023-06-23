/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:00:44 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/23 12:11:03 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	texture(t_cube *cube)
{
	cube->text[0].img = mlx_xpm_file_to_image(cube->mlx.mlx_ptr, "srcs/l.xpm", &cube->text[0].width, &cube->text[0].hight);
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

void	find_player(t_cube *cube,int x,int y)
{
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

t_hit	*hit_init(t_hit *hit,double angle)
{
	hit->angle = angle;
	hit->vertical= 0;
	return(hit);
}

t_hitfinder y_and_ystep(t_cube * cube,t_hitfinder h, double angle)
{
		h.y = floor(cube->player.y / TOLE) * TOLE;
	h.ystep = TOLE;
	if (angle < M_PI && angle > 0)
		h.y += TOLE;	
	else
		h.ystep = -TOLE;
	return (h);
}
t_hitfinder x_and_xstep(t_cube *cube, t_hitfinder h,double angle)
{
	h.x = cube->player.x + ((h.y - cube->player.y) / tan(angle));
	h.xstep = TOLE / tan(angle);
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2 && h.xstep > 0)
		h.xstep *= -1;
	return (h);
}

t_hitfinder finder_init(void)
{
	t_hitfinder h;

	h.x = 0;
	h.y = 0;
	h.xstep = 0;
	h.ystep = 0;
	return (h);
}

void	horizintol_hit(t_cube *cube,double angle,t_hit *hit)
{
	t_hitfinder h;
	
	h = finder_init();
	hit = hit_init(hit,angle);
	if (angle == 0 || angle == M_PI || angle == 2 * M_PI)
		return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));
	h = y_and_ystep(cube,h,angle);
	h = x_and_xstep(cube,h,angle);
	if (angle > M_PI && angle < 2 * M_PI)
		h.y--;
	if ((int)floor(h.y/TOLE) > (int)ft_double_strlen(cube->map) || (int)floor(h.y/TOLE) < 0 || (int)floor(h.x/TOLE) > (int)ft_stlen_v2(cube->map,(int)floor(h.y/TOLE)) || (int)floor(h.x/TOLE) < 0)
		return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));	
	step_check(angle,&h.xstep,&h.ystep);
	while (cube->map[(int)floor(h.y / TOLE)] && cube->map[(int)floor(h.y / TOLE)][(int)floor(h.x / TOLE)] && cube->map[(int)floor(h.y / TOLE)][(int)floor(h.x / TOLE)] != '1')
	{
		h.y += h.ystep;
		h.x += h.xstep;
		if ((int)floor(h.y/TOLE) > (int)ft_double_strlen(cube->map) || (int)floor(h.y/TOLE) < 0 || (int)floor(h.x/TOLE) > (int)ft_stlen_v2(cube->map,(int)floor(h.y/TOLE)) || (int)floor(h.x/TOLE) < 0)
			return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));
	}
	if (angle > M_PI && angle < 2 * M_PI)
		h.y++;
	hit->x = h.x;
	hit->y = h.y;
}

t_hitfinder x_and_xstep_vertical(t_cube *cube,double angle,t_hitfinder h)
{
	h.x = floor(cube->player.x / TOLE) * TOLE;
	h.xstep = TOLE;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		h.xstep = -TOLE;
	else
		h.x += TOLE;
	return (h);
}

t_hitfinder y_and_ystep_vertical(t_cube *cube,double angle,t_hitfinder h)
{
	h.y = cube->player.y + ((h.x - cube->player.x) * tan(angle));
	h.ystep = TOLE * tan(angle);
	if (angle > M_PI && angle < 2*M_PI && h.ystep > 0)
		h.ystep *= -1;
	return (h);
}

t_hit *distance_calcu(t_cube *cube,t_hit *hit,t_hitfinder h)
{
	if (sqrt(pow(hit->x - cube->player.x,2) + pow(hit->y - cube->player.y,2)) > sqrt(pow(h.x - cube->player.x,2) + pow(h.y - cube->player.y,2)))
	{
		hit->x = h.x;
		hit->y = h.y;
		hit->vertical = 1;
	}
	return(hit);
}

void	vertical_hit(t_cube *cube,double angle,t_hit *hit)
{
	t_hitfinder h;
	
	h = finder_init();
	if (cube->map[(int)floor(cube->player.y / TOLE)][(int)floor(cube->player.x / TOLE)] == '1' || angle == 3 * M_PI / 2 || angle == M_PI / 2)
		return;
	h = x_and_xstep_vertical(cube,angle,h);
	h = y_and_ystep_vertical(cube,angle,h);
	if ((int)floor(h.y/TOLE) >= (int)ft_double_strlen(cube->map) || (int)floor(h.y/TOLE) < 0 || (int)floor(h.x/TOLE) >= (int)ft_stlen_v2(cube->map,(int)floor(h.y/TOLE)) || (int)floor(h.x/TOLE) < 0)
			return;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		h.x--;
	step_check(angle,&h.xstep,&h.ystep);
	while (cube->map[(int)floor(h.y / TOLE)] && cube->map[(int)floor(h.y / TOLE)][(int)floor(h.x / TOLE)] && cube->map[(int)floor(h.y / TOLE)][(int)floor(h.x / TOLE)] != '1')
	{
		h.y += h.ystep;
		h.x += h.xstep;
		if ((int)floor(h.y/TOLE) >= (int)ft_double_strlen(cube->map) || (int)floor(h.y/TOLE) < 0 || (int)floor(h.x/TOLE) >= (int)ft_stlen_v2(cube->map,(int)floor(h.y/TOLE)) || (int)floor(h.x/TOLE) < 0)
			return;
	}
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		h.x++;
	hit = distance_calcu(cube,hit,h);
}

void draw_all(t_cube *cube)
{
	t_hit x;
	double	angle;
	int i;
	int y;

	y = 0;
	i = 0;
	angle = cube->player.angle - 30 * M_PI / 180;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	while (i < WIDTH)
	{
		horizintol_hit(cube,angle,&x);
		vertical_hit(cube,angle,&x);
		d_game(cube,sqrt(pow(x.x - cube->player.x, 2) + pow(x.y - cube->player.y, 2)),y,x);
		y++;
		i++;
		angle += (60 * M_PI / 180 ) / (WIDTH);
		if (angle > 2 * M_PI)
			angle -= 2 * M_PI;
		if (angle < 0)
			angle += 2 * M_PI;
	}
}

void	draw_down(t_cube *cube,int y,int tmp_x)
{
	while(y < HIGHT)
	{
		my_mlx_pixel_put(cube,tmp_x,y,cube->cc);
		y++;
	}
}

void	draw_up(t_cube *cube,int y,int tmp_x)
{
	while(y > 0)
	{
		my_mlx_pixel_put(cube,tmp_x,y,cube->fc);
		y--;
	}
}

float	calcul_c(int y,int c)
{
	float i;

	i = 0;
	while (y <= HIGHT/2 + c/2)
	{
		y++;
		i++;
	}
	return (i);
}

t_draw draw_init(int c,t_hit hit)
{
	t_draw draw;
	
	draw.y = HIGHT/2 - c/2;
	draw.i = (float) (TOLE / calcul_c(draw.y,c));
	draw.z = (hit.x / TOLE - (int)(hit.x / TOLE)) * TOLE;
	draw.r = (hit.y / TOLE - (int)(hit.y / TOLE)) * TOLE;
	draw.l = 0;
	return (draw);
}

void	draw_wall(t_cube *cube,int c,int tmp_x,t_hit hit)
{
	t_draw draw;
	
	draw = draw_init(c,hit);
	while(draw.y < HIGHT && draw.y <= HIGHT/2 + c/2)
	{
		if (hit.vertical == 1)
		{
			if (hit.angle > M_PI / 2 && hit.angle < 3 * M_PI / 2)
				my_mlx_pixel_put(cube,tmp_x,draw.y,texture_color(cube,draw.r,(int)draw.l,0));
			else
				my_mlx_pixel_put(cube,tmp_x,draw.y,texture_color(cube,draw.r,(int)draw.l,1));
		}
		else
			if (hit.angle > 0 && hit.angle < M_PI)
				my_mlx_pixel_put(cube,tmp_x,draw.y,texture_color(cube,draw.z,(int)draw.l,2));
			else
				my_mlx_pixel_put(cube,tmp_x,draw.y,texture_color(cube,draw.z,(int) draw.l,3)); 
		draw.y++;
		draw.l += draw.i;
	}
	draw_up(cube,HIGHT/2 - c/2,tmp_x);
	draw_down(cube,HIGHT/2 + c/2,tmp_x);
}

void	d_game(t_cube *cube,float i,int x,t_hit hit)
{
	double c;
	float tmp_x;

	tmp_x = (float)TOLE/i;
	c = tmp_x * ((WIDTH/2) / tan(30 * M_PI / 180));
	if (c > 2000)
		c = 2000;
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
	if (keycode == 124)
		cube->player.a = 0;
	if (keycode == 123)
		cube->player.a = 0;
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
		cube->player.a = - 1;
	if (keycode == 123)
		cube->player.a = 1;
	return(0);
}

void	my_mlx_pixel_put(t_cube *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HIGHT)
		return ;
	dst = data->mlx.data + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int wall_check_test(t_cube *cube)
{
	if (cube->map[(int)((cube->player.y + 10) / TOLE)][(int)((cube->player.x) / TOLE )] == '1' && cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x + 10) / TOLE)] == '1')
		return (1);
	if (cube->map[(int)((cube->player.y + 10) / TOLE)][(int)((cube->player.x) / TOLE )] == '1' && cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x - 10) / TOLE)] == '1')
		return (1);
	if (cube->map[(int)((cube->player.y - 10) / TOLE)][(int)((cube->player.x) / TOLE )] == '1' && cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x + 10) / TOLE)] == '1')
		return (1);
	if (cube->map[(int)((cube->player.y - 10) / TOLE)][(int)((cube->player.x) / TOLE )] == '1' && cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x - 10) / TOLE )] == '1')
		return (1);
	return (0);
}

void	update_player_toward_left(t_cube *cube)
{
	cube->player.x += 5 * cos(cube->player.angle - (M_PI / 2));
	cube->player.y += 5 * sin(cube->player.angle - (M_PI / 2));
	if (cube->map[(int)((cube->player.y ) / TOLE)][(int)((cube->player.x - 10) / TOLE )] && (cube->map[(int)((cube->player.y ) / TOLE)][(int)((cube->player.x - 10) / TOLE )] == '1' || wall_check_test(cube) == 1))
	{
		cube->player.x -= 5 * cos(cube->player.angle - (M_PI / 2));
		cube->player.y -= 5 * sin(cube->player.angle - (M_PI / 2));
	}
	return ;
}

void	update_player_toward_right(t_cube *cube)
{
	cube->player.x += 5 * cos(cube->player.angle + (M_PI / 2));
	cube->player.y += 5 * sin(cube->player.angle + (M_PI / 2));
	if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x + 10) / TOLE )] && (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x + 10) / TOLE )] == '1' || wall_check_test(cube) == 1))
	{
		cube->player.x -= 5 * cos(cube->player.angle + (M_PI / 2));
		cube->player.y -= 5 * sin(cube->player.angle + (M_PI / 2));	
	}
	return ;
}

void	update_player_forward(t_cube *cube)
{
	cube->player.x +=  5 * cos(cube->player.angle);
	if(cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] && (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] == '1' || wall_check_test(cube) == 1))
		cube->player.x -=  5 * cos(cube->player.angle);
	cube->player.y += 5 * sin(cube->player.angle);
	if(cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] && (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] == '1' || wall_check_test(cube) == 1))
		cube->player.y -= 5 * sin(cube->player.angle);
	return ;
}

void	update_player_backward(t_cube *cube)
{
	cube->player.x -=  5 * cos(cube->player.angle);
	if(cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] && (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] == '1' || wall_check_test(cube) == 1))
		cube->player.x +=  5 * cos(cube->player.angle);
	cube->player.y -= 5 * sin(cube->player.angle);
	if(cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] && (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x) / TOLE )] == '1' || wall_check_test(cube) == 1))
		cube->player.y += 5 * sin(cube->player.angle);
	return ;
}

int update_player(t_cube *cube)
{
	if (cube->player.lor == -1) //d
		update_player_toward_right(cube);
	else if (cube->player.lor == 1) //a
		update_player_toward_left(cube);
	if (cube->player.uod == -1) //w
		update_player_forward(cube);
	else if (cube->player.uod == 1) //s
		update_player_backward(cube);
	if (cube->player.a == -1)
		cube->player.angle -= 0.01 * M_PI;
	else if (cube->player.a == 1)
		cube->player.angle += 0.01 * M_PI;
	if (cube->player.angle > 2 * M_PI)
		cube->player.angle -= 2 * M_PI;
	if (cube->player.angle < 0)
		cube->player.angle += 2 * M_PI;
	return (0);
}

int	update(t_cube *cube)
{
	mlx_clear_window(cube->mlx.mlx_ptr, cube->mlx.win_ptr);
	cube->mlx.img = mlx_new_image(cube->mlx.mlx_ptr, WIDTH, HIGHT);
	cube->mlx.data = mlx_get_data_addr(cube->mlx.img, &cube->mlx.bits_per_pixel, &cube->mlx.line_length, &cube->mlx.endian);
	update_player(cube);
	draw_all(cube);
	mlx_put_image_to_window(cube->mlx.mlx_ptr, cube->mlx.win_ptr, cube->mlx.img, 0, 0);
	mlx_destroy_image(cube->mlx.mlx_ptr, cube->mlx.img);
	return (0);
}

int	rotation(int x,int y ,t_cube *cube)
{
	(void)y;
	static int tmp;

	if ((x > WIDTH / 2 && x < WIDTH && tmp == 0) || x > tmp)
	{
		cube->player.angle -= 0.03;
		tmp = x;
	}
	else if ((x < WIDTH / 2 && x > 0 && tmp == 0) || x < tmp)
	{
		cube->player.angle += 0.03;
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
	find_player(&cube ,0 , 0);
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
