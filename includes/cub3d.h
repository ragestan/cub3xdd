/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:16:03 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/11 18:54:19 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>


# define WIDTH 1400
# define HIGHT 720
# define TOLE 40
# define ARD 24


typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_mlx;

typedef struct s_cube
{
	char **map;
	int  fc;
	int  cc;
	t_mlx mlx;
}			t_cube;

typedef struct s_pars
{
	char	**rgb;
	char	*hash;
	char	*line;
	int		l;
	int		l1;
	int		fd;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	t_mlx	mlx;
}			t_pars;

char		*get_next_line(int fd);
char		*gnl_strjoin(char *s1, char const *s2);
int			first_elem(t_pars *g);
int			second_elem(t_pars *g, char *s, int n);
void		valid_rgb(t_pars *g);
void		check_rgb(t_pars *g, char c);
int			valid_line(t_pars *g);
void		write_error(char *str);
void		loopars(t_pars *g);

//--------------------window.c--------------------

void	start(t_pars *g);
#endif