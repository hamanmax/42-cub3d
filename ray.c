/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map->ray[i].c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:59:58 by mhaman            #+#    #+#             */
/*   Updated: 2020/08/09 11:20:16 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_float	set_wall_pos(float x, float y)
{
	t_float	wp;

	wp.x = (int)x;
	wp.y = (int)y;
	return (wp);
}

t_float	set_ray_pos(float x, float y)
{
	t_float	wp;

	wp.x = x;
	wp.y = y;
	return (wp);
}

int calc_del(t_ray ray)
{
	int t;

	t = 0;
	if (ray.oppose > 0)
		t = ceilf(ray.oppose) * -1;
	if (ray.oppose < 0)
		t = floorf(ray.oppose) * -1;
	return (t);
}

float	calc_t( t_cub *map, int i)
{
	t_float p[5];

	p[1] = map->ray[i].wallpos[0];
	p[2] = map->ray[i].wallpos[1];
	p[3] = map->player_pos;
	p[4] = map->ray[i].raypos[1];
	map->ray[i].t = ((p[1].y - p[3].y)*(p[3].x - p[4].x) - (p[1].x - p[3].x)*(p[3].y - p[4].y)) / ((p[1].y - p[2].y)*(p[3].x - p[4].x) - (p[1].x - p[2].x)*(p[3].y - p[4].y));
	return (map->ray[i].t);
}

int		check_player_orientation(t_cub *map)
{
	if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'N')
		return (0);
	else if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'S')
		return (1);
	else if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'W')
		return (2);
	else if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'E')
		return (3);
	return (-1);
}

float	check_wall_north_up(t_cub *map,  int i)
{
	map->ray[i].wallpos[0] = set_wall_pos(map->ray[i].raypos[0].x, map->ray[i].raypos[0].y);
	map->ray[i].wallpos[1] = set_wall_pos(map->ray[i].raypos[0].x, map->ray[i].raypos[0].y + 1);
	if (calc_t (map, i) > 0 && (map->ray[i].t <= 1))
		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

float	check_wall_north_side(t_cub *map,  int i)
{
	map->ray[i].wallpos[0].x = (int)map->ray[i].raypos[0].x;
	map->ray[i].wallpos[0].y = (int)map->ray[i].raypos[0].y + ceilf(map->ray[i].oppose);
	map->ray[i].wallpos[1].x = (int)map->ray[i].raypos[0].x + 1;
	map->ray[i].wallpos[1].y = (int)map->ray[i].raypos[0].y + ceilf(map->ray[i].oppose);
	if (calc_t (map, i) > 0 && (map->ray[i].t <= 1))

		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

float	check_wall_east_up(t_cub *map,  int i)
{
	map->ray[i].wallpos[0] = set_wall_pos(map->ray[i].raypos[0].x + ceilf(map->ray[i].oppose), map->ray[i].raypos[0].y);
	map->ray[i].wallpos[1] = set_wall_pos(map->ray[i].raypos[0].x + ceilf(map->ray[i].oppose), map->ray[i].raypos[0].y + 1);
	if (calc_t (map, i) > 0 && (map->ray[i].t <= 1))
		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

float	check_wall_east_side(t_cub *map,  int i)
{
	map->ray[i].wallpos[0].x = (int)map->ray[i].raypos[0].x;
	map->ray[i].wallpos[0].y = (int)map->ray[i].raypos[0].y + 1;
	map->ray[i].wallpos[1].x = (int)map->ray[i].raypos[0].x + 1;
	map->ray[i].wallpos[1].y = (int)map->ray[i].raypos[0].y + 1;
	if (calc_t (map, i) > 0 && (map->ray[i].t <= 1))
		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

float	check_wall_south_up(t_cub *map,  int i)
{
	map->ray[i].wallpos[0] = set_wall_pos(map->ray[i].raypos[0].x + 1, map->ray[i].raypos[0].y);
	map->ray[i].wallpos[1] = set_wall_pos(map->ray[i].raypos[0].x + 1, map->ray[i].raypos[0].y + 1);
	if (calc_t (map, i) > 0 && (map->ray[i].t <= 1))
		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

float	check_wall_south_side(t_cub *map,  int i)
{
	map->ray[i].wallpos[0].x = (int)map->ray[i].raypos[0].x;
	map->ray[i].wallpos[0].y = (int)map->ray[i].raypos[0].y + ceilf(map->ray[i].oppose);
	map->ray[i].wallpos[1].x = (int)map->ray[i].raypos[0].x + 1;
	map->ray[i].wallpos[1].y = (int)map->ray[i].raypos[0].y + ceilf(map->ray[i].oppose);
	if (calc_t (map, i) > 0 && (map->ray[i].t <= 1))
		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

float	check_wall_west_up(t_cub *map,  int i)
{
	//printf("%f\n",ceilf(map->ray[i].oppose));
	map->ray[i].wallpos[0] = set_wall_pos(map->ray[i].raypos[0].x + ceilf(map->ray[i].oppose), map->ray[i].raypos[0].y);
	map->ray[i].wallpos[1] = set_wall_pos(map->ray[i].raypos[0].x + ceilf(map->ray[i].oppose), map->ray[i].raypos[0].y + 1);
	//if (i == 357)
	//printf("%f\t%f\n",map->ray[i].wallpos[0].x,map->ray[i].wallpos[0].y);
	if (calc_t (map, i) > 0 && (map->ray[i].t <= 1))
		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

float	check_wall_west_side(t_cub *map,  int i)
{
	map->ray[i].wallpos[0].x = (int)map->ray[i].raypos[0].x;
	map->ray[i].wallpos[0].y = (int)map->ray[i].raypos[0].y;
	map->ray[i].wallpos[1].x = (int)map->ray[i].raypos[0].x + 1;
	map->ray[i].wallpos[1].y = (int)map->ray[i].raypos[0].y;
	if (calc_t (map, i) > 0 && (map->ray[i].t <= 1))
		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

void	check_wall_north(t_cub *map,  int i)
{
	while (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[0].y] != '1')
	{
		map->ray[i].raypos[1] = set_ray_pos(map->ray[i].raypos[0].x - 1, map->ray[i].raypos[0].y + map->ray[i].oppose);
		if ((int)map->ray[i].raypos[1].y != (int)map->ray[i].raypos[0].y)
		{
			if (map->map[(int)map->ray[i].raypos[1].x][(int)map->ray[i].raypos[0].y] == '1')
				if (check_wall_north_up(map, i) != 0)
					break ;
			if (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[1].y] == '1')
			{
				if (check_wall_north_side(map, i) != 0)
					break ;
			}
		}
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x, map->ray[i].raypos[1].y);
	}
	if (map->ray[i].t == 0)
	{
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x + 1, map->ray[i].raypos[1].y);
		check_wall_north_up(map, i);
		if (map->ray[i].t == 0 && map->ray[i].angle != 45)
		{
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x, (map->ray[i].raypos[1].y + calc_del(map->ray[i])));
			check_wall_north_side(map, i);
		}
	}
}

void	check_wall_east(t_cub *map,  int i)
{
	while (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[0].y] != '1')
	{
		map->ray[i].raypos[1] = set_ray_pos(map->ray[i].raypos[0].x + map->ray[i].oppose, map->ray[i].raypos[0].y + 1);
		if ((int)map->ray[i].raypos[1].x != (int)map->ray[i].raypos[0].x)
		{
			if (map->map[(int)map->ray[i].raypos[1].x][(int)map->ray[i].raypos[0].y] == '1')
				if (check_wall_east_up(map, i) != 0)
					break ;
			if (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[1].y] == '1')
			{
				if (check_wall_east_side(map, i) != 0)
					break ;
			}
		}
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x, map->ray[i].raypos[1].y);
	}
	if (map->ray[i].t == 0)
	{
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x + calc_del(map->ray[i]), map->ray[i].raypos[1].y);
		check_wall_east_up(map, i);
		if (map->ray[i].t == 0 && map->ray[i].angle != 45)
		{
			map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x , map->ray[i].raypos[1].y - 1);
			check_wall_east_side(map, i);
		}
	}
}

void	check_wall_south(t_cub *map,  int i)
{
	while (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[0].y] != '1')
	{
		map->ray[i].raypos[1] = set_ray_pos(map->ray[i].raypos[0].x + 1, map->ray[i].raypos[0].y + map->ray[i].oppose);
		if ((int)map->ray[i].raypos[1].y != (int)map->ray[i].raypos[0].y) /* S'il rentre la dedans c'est qu'il est en +1 +1*/
		{
			if (map->map[(int)map->ray[i].raypos[1].x][(int)map->ray[i].raypos[0].y] == '1') /* si la case au dessus est = a un 1 */
				if (check_wall_south_up(map, i) != 0)
					break ;
			if (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[1].y] == '1') /* si la case du cote est = a un 1 */
			{
				if (check_wall_south_side(map, i) != 0)
					break ;
			}
		}
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x, map->ray[i].raypos[1].y);
	}
	if (map->ray[i].t == 0)
	{
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x - 1, map->ray[i].raypos[1].y);
		check_wall_south_up(map, i);
		if (map->ray[i].t == 0 && map->ray[i].angle != 45)
		{
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x, (map->ray[i].raypos[1].y));
			check_wall_south_side(map, i);
		}
	}
}

