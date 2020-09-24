/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:02:24 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/24 12:33:03 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int set_texture(t_cub *map, int i)
{
	const double a = map->ray[i].angle;
	int j;

	j = 1;
	if (i < map->screen.x - 1 && map->ray[i].pointpos.y == map->ray[i + 1].pointpos.y)
		j = 2;
	if (a >= 90 && a <= 270 && j == 1)
		j = 0;
	if (a >= 0 && a <= 180 && j == 2)
		j = 3;
	return (j);
}

t_ste set_start_to_end(t_cub *map, int len, int i)
{
	t_ste ste;

	ste.start = (int)(map->mlx.w * map->ray[i].t);
	if (map->ray[i + len].t < map->ray[i].t)
		ste.start = (int)(map->mlx.w * (1-map->ray[i].t));
	if (map->ray[i].t < 0.05 || map->ray[i].t > 0.95)
		ste.start = 0;
	ste.end = (int)(map->mlx.w * map->ray[i + len].t);
	if (map->ray[i + len].t < map->ray[i].t)
		ste.end = (int)(map->mlx.w * (1 - map->ray[i + len].t));
	if (map->ray[i + len].t < 0.05 || map->ray[i + len].t > 0.95)
		ste.end = (int)map->mlx.w;
	return (ste);
}

int set_color(double ligne,double colonne,double width)
{
	return((int)(ligne) * width + colonne);
}

void set_color_ray(t_cub *map, int len, int i)
{
	const int k = set_texture(map, i);
	int col;
	t_ste width;

	map->mlx.img = mlx_xpm_file_to_image(map->mlx.ptr,
	map->text[k], &map->mlx.w, &map->mlx.h);
	map->mlx.data = (int *)mlx_get_data_addr(map->mlx.img,
	&map->mlx.bpp, &map->mlx.line_size, &map->mlx.endian);
	width = set_start_to_end(map, len - 1, i);
	while ((int)map->b < len)
	{
		map->diffangle2 = (width.end - width.start) / (double)len;
		while ((int)map->a <= (int)map->ray[i + (int)map->b].wheight)
		{
			map->diffangle = map->mlx.h / (map->ray[i + (int)map->b].wheight);
			col = set_color(map->a * map->diffangle,
			(map->b * map->diffangle2) + width.start,map->mlx.h);
			map->ray[i + (int)map->b].color[(int)map->a] = map->mlx.data[col];
			map->a++;
		}
		map->a = 0;
		map->b++;
	}
}

int check_wall_end(t_cub *map, int i)
{
	if (map->ray[i].wallpos[1].x != map->ray[i - 1].wallpos[1].x)
		return (1);
	if (map->ray[i].wallpos[1].y != map->ray[i - 1].wallpos[1].y)
		return (1);
	if (map->ray[i].wallpos[0].x != map->ray[i - 1].wallpos[0].x)
		return (1);
	if (map->ray[i].wallpos[0].y != map->ray[i - 1].wallpos[0].y)
		return (1);
	return (0);
}

void get_wall_lenght(t_cub *map)
{
	int i;
	int j;

	j = 1;
	i = 1;

	while (i + j < map->screen.x)
	{
		if (check_wall_end(map, j + i) != 0)
		{
			set_color_ray(map, i, j);
			map->b = 0;
			j += i;
			i = 0;
		}
		i++;
	}
	set_color_ray(map, i - 1, j);
}

void projection(t_cub *map)
{
	get_wall_lenght(map);
	//set_color_ray();
	mlx_destroy_image(map->mlx.ptr,map->mlx.img);
}