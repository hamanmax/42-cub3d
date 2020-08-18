/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 11:57:10 by mhaman            #+#    #+#             */
/*   Updated: 2020/08/09 11:09:56 by mhaman           ###   ########lyon.fr   */
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
#include "libft/libft.h"

enum			e_text
{
	NO,
	SO,
	WE,
	EA,
	SPRITE,
	TEXTURE_COUNT
};

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

typedef struct	s_cub
{
	t_int		screen;
	int			colorsky[4];
	int			colorfloor[4];
	int			northtexture;
	int			southtexture;
	int			easttexture;
	int			westtexture;
	int			spritetexture;
	char		**map;
	t_float		player_pos;
	t_int		player_pos_base;
	char		*text[TEXTURE_COUNT];
}				t_cub;

typedef	struct	s_ray
{
	int		id;
	float	t;
	int		angle;
	float	oppose;
	t_float	walldist;
	t_float	raypos[2];
	t_float	wallpos[2];
}				t_ray;

int		parse_file_cub(t_cub *map, char **argv, int argc);
int		check_instruction_validity(t_cub *map, char **argv);
int		check_texture_validity(t_cub *map, char *line);
int		check_type_texture(char *line);
int		check_map_validity(t_cub *map, char *found, char **line);
int		check_struct_validity(t_cub *map,size_t i);
int		check_color_validity(t_cub *map, char *line, int color[4]);
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
#endif
