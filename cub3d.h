/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 11:57:10 by mhaman            #+#    #+#             */
/*   Updated: 2020/10/15 10:16:27 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <mlx.h>
#include "libft/libft.h"
//#include "mlx.h"
//#include "mlx_int.h"

#define PI	3.14159265359
#define FOV	60
#define MVS 0.05
#define RTS 1

enum			e_text
{
	NO,
	SO,
	EA,
	WE,
	SPRITE,
	TEXTURE_COUNT
};

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
	int		*data;
	int		*data_text[TEXTURE_COUNT];
	void	*img;
	int		h[TEXTURE_COUNT];
	int		w[TEXTURE_COUNT];

}				t_mlx;

typedef	struct	s_float
{
	double	x;
	double	y;
}				t_float;

typedef	struct	s_ste
{
	double	start;
	double	end;
}				t_ste;


typedef	struct	s_raytab
{
	int		k;
	double	angle;
	double	oppose;
}				t_raytab;

typedef	struct	s_int
{
	int		x;
	int		y;
}				t_int;

typedef	struct	s_ray
{
	int		id;
	double	t;
	t_raytab tan;
	double	diffangle;
	double	walldist;
	double	wheight;
	int		texture;
	int		textpos;
	int		*data;
	int		w;
	t_float	pos[2];
	t_float	wallpos[2];
	t_float	pointpos;
}				t_ray;

typedef struct s_player
{
	t_float		pos;
	double		orientation;
	t_float		dir;
}				t_player;

typedef struct	s_cub
{
	t_int		screen;
	t_int		mapsize;
	int			colorsky;
	int			colorfloor;
	int			texture[TEXTURE_COUNT];
	char		*text[TEXTURE_COUNT];
	char		**map;
	int			nbsprite;
	t_player	player;
	t_mlx		mlx;
	t_ray		*ray;
	t_ray		*spr;
	t_raytab	*raytab;
	int			tabsize;
	int			kp;
}				t_cub;


int		parse_file_cub(t_cub *map, char **argv, int argc);
int		check_instruction_validity(t_cub *map, char **argv);
int		check_texture_validity(t_cub *map, char *line);
int		check_type_texture(char *line);
int		check_map_validity(t_cub *map, char *found, char **line);
int		check_struct_validity(t_cub *map,size_t i);
int		check_color_validity(t_cub *map, char *line,int i);
int		check_resolution_validity(t_cub *map, char *line);
int		check_file_validity(t_cub *map, char **argv, int argc);
int		ft_str_char_occur(char *str, int c);
int		ft_str_isdigit(char *str);
int		error_str_return(char *str);
void	resizing_map(t_cub *map);
int		test_map_integrity(t_cub *map, int nbline);
void	test_map_char_integrity(t_cub *map,int nbline, char buffer[256],int j);
int		test_map_overall_integrity(t_cub *map, int nbline);
int		test_map_validity(t_cub *map,int nbline);
int		check_around_char(char **tab, size_t x, size_t y, char *tofind);
int		raytracing(t_cub *map);
void	projection(t_cub *map);
t_float	set_wall_pos(float x, float y);
void	create_new_black_window(t_cub *map);
void	draw_base_ray(t_cub *map);
void	get_wall_lenght(t_cub *map);

#endif
