/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 14:49:25 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/08 14:50:59 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int check_corner(t_cub *map,int i)
{
	t_float p[5];

	p[0]= map->ray[i].wallpos[0];
	p[1]= map->ray[i].wallpos[1];
	p[2]= map->ray[i + 1].wallpos[0];
	p[3]= map->ray[i + 1].wallpos[1];

	if (p[0].x == p[2].x && p[0].y == p[2].y)
		return (1);
	if (p[0].x == p[3].x && p[0].y == p[3].y)
		return (1);
	if (p[1].x == p[2].x && p[1].y == p[2].y)
		return (1);
	if (p[1].x == p[3].x && p[1].y == p[3].y)
		return (1);
	return (0);
}

void	fill_colonne_wallheight(t_cub *map, int i)
{
	int j;
	double diff;

	j = 1;
	while(map->colonne[i - j].wallheight == 0)
		j++;
	diff = (map->colonne[i].wallheight - map->colonne[i - j].wallheight) / j;
	j--;
	while(map->colonne[i - j].wallheight == 0)
	{
		map->colonne[i - j].wallheight = map->colonne[i - j - 1].wallheight + diff;
		j--;
	}
}

void calc_colonne_wallheight(t_cub *map, int i,int j)
{
	int c;
	float diff;
	const float nbc = map->screen.x / 60;

	c = 0;
	map->colonne[0].wallheight = map->ray[i].wallheight;
	map->colonne[0].ivalue = i;
	while (i <= j)
	{
		c++;
		if (map->ray[i].pointpos.y != map->ray[i + 1].pointpos.y &&
		map->ray[i].pointpos.x != map->ray[i + 1].pointpos.x)
		{
			map->colonne[(int)(c * nbc)].wallheight = map->ray[i].wallheight;
			map->colonne[(int)(c * nbc)].ivalue = i;
			if (check_corner(map, i) == 0)
				map->colonne[(int)(c * nbc) + 1].wallheight = map->ray[i + 1].wallheight;
			fill_colonne_wallheight(map, (int)(c * nbc));
		}
		i++;
	}
	map->colonne[map->screen.x - 1].wallheight = map->ray[i - 1].wallheight;
	map->colonne[map->screen.x - 1].ivalue = i;
	fill_colonne_wallheight(map, (map->screen.x - 1));
	c = 0;
	while(c < map->screen.x)
	{
		if (map->colonne[c].ivalue != 0)
			printf("%f\t%f\n",map->ray[map->colonne[c].ivalue].pointpos.y,map->ray[map->colonne[c].ivalue].t);
		c++;
	}
}

void    calc_correct_wallheight(t_cub *map, int i,int j)
{
	float pi;
	pi = 3.14159265359;
	while(i <= j)
	{
 		map->ray[i].wallheight = (0.5/map->ray[i].walldist)*map->projectiondist;
		i++;
	}
}

int		projection(t_cub *map)
{
	float	pi;

	pi = 3.14159265359;
	map->projection_center.x = map->screen.x / 2;
	map->projection_center.y = map->screen.y / 2;
	map->projectiondist = (map->screen.x / 2) / tanf((30 * (pi / 180)));
	if (check_player_orientation(map) == 0)
		map->projection_id = set_wall_pos(15, 75);
	if (check_player_orientation(map) == 1)
		map->projection_id = set_wall_pos(195, 255);
	if (check_player_orientation(map) == 2)
		map->projection_id = set_wall_pos(285, 345);
	if (check_player_orientation(map) == 3)
		map->projection_id = set_wall_pos(105, 165);
	calc_correct_wallheight(map, map->projection_id.x,map->projection_id.y);
	calc_colonne_wallheight(map, map->projection_id.x,map->projection_id.y);
}