void	check_wall_west(t_cub *map,  int i)
{
	while (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[0].y] != '1')
	{
		map->ray[i].raypos[1] = set_ray_pos(map->ray[i].raypos[0].x + map->ray[i].oppose, map->ray[i].raypos[0].y - 1);
		if ((int)map->ray[i].raypos[1].x != (int)map->ray[i].raypos[0].x) /* S'il rentre la dedans c'est qu'il est en +1 +1*/
		{
			if (map->map[(int)map->ray[i].raypos[1].x][(int)map->ray[i].raypos[0].y] == '1') /* si la case au dessus est = a un 1 */
				if (check_wall_west_up(map, i) != 0)
					break ;
			if (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[1].y] == '1')
				if (check_wall_west_side(map, i) != 0)
					break ;
		}
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x, map->ray[i].raypos[1].y);
	}
	if (map->ray[i].t == 0)
	{
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x + calc_del(map->ray[i]), map->ray[i].raypos[1].y);
		check_wall_west_up(map, i);
		if (map->ray[i].t == 0 && map->ray[i].angle != 45)
		{
			map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x, map->ray[i].raypos[1].y + 1);
			check_wall_west_side(map, i);
		}
	}
}

int		check_wall_dist(t_cub *map,  int i)
{
	t_float p[5];

	p[1] = map->ray[i].wallpos[0];
	p[2] = map->ray[i].wallpos[1];
	p[3] = map->player_pos;
	map->ray[i].pointpos.x = p[1].x + (map->ray[i].t * (p[2].x - p[1].x));
	map->ray[i].pointpos.y = p[1].y + (map->ray[i].t * (p[2].y - p[1].y));
	p[4] = map->ray[i].pointpos;
	map->ray[i].walldist = sqrt(((p[4].x - p[3].x) * (p[4].x - p[3].x) + ((p[4].y - p[3].y) * (p[4].y - p[3].y))));
}

