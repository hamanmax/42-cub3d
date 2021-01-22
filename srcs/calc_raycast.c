/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 21:15:43 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 16:36:27 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	calc_wallx(t_cub *map)
{
	double	wallx;

	if (map->side == 0)
		wallx = map->pla.pos.y + map->ray.perpdist * map->ray.dir.y;
	else
		wallx = map->pla.pos.x + map->ray.perpdist * map->ray.dir.x;
	wallx -= (int)wallx;
	return (wallx);
}

void	calc_tex(t_cub *map, double wallx)
{
	map->tex.x = (int)(wallx * (double)(map->mlx.w[map->textpx]));
	if (map->side == 0 && map->ray.dir.x > 0)
		map->tex.x = map->mlx.h[map->textpx] - map->tex.x - 1;
	if (map->side == 1 && map->ray.dir.y < 0)
		map->tex.x = map->mlx.h[map->textpx] - map->tex.x - 1;
	map->textstep = 1.0 * map->mlx.w[map->textpx] / map->ray.height;
	map->texpos = (map->draw.start - map->screen.y / 2 + map->ray.height / 2) *
	map->textstep;
}

void	calc_perp(t_cub *map)
{
	if (map->side == 0)
		map->ray.perpdist = (map->ray.pos.x - map->pla.pos.x +
		(1 - map->ray.step.x) / 2) / map->ray.dir.x;
	else
		map->ray.perpdist = (map->ray.pos.y - map->pla.pos.y +
		(1 - map->ray.step.y) / 2) / map->ray.dir.y;
	map->ray.height = (int)(map->screen.y / map->ray.perpdist);
}
