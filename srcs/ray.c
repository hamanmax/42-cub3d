/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:03:13 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 22:11:46 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <assert.h>

void	set_next_wall_dist(t_cub *map)
{
	map->ray.ddist.x = fabs(1 / map->ray.dir.x);
	map->ray.ddist.y = fabs(1 / map->ray.dir.y);
	if (map->ray.dir.x < 0)
	{
		map->ray.step.x = -1;
		map->ray.sdist.x = (map->pla.pos.x - map->ray.pos.x) * map->ray.ddist.x;
	}
	else
	{
		map->ray.step.x = 1;
		map->ray.sdist.x =
		(map->ray.pos.x + 1.0 - map->pla.pos.x) * map->ray.ddist.x;
	}
	if (map->ray.dir.y < 0)
	{
		map->ray.step.y = -1;
		map->ray.sdist.y = (map->pla.pos.y - map->ray.pos.y) * map->ray.ddist.y;
	}
	else
	{
		map->ray.step.y = 1;
		map->ray.sdist.y =
		(map->ray.pos.y + 1.0 - map->pla.pos.y) * map->ray.ddist.y;
	}
}

void	perform_dda(t_cub *map)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (map->ray.sdist.x < map->ray.sdist.y)
		{
			map->ray.sdist.x += map->ray.ddist.x;
			map->ray.pos.x += map->ray.step.x;
			map->side = 0;
		}
		else
		{
			map->ray.sdist.y += map->ray.ddist.y;
			map->ray.pos.y += map->ray.step.y;
			map->side = 1;
		}
		if (map->map[(int)map->ray.pos.x][(int)map->ray.pos.y] == '1')
			hit = 1;
	}
}

int		main_loop(t_cub *map)
{
	move(map);
	raycasting(map);
	draw(map);
	mlx_put_image_to_window(map->mlx.ptr, map->mlx.win, map->mlx.img, 0, 0);
	return (0);
}

void	raycast_sprite(t_cub *map)
{
	int		i;

	i = 0;
	while (i < map->nbsprite)
	{
		map->sprite[i].dist = ((map->pla.pos.x - map->sprite[i].pos.x) *
		(map->pla.pos.x - map->sprite[i].pos.x) + (map->pla.pos.y -
		map->sprite[i].pos.y) * (map->pla.pos.y - map->sprite[i].pos.y));
		i++;
	}
	sort_sprite(map);
	set_sprite(map);
}

void	raycasting(t_cub *map)
{
	int		i;
	double	wallx;

	i = 0;
	set_backgroud(map);
	while (i < map->screen.x)
	{
		set_ray(map, i);
		set_next_wall_dist(map);
		perform_dda(map);
		calc_perp(map);
		set_start_to_end(&map->draw, map->ray.height, map->screen, 0);
		set_texture(map);
		wallx = calc_wallx(map);
		calc_tex(map, wallx);
		set_wall(map, i);
		map->zbuffer[i] = map->ray.perpdist;
		i++;
	}
	raycast_sprite(map);
}
