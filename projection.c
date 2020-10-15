/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:02:24 by mhaman            #+#    #+#             */
/*   Updated: 2020/10/09 10:59:37 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int set_texture(t_cub *map, int i)
{
	const double a = map->ray[i].tan.angle;
	int j;

	j = 1;
	if (i < map->screen.x - 1 && map->ray[i].wallpos[0].x != map->ray[i].wallpos[1].x)
		j = 2;
	if (a >= 90 && a <= 270 && j == 1)
		j = 0;
	if (a >= 0 && a <= 180 && j == 2)
		j = 3;
	return (j);
}

t_ste set_start_to_end(t_cub *map, int len, int i,int k)
{
	t_ste ste;

	ste.start = (map->mlx.w[k] * map->ray[i].t);
	if (map->ray[i + len].t < map->ray[i].t)
		ste.start = (map->mlx.w[k] * (1-map->ray[i].t));
	if (map->ray[i].t < 0.05 || map->ray[i].t > 0.95)
		ste.start = 0;
	ste.end = (map->mlx.w[k] * map->ray[i + len].t);
	if (map->ray[i + len].t < map->ray[i].t)
		ste.end = (map->mlx.w[k] * (1 - map->ray[i + len].t));
	if (map->ray[i + len].t < 0.05 || map->ray[i + len].t > 0.95)
		ste.end = map->mlx.w[k];
	return (ste);
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

int set_textpos(t_cub *map, int width,int i)
{
	int ret;
	const double angle = map->ray[i].tan.angle;

	ret = 0;
	if (angle > 180 && map->ray[i].wallpos[0].x != map->ray[i].wallpos[1].x)
	{
		ret = (1 - map->ray[i].t) * width;
	}
	else
	{
		ret = map->ray[i].t * width;
	}
	return(ret);
}

void get_wall_lenght(t_cub *map)
{
	int i;

	i = 0;
	while (i < map->screen.x)
	{
		map->ray[i].texture = set_texture(map, i);
		map->ray[i].textpos = set_textpos(map, map->mlx.w[set_texture(map, i)], i);
		map->ray[i].diffangle = map->mlx.w[set_texture(map, i)] / map->ray[i].wheight;
		map->ray[i].data = map->mlx.data_text[set_texture(map,i)];
		map->ray[i].w = map->mlx.w[set_texture(map , i)];
		if (map->ray[i].wheight > map->screen.y)
			map->ray[i].wheight = map->screen.y;
		i++;
	}
}