/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 11:57:10 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/23 10:53:49 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <stddef.h>
#include "keycode.h"
#include "../minilibx-linux/mlx.h"
#include "../libft/include/libft.h"

#define MVS 0.05
#define RTS 0.10

enum			e_text
{
	NO,
	SO,
	EA,
	WE,
	SPRITE,
	TEXTURE_COUNT
};

typedef struct		s_bpm
{
	unsigned char	bitmap_type[2];
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
}					t_bpm;

typedef struct		s_bpm2
{
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}			t_bpm2;

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
	int		*data;
	int		*data_text[TEXTURE_COUNT];
	void	*img;
	void	*img_txt[TEXTURE_COUNT];
	int		bpp;
	int		line_size;
	int		endien;
	int		h[TEXTURE_COUNT];
	int		w[TEXTURE_COUNT];

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

typedef	struct	s_ste
{
	int		start;
	int		end;
}				t_ste;

typedef struct s_player
{
	t_float		pos;
	char		orientation;
	t_float		dir;
	t_float		plane;
	t_float		camera;
}				t_player;

typedef struct s_move
{
	int		forward;
	int		backward;
	int		rightside;
	int		leftside;
	int		rightrot;
	int		leftrot;
	int		close;
}			t_move;

typedef struct	s_sprite
{
	t_float	pos;
	double	dist;
}				t_sprite;

typedef struct	s_ray
{
	t_float		dir;
	t_int		pos;
	t_float		sdist;
	t_float		ddist;
	double		perpdist;
	t_int		step;
	int			height;
}				t_ray;

typedef struct	s_cub
{
	t_int		screen;
	int			colorsky;
	int			colorfloor;
	int			texture[TEXTURE_COUNT];
	char		*text[TEXTURE_COUNT];
	char		**map;
	int			*screenpx;
	int			hit;
	int			side;
	int			textpx;
	double		textstep;
	t_int		tex;
	double		texpos;
	t_ste		draw;
	t_int		mapsize;
	t_mlx		mlx;
	t_ray		ray;
	t_player	pla;
	int			spriteheight;
	t_ste		sprite_y;
	t_ste		sprite_x;
	int			nbsprite;
	t_sprite	*sprite;
	t_move		move;
	double		zbuffer[1920];
	int			color;
	t_float		spr;
	t_float		trans;
	int		screenshot;
}				t_cub;

void	parse_file_cub(t_cub *map, char **argv, int argc);
int		check_instruction_validity(t_cub *map, char **argv);
int		check_texture_validity(t_cub *map, char *line);
int		check_type_texture(char *line);
int		check_map_validity(t_cub *map, char *found, char **line);
int		check_struct_validity(t_cub *map,size_t i);
int		check_color_validity(t_cub *map, char *line,int i);
int		check_resolution_validity(t_cub *map, char *line);
void	check_file_validity(t_cub *map,char **argv, int argc);
void	check_around_map(t_cub *map,int i, int j, int nbline);
int		error_str_return(char *str);
void	resizing_map(t_cub *map);
int		test_map_integrity(t_cub *map, int nbline);
void	test_map_char_integrity(t_cub *map,int nbline, char buffer[256],int j);
int		test_map_overall_integrity(t_cub *map, int nbline);
int		test_map_validity(t_cub *map,int nbline);
int		check_around_char(char **tab, size_t x, size_t y, char *tofind);
int		main_loop(t_cub *map);
void	raycasting(t_cub *map);
int		deal_key(int key,t_cub *map);
void	move(t_cub *map);
void	move_ws(t_cub *map);
void	move_ad(t_cub *map);
void	rotation_qe(t_cub *map);
void	set_data(t_cub *map);
void	load_sprite(t_cub *map);
void	set_start_to_end(t_ste *draw, int height, t_int size, int sx);
void	set_dir_plane_vector(t_cub *map);
void	set_texture(t_cub *map);
void	set_ray(t_cub *map, int i);
void	free_cub(t_cub *map);
void	set_sprite(t_cub *map);
void	sort_sprite(t_cub *map);
void	set_backgroud(t_cub *map);
void	draw(t_cub *map);
void	set_wall(t_cub *map,int x);
void	draw_sprite(t_cub *map,int st, int spritescreenx,t_float trans);
double	calc_wallx(t_cub *map);
void	calc_tex(t_cub *map, double wallx);
void	calc_perp(t_cub *map);
int		closecub(t_cub *map, int code);
void		ft_save_bitmap(const char *filename, t_cub *map);

#endif
