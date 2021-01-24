/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 21:17:07 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 16:47:27 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_ray(t_cub *map, int i)
{
	map->ray.pos.x = (int)map->pla.pos.x;
	map->ray.pos.y = (int)map->pla.pos.y;
	map->pla.camera.x = 2 * i / (double)map->screen.x - 1;
	map->ray.dir.x = map->pla.dir.x + map->pla.plane.x * map->pla.camera.x;
	map->ray.dir.y = map->pla.dir.y + map->pla.plane.y * map->pla.camera.x;
}

void	set_texture(t_cub *map)
{
	if (map->side)
	{
		if (map->ray.dir.y < 0)
			map->textpx = 2;
		else
			map->textpx = 3;
	}
	else
	{
		if (map->ray.dir.x < 0)
			map->textpx = 1;
		else
			map->textpx = 0;
	}
}

void	set_start_to_end(t_ste *draw, int height, t_int size, int sx)
{
	if (sx == 0)
	{
		draw[0].start = -height / 2 + size.y / 2;
		if (draw[0].start < 0)
			draw[0].start = 0;
		draw[0].end = height / 2 + size.y / 2;
		if (draw[0].end >= size.y)
			draw[0].end = size.y - 1;
	}
	else
	{
		draw[0].start = -height / 2 + sx;
		if (draw[0].start < 0)
			draw[0].start = 0;
		draw[0].end = height / 2 + sx;
		if (draw[0].end >= size.x)
			draw[0].end = size.x;
	}
}

void	set_sprite(t_cub *map)
{
	int			i;
	double		invdet;
	int			scx;

	i = -1;
	while (++i < map->nbsprite)
	{
		map->spr.x = map->sprite[i].pos.x - map->pla.pos.x;
		map->spr.y = map->sprite[i].pos.y - map->pla.pos.y;
		invdet = 1.0 /
		(map->pla.plane.x * map->pla.dir.y - map->pla.dir.x * map->pla.plane.y);
		map->trans.x = invdet * (map->pla.dir.y * map->spr.x -
		map->pla.dir.x * map->spr.y);
		map->trans.y = invdet * (-map->pla.plane.y *
		map->spr.x + map->pla.plane.x * map->spr.y);
		scx = (int)((map->screen.x / 2) * (1.0 + map->trans.x / map->trans.y));
		map->spriteheight = abs((int)(map->screen.y / map->trans.y));
		set_start_to_end(&map->sprite_y, map->spriteheight, map->screen, 0);
		set_start_to_end(&map->sprite_x, map->spriteheight, map->screen, scx);
		draw_sprite(map, map->sprite_x.start, scx, map->trans);
	}
}

void	sort_sprite(t_cub *map)
{
	t_sprite	temp;
	int			i;

	i = 0;
	while (i < map->nbsprite - 1)
	{
		if (map->sprite[i].dist < map->sprite[i + 1].dist)
		{
			temp = map->sprite[i];
			map->sprite[i] = map->sprite[i + 1];
			map->sprite[i + 1] = temp;
			i = -1;
		}
		i++;
	}
}
