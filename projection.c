/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:02:24 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/18 11:54:32 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int set_texture(t_cub *map, int i)
{
	const double a = map->ray[i].angle;
	int j;

	j = 1;
	if ( i < map->screen.x - 1 && map->ray[i].pointpos.y == map->ray[i + 1].pointpos.y)
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

	ste.start = map->mlx.width * map->ray[i].t;
	if (map->ray[i].t < 0.09 || map->ray[i].t > 0.95)
		ste.start = 0;
	ste.end = map->mlx.width * map->ray[i].t;
	if (i + len < map->screen.x - 1 && (map->ray[i + len].t < 0.05 || map->ray[i + len].t > 0.95))
		ste.end = map->mlx.width;
	return (ste);
}

void set_color_ray(t_cub *map, int len, int i)
{
	const int k = set_texture(map, i);
	int l;
	void *img;
	int *data;
	double m;
	int		n;
	double diffangle2;
	t_ste width;

	l = 0;
	n = 0;
	m = 0;
	img = mlx_xpm_file_to_image(map->mlx.ptr, map->text[k], &map->mlx.width, &map->mlx.height);
	data = (int *)mlx_get_data_addr(img, &map->mlx.bpp, &map->mlx.line_size, &map->mlx.endian);
	width = set_start_to_end(map, len, i);
	while (n < len)
	{
		diffangle2 = map->mlx.width / map->ray[i + n].wallheight;
		while (l < (int)map->ray[i + n].wallheight)
		{
			map->ray[i + n].color[l] = data[(map->mlx.width * (int)m) + n];
			l++;
			if (width.start == 0)
				width.start = map->mlx.width;
			m += diffangle2;
		}
		m = 0;
		l = 0;
		n++;
	}
}

int check_wall_end(t_cub *map, int i)
{
	if (i < map->screen.x - 1 && map->ray[i].pointpos.x == map->ray[i + 1].pointpos.x)
	{
		if ((int)map->ray[i].pointpos.y != (int)map->ray[i + 1].pointpos.y)
			return (1);
		if (map->ray[i].pointpos.y != map->ray[i + 1].pointpos.y)
			return (0);
	}
	if (i < map->screen.x - 1 && map->ray[i].pointpos.y == map->ray[i + 1].pointpos.y)
	{
		if ((int)map->ray[i].pointpos.x != (int)map->ray[i + 1].pointpos.x)
			return (1);
		if (map->ray[i].pointpos.x != map->ray[i + 1].pointpos.x)
			return (0);
	}
	return (1);
}

void get_wall_lenght(t_cub *map)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i + j < map->screen.x)
	{
		if (check_wall_end(map, j + i) == 1)
		{
			j += i;
			set_color_ray(map, i, j - i + 1);
			i = 0;
		}
		i++;
	}
	set_color_ray(map, i, j);
}

void projection(t_cub *map)
{
	get_wall_lenght(map);
	//set_color_ray();
}