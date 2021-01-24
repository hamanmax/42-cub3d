/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:04:06 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/23 09:54:07 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_ws(t_cub *map)
{
	t_player		p;

	p = map->pla;
	if (map->move.forward)
	{
		if (map->map[(int)(p.pos.x + p.dir.x * MVS)][(int)(p.pos.y)] != '1')
			p.pos.x += p.dir.x * MVS;
		if (map->map[(int)(p.pos.x)][(int)(p.pos.y + p.dir.y * MVS)] != '1')
			p.pos.y += p.dir.y * MVS;
	}
	if (map->move.backward)
	{
		if (map->map[(int)(p.pos.x - p.dir.x * MVS)][(int)(p.pos.y)] != '1')
			p.pos.x -= p.dir.x * MVS;
		if (map->map[(int)(p.pos.x)][(int)(p.pos.y - p.dir.y * MVS)] != '1')
			p.pos.y -= p.dir.y * MVS;
	}
	map->pla = p;
}

void	move_ad(t_cub *map)
{
	t_player		p;

	p = map->pla;
	if (map->move.rightside)
	{
		p.pos.x += p.plane.x * MVS;
		if (map->map[(int)p.pos.x][(int)p.pos.y] == '1')
			p.pos.x -= p.plane.x * MVS;
		p.pos.y += p.plane.y * MVS;
		if (map->map[(int)p.pos.x][(int)p.pos.y] == '1')
			p.pos.y -= p.plane.y * MVS;
	}
	if (map->move.leftside)
	{
		p.pos.x -= p.plane.x * MVS;
		if (map->map[(int)p.pos.x][(int)p.pos.y] == '1')
			p.pos.x += p.plane.x * MVS;
		p.pos.y -= p.plane.y * MVS;
		if (map->map[(int)p.pos.x][(int)p.pos.y] == '1')
			p.pos.y += p.plane.y * MVS;
	}
	map->pla = p;
}

void	rotation_qe(t_cub *map)
{
	t_player		p;
	const double	olddirx = map->pla.dir.x;
	const double	oldplanex = map->pla.plane.x;

	p = map->pla;
	if (map->move.rightrot)
	{
		p.dir.x = p.dir.x * cos(-RTS) - p.dir.y * sin(-RTS);
		p.dir.y = olddirx * sin(-RTS) + p.dir.y * cos(-RTS);
		p.plane.x = p.plane.x * cos(-RTS) - p.plane.y * sin(-RTS);
		p.plane.y = oldplanex * sin(-RTS) + p.plane.y * cos(-RTS);
	}
	if (map->move.leftrot)
	{
		p.dir.x = p.dir.x * cos(RTS) - p.dir.y * sin(RTS);
		p.dir.y = olddirx * sin(RTS) + p.dir.y * cos(RTS);
		p.plane.x = p.plane.x * cos(-RTS) - p.plane.y * sin(RTS);
		p.plane.y = oldplanex * sin(RTS) + p.plane.y * cos(RTS);
	}
	map->pla = p;
}

int		closecub(t_cub *map, int code)
{
	mlx_destroy_image(map->mlx.ptr, map->mlx.img);
	if (code != 1)
		mlx_destroy_window(map->mlx.ptr, map->mlx.win);
	free_cub(map);
	exit(1);
}

void	move(t_cub *map)
{
	if (map->move.close)
		closecub(map, 0);
	move_ws(map);
	move_ad(map);
	rotation_qe(map);
}
