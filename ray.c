/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:03:13 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/17 08:17:28 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <assert.h>


int	set_screenpx(t_cub *map)
{
	int x;
	int y;
	int i;
	
	x = 0;
	y = 0;
	i = 0;
	while (x < map->screen.x / 2)
	{
		while (y < map->screen.y)
		{
			map->screenpx[x][y] = map->colorsky;
			map->screenpx[x + map->screen.x / 2][y] = map->colorfloor;
			y++;
		}
		x++;
		y = 0;
	}
	x = 0;
	y = 0;
	while (x < map->screen.x)
	{
		while (y < map->screen.y)
		{
			map->mlx.data[i] = map->screenpx[x][y];
			y++;
			i++;
		}
		x++;
		y = 0;
	}
}

void	set_next_wall_dist(t_cub *map)
{
	map->ray.deltadist.x = fabs(1 / map->ray.dir.x);
	map->ray.deltadist.y = fabs(1 / map->ray.dir.y);
	if (map->ray.dir.x < 0)
	{
		map->ray.step.x = -1;
		map->ray.sidedist.x = (map->player.pos.x - map->ray.pos.x) * map->ray.deltadist.x;
	}
	else
	{
		map->ray.step.x = 1;
		map->ray.sidedist.x = (map->ray.pos.x + 1.0 - map->player.pos.x) * map->ray.deltadist.x;
	}
	if (map->ray.dir.y < 0)
	{
		map->ray.step.y = -1;
		map->ray.sidedist.y = (map->player.pos.y - map->ray.pos.y) * map->ray.deltadist.y;
	}
	else
	{
		map->ray.step.y = 1;
		map->ray.sidedist.y = (map->ray.pos.y + 1.0 - map->player.pos.y) * map->ray.deltadist.y;
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
		if (map->map[(int)map->ray.pos.x][(int)map->ray.pos.y] == '1')
		{
			hit = 1;
		}
	}
}

void draw_wall(t_cub *map,int j)
{
	int i;

	i = map->draw.start;
	while (i <= map->draw.end)
	{
		mlx_pixel_put(map->mlx.ptr, map->mlx.win,j,i,1356585);
		if (map->side== 1)
			mlx_pixel_put(map->mlx.ptr, map->mlx.win,j,i,2556585);
		i++;
	}
}

int		raycasting(t_cub *map)
{
		int i;

		i = 0;
		int j = 0;
		set_screenpx(map);
		map->mlx.win = mlx_new_window(map->mlx.ptr, map->screen.x, map->screen.y, "Cub3d");
		mlx_put_image_to_window(map->mlx.ptr,map->mlx.win,map->mlx.img,0,0);
		i = 0;
		while (i <= map->screen.x)
		{
			map->ray.pos.x = (int)map->player.pos.x;
			map->ray.pos.y = (int)map->player.pos.y;
			map->player.camera.x = 2 * i / (double)map->screen.x - 1;
			map->ray.dir.x = map->player.dir.x + map->player.plane.x * map->player.camera.x;
			map->ray.dir.y = map->player.dir.y + map->player.plane.y * map->player.camera.x;
			set_next_wall_dist(map);
			perform_dda(map);
			if (map->side == 0)
				map->ray.perpdist = (map->ray.pos.x - map->player.pos.x + (1 - map->ray.step.x) / 2) / map->ray.dir.x;
			else
				map->ray.perpdist = (map->ray.pos.y - map->player.pos.y + (1 - map->ray.step.y) / 2) / map->ray.dir.y;
			map->ray.height = (int)(map->screen.y / map->ray.perpdist);
			map->draw.start = -map->ray.height / 2 + map->screen.y / 2;
			if (map->draw.start < 0)
				map->draw.start = 0;
			map->draw.end = map->ray.height / 2 + map->screen.y / 2;
			if (map->draw.end >= map->screen.y)
				map->draw.end = map->screen.y - 1;
			draw_wall(map,i);
			i++;
		}
		return(0);
}