/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:03:13 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 15:04:17 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"
#include <assert.h>

int	set_backgroud(t_cub *map)
{
	int i;

	i = 0;
	while (i < (map->screen.x * map->screen.y) / 2)
	{
		map->screenpx[i] = map->colorsky;
		map->screenpx[(map->screen.x * map->screen.y) / 2 + i] = map->colorfloor;
		i++;
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
	int i;

	i = 0;
	while (i < map->screen.x * map->screen.y)
	{
		map->mlx.data[i] = map->screenpx[i];
		//map->mlx.data[i + (map->screen.x * map->screen.y / 2)] = map->screenpx[i + (map->screen.x * map->screen.y / 2)];
		i++;
	}
}

int main_loop(t_cub *map)
{
	move(map);
	raycasting(map);
	draw(map);
	mlx_put_image_to_window(map->mlx.ptr,map->mlx.win,map->mlx.img,0,0);
}
int set_wall(t_cub *map,int x)
{
	int y = map->draw.start;

	while (y < map->draw.end)
	{
		map->tex.y = (int)map->texpos & (map->mlx.h[map->textpx] - 1);
		map->texpos += map->textstep;
		map->screenpx[y * map->screen.x + x] = 
		map->mlx.data_text[map->textpx][(int)(map->mlx.h[map->textpx] * map->tex.y + map->tex.x)];
		y++;
	}
}

void draw_sprite(t_cub *map)
{
	t_float sprite;
	t_float transform;
	int i;
	int y;
	int d;
	double invdet;
	int spritescreenx;
	int stripe;

	i = 0;
	while (i < map->nbsprite)
	{
		sprite.x = map->sprite[i].pos.x - map->player.pos.x;
		sprite.y = map->sprite[i].pos.y - map->player.pos.y;
		invdet = 1.0 / (map->player.plane.x * map->player.dir.y - map->player.dir.x * map->player.plane.y);
		transform.x = invdet * (map->player.dir.y * sprite.x - map->player.dir.x * sprite.y);
		transform.y = invdet * (-map->player.plane.y * sprite.x + map->player.plane.x * sprite.y);
		spritescreenx = (int)((map->screen.x / 2) * (1 + transform.x / transform.y));
		map->spriteheight = abs((int)(map->screen.y / transform.y));
		map->sprite_start.y = -map->spriteheight / 2 + map->screen.y / 2;
		if (map->sprite_start.y < 0)
			map->sprite_start.y = 0;
		map->sprite_end.y = map->spriteheight / 2 + map->screen.y / 2;
		if (map->sprite_end.y >= map->screen.y)
			map->sprite_end.y = map->screen.y - 1;
		map->sprite_width = abs((int)(map->screen.y / transform.y));
		map->sprite_start.x = -map->sprite_width / 2 + spritescreenx;
		if (map->sprite_start.x < 0)
			map->sprite_start.x = 0;
		map->sprite_end.x = map->sprite_width / 2 + spritescreenx;
		if (map->sprite_end.x >= map->screen.x)
			map->sprite_end.x = map->screen.x;
		stripe = map->sprite_start.x;
		while (stripe < map->sprite_end.x)
		{
			map->tex.x = (int)((256 * (stripe - (-map->sprite_width / 2 +
			spritescreenx)) * map->mlx.w[4] / map->sprite_width) / 256);
			if (transform.y > 0 && stripe < map->screen.x &&
			transform.y < map->zbuffer[stripe])
			{
				y = map->sprite_start.y;
				while (y < map->sprite_end.y)
				{
					d = y * 256 - map->screen.y * 128 + map->spriteheight * 128;
					map->tex.y = ((d * map->mlx.h[4]) / map->spriteheight) / 256;
					map->color = map->mlx.data_text[4][map->tex.y *
						map->mlx.w[4] + map->tex.x];
					if ((map->color & 0xffffff) != 0)
						map->screenpx[y * map->screen.x + stripe] = map->color;
					// map->screenpx[y * map->screen.x + stripe] = map->mlx.data_text[4][map->tex.y * map->mlx.w[4] + map->tex.x];
					y++;
				}
			}
		stripe++;
		}
		i++;
	}

}

void sort_sprite(t_cub *map)
{
	t_sprite temp;
	int i;

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

void raycast_sprite(t_cub *map)
{
	int i;

	i = 0;
	while (i < map->nbsprite)
	{
		map->sprite[i].dist = ((map->player.pos.x - map->sprite[i].pos.x) *
		(map->player.pos.x - map->sprite[i].pos.x) + (map->player.pos.y - map->sprite[i].pos.y) *
		(map->player.pos.y - map->sprite[i].pos.y));
		i++;
	}
	sort_sprite(map);
	draw_sprite(map);
}

int		raycasting(t_cub *map)
{
		int i;
		double wallx;
		i = 0;
		set_backgroud(map);
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
			map->zbuffer[i] = map->ray.perpdist;
			i++;
		}
		raycast_sprite(map);
		return(0);
}