int		check_wall_pos(t_cub *map,  int i)
{
	map->ray[i].raypos[0] = map->player_pos;
	map->ray[i].raypos[1] = map->ray[i].raypos[0];
	if (i >= 0 && i < 90)
		check_wall_north(map, i);
	if (i >= 90 && i < 180)
		check_wall_east(map, i);
	if (i >= 180 && i < 270)
		check_wall_south(map, i);
	if (i >= 270 && i < 360)
		check_wall_west(map, i);
	return (0);
}

void		draw_base_ray(t_cub *map)
{
	int		i;
	int		angle;
	float	pi;

	pi = 3.14159265359;
	angle = 45;
	i = 0;
	while (i < 360)
	{
		map->ray[i].id = i;
		map->ray[i].angle = angle;
		map->ray[i].oppose = tan(((angle) * (pi / 180)));
		if ((i >= 0 && i < 45) || (i >= 90 && i < 135) || (i >= 225 && i < 270)
		|| (i >= 315 && i < 360))
			map->ray[i].oppose = -1 * tan(((angle) * (pi / 180)));
		if ((i >= 45 && i < 90) || (i >= 135 && i < 180)
		|| (i >= 225 && i < 270) || (i >= 315 && i < 360))
			angle += 2;
		angle--;
		check_wall_pos(map, i);
		check_wall_dist(map, i);
		i++;
	}
}

void	draw_ray(t_cub *map,  int i, int j)
{
	while (i < j)
	{
		check_wall_pos(map, i);
		check_wall_dist(map, i);
	}
}

int		raytracing(t_cub *map)
{
	int		i;

	i = 0;
	map->player_pos.x = map->player_pos_base.x + 0.5;
	map->player_pos.y = map->player_pos_base.y + 0.5;
	draw_base_ray(map);
	return (0);
}
