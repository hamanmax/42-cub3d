/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:03:13 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/19 20:14:21 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <assert.h>

int	set_backgroud(t_cub *map)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	while (x < map->screen.x)
	{
		while (y < map->screen.y / 2)
		{
			map->screenpx[x][y] = map->colorsky;
			map->screenpx[x][y + map->screen.y / 2] = map->colorfloor;
			y++;
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

void draw(t_cub *map)
{
	int x;
	int y;
	int i;

	i = 0;
	x = 0;
	y = 0;
	while (y < map->screen.y)
	{
		while (x < map->screen.x)
		{
			map->mlx.data[i] = map->screenpx[x][y];
			x++;
			i++;
		}
		y++;
		x = 0;
	}
}
int main_loop(t_cub *map)
{
	raycasting(map);
	draw(map);
	mlx_put_image_to_window(map->mlx.ptr,map->mlx.win,map->mlx.img,0,0);
	if (map->kp == 119)
	{
		map->player.pos.x -= 0.3;
	}
	if (map->kp == 115)
	{
		map->player.pos.x += 0.3;
	}
	if (map->kp == 97)
	{
		map->player.pos.y -= 0.3;
	}
	if (map->kp == 100)
	{
		map->player.pos.y += 0.3;
	}
	printf("%d\n",map->kp);
}
int set_wall(t_cub *map,int x)
{
	int y = map->draw.start;
	while (y < map->draw.end)
	{
		map->tex.y = (int)map->texpos & (map->mlx.h[map->textpx] - 1);
		map->texpos += map->textstep;
		map->screenpx[x][y] = 
		map->mlx.data_text[map->textpx][(int)(map->mlx.h[map->textpx] * map->tex.y + map->tex.x)];
		y++;
	}
}

int		raycasting(t_cub *map)
{
		int i;
		int j = 0;
		double wallx;
		set_backgroud(map);
		i = 0;
		while (i < map->screen.x)
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
			if (map->side)
			{
				if (map->ray.dir.y < 0)
				{
					map->textpx = 2;
				}
				else
				{
					map->textpx = 3;
				}
			}
			else
			{
				if (map->ray.dir.x < 0)
				{
					map->textpx = 0;
				}
				else
				{
					map->textpx = 1;
				}
			}
			if (map->side == 0)
				wallx = map->player.pos.y + map->ray.perpdist * map->ray.dir.y;
			else
				wallx = map->player.pos.x + map->ray.perpdist * map->ray.dir.x;
			wallx -= (int)wallx;
			map->tex.x = (int)(wallx * (double)(map->mlx.w[map->textpx]));
			if (map->side == 0 && map->ray.dir.x > 0)
				map->tex.x = map->mlx.h[map->textpx] - map->tex.x - 1;
			if (map->side == 1 && map->ray.dir.y < 0)
				map->tex.x = map->mlx.h[map->textpx] - map->tex.x - 1;
			map->textstep = 1.0 * map->mlx.w[map->textpx] / map->ray.height;
			map->texpos = (map->draw.start - map->screen.y / 2 + map->ray.height / 2) * map->textstep;
			set_wall(map, i);
			i++;
		}
		return(0);
}