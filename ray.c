/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:03:13 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/15 17:07:45 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <assert.h>

void	set_next_wall_dist(t_cub *map)
{
	map->ray.deltadist.x = fabs(1 / map->ray.dir.x);
	map->ray.deltadist.y = fabs(1 / map->ray.dir.y);
	if (map->ray.dir.x < 0)
	{
		map->ray.step.x = -1;
		map->ray.sidedist.x = (map->player.pos.x - (int)map->player.pos.x) * map->ray.deltadist.x;
	}
	else
	{
		map->ray.step.x = 1;
		map->ray.sidedist.x = (map->player.pos.x + 1 - (int)map->player.pos.x) * map->ray.deltadist.x;
	}
	if (map->ray.dir.y < 0)
	{
		map->ray.step.y = -1;
		map->ray.sidedist.y = (map->player.pos.y - (int)map->player.pos.y) * map->ray.deltadist.y;
	}
	else
	{
		map->ray.step.y = 1;
		map->ray.sidedist.y = (map->player.pos.y + 1 - (int)map->player.pos.y) * map->ray.deltadist.y;
	}
}

void	perform_dda(t_cub *map)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (map->ray.sidedist.x < map->ray.sidedist.y)
		{
			map->ray.sidedist.x += map->ray.deltadist.x;
			map->ray.pos.x += map->ray.step.x;
			map->side = 0;
		}
		else
		{
			map->ray.sidedist.y += map->ray.deltadist.y;
			map->ray.pos.y += map->ray.step.y;
			map->side = 1;

		}
			dprintf(1,"%f\n",map->ray.sidedist.y);
			//dprintf(1,"%c\n",map->map[(int)map->ray.pos.x][(int)map->ray.pos.y]);
		if (map->map[(int)map->ray.pos.x][(int)map->ray.pos.y] == '1')
		{
			dprintf(1,"%d\t%d\n",map->ray.pos.x,map->ray.pos.y);
			hit = 1;
		}
	}
}

int		raycasting(t_cub *map)
{
		int i;

		i = 0;
		while (i <= map->screen.x)
		{
			map->player.camera.x = 2 * i / (double)map->screen.x - 1;
			map->ray.dir.x = map->player.dir.x + map->player.plane.x * map->player.camera.x;
			map->ray.dir.y = map->player.dir.y + map->player.plane.y * map->player.camera.y;
			set_next_wall_dist(map);
			perform_dda(map);
			if (map->side == 0)
				map->ray.perpdist = (map->ray.pos.x - map->player.pos.x + (1 - map->ray.step.x) / 2) / map->ray.dir.x;
			else
				map->ray.perpdist = (map->ray.pos.y - map->player.pos.y + (1 - map->ray.step.y) / 2) / map->ray.dir.y;
			map->ray.height = (int)(map->screen.y / map->ray.perpdist);
			map->draw.start = (-map->ray.height / 2) + map->screen.y / 2;
			if (map->draw.start < 0)
				map->draw.start = 0;
			map->draw.end = -map->ray.height / 2 + map->screen.y / 2;
			if (map->draw.end >= map->screen.y)
				map->draw.end = map->screen.y - 1;
			dprintf(1,"perpdist=%d\n",map->ray.height);
			i++;
		}
		return(0);
}