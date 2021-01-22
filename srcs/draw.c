/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 21:19:18 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/22 21:33:10 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_backgroud(t_cub *map)
{
	int			i;
	const	int	demiscreen = (map->screen.x * map->screen.y) / 2;

	i = 0;
	while (i < (map->screen.x * map->screen.y) / 2)
	{
		map->screenpx[i] = map->colorsky;
		map->screenpx[demiscreen + i] = map->colorfloor;
		i++;
	}
}

void	draw(t_cub *map)
{
	int			i;

	i = 0;
	while (i < map->screen.x * map->screen.y)
	{
		map->mlx.data[i] = map->screenpx[i];
		i++;
	}
}

void	set_wall(t_cub *map, int x)
{
	int			y;

	y = map->draw.start;
	while (y < map->draw.end)
	{
		map->tex.y = (int)map->texpos & (map->mlx.h[map->textpx] - 1);
		map->texpos += map->textstep;
		map->screenpx[y * map->screen.x + x] =
		map->mlx.data_text[map->textpx][(int)(map->mlx.h[map->textpx] *
		map->tex.y + map->tex.x)];
		y++;
	}
}

void	draw_sprite(t_cub *map, int st, int spritescreenx, t_float trans)
{
	int			y;
	int			d;

	while (st < map->sprite_x.end)
	{
		map->tex.x = (int)((256 * (st - (-map->spriteheight / 2 +
		spritescreenx)) * map->mlx.w[4] / map->spriteheight) / 256);
		if (trans.y > 0 && st < map->screen.x && trans.y < map->zbuffer[st])
		{
			y = map->sprite_y.start;
			while (y < map->sprite_y.end)
			{
				d = y * 256 - map->screen.y * 128 + map->spriteheight * 128;
				map->tex.y = ((d * map->mlx.h[4]) / map->spriteheight) / 256;
				if (map->tex.y <= 0)
					map->tex.y *= -1;
				map->color = map->mlx.data_text[4][map->tex.y *
					map->mlx.w[4] + map->tex.x];
				if ((map->color & 0xffffff) != 0)
					map->screenpx[y * map->screen.x + st] = map->color;
				y++;
			}
		}
		st++;
	}
}
