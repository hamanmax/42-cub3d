/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 11:57:10 by mhaman            #+#    #+#             */
/*   Updated: 2020/08/26 15:17:32 by mhaman           ###   ########lyon.fr   */
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
#include "mlx.h"
#include "mlx_int.h"

enum			e_text
{
	NO,
	SO,
	WE,
	EA,
	SPRITE,
	TEXTURE_COUNT
};

typedef struct	s_mlx
{
	void *mlx_ptr;
	void *win_ptr;

}				t_mlx;

typedef	struct	s_float
{
	double	x;
	double	y;
}				t_float;

typedef	struct	s_int
{
	int		x;
	int		y;
}				t_int;

typedef	struct	s_ray
{
	int		id;
	float	t;
	int		angle;
	float	oppose;
	float	walldist;
	float	wallheight;
	t_float	raypos[2];
	t_float	wallpos[2];
	t_float	pointpos;
}				t_ray;

typedef struct	s_cub
{
	t_int		screen;
	int			colorsky;
	int			colorfloor;
	int			texture[5];
	char		**map;
	double		projectiondist;
	float		wallheight;
	t_float		projection_id;
	t_float		projection_center;
	t_float		player_pos;
	t_int		player_pos_base;
	t_mlx		mlx;
	t_ray		ray[360];
	char		*text[TEXTURE_COUNT];
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
int		test_map_char_integrity(t_cub *map,int nbline, char buffer[256],int j);
int		test_map_overall_integrity(t_cub *map, int nbline);
int		test_map_validity(t_cub *map,int nbline);
int		check_around_char(char **tab, size_t x, size_t y, char *tofind);
int		raytracing(t_cub *map);
int		projection(t_cub *map);
int		check_player_orientation(t_cub *map);
t_float	set_wall_pos(float x, float y);
void create_new_black_window(t_cub *map);
void	draw_ray(t_cub *map,  int i, int j);
void    calc_correct_distance(t_cub *map, int i,int j);
#endif
