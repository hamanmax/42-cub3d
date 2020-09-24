/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:03:13 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/24 15:56:30 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <assert.h>

double	set_player_orientation(t_cub *map, double i)
{
	if (i != 0)
		return (i);
	if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'N')
		return (0);
	if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'E')
		return (90);
	if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'S')
		return (180);
	if (map->map[map->player_pos_base.x][map->player_pos_base.y] == 'W')
		return (270);
	return (0);
}

t_float	set_wall_pos(float x, float y)
{
	t_float		wp;

	wp.x = (int)x;
	wp.y = (int)y;
	return (wp);
}

t_float	set_ray_pos(float x, float y)
{
	t_float		wp;

	wp.x = x;
	wp.y = y;
	return (wp);
}

int		calc_del(t_ray ray)
{
	int			t;

	t = 0;
	if (ray.oppose > 0)
		t = ceilf(ray.oppose) * -1;
	if (ray.oppose < 0)
		t = floorf(ray.oppose) * -1;
	return (t);
}

float	calc_t(t_cub *map, int i)
{
	t_float		p[5];

	p[1] = map->ray[i].wallpos[0];
	p[2] = map->ray[i].wallpos[1];
	p[3] = map->player_pos;
	p[4] = map->ray[i].raypos[1];
	map->ray[i].t = ((p[1].y - p[3].y) *
	(p[3].x - p[4].x) - (p[1].x - p[3].x) *
	(p[3].y - p[4].y)) / ((p[1].y - p[2].y) *
	(p[3].x - p[4].x) - (p[1].x - p[2].x) *
	(p[3].y - p[4].y));
	return (map->ray[i].t);
}

float	set_wall_north_south(t_cub *map,  int i, char c)
{
	const t_float *rp = map->ray[i].raypos;
	const double op = map->ray[i].oppose;
	
	if (c == 'N')
	{
		map->ray[i].wallpos[0] = set_wall_pos(rp[0].x, rp[0].y);
		map->ray[i].wallpos[1] = set_wall_pos(rp[0].x, rp[0].y + 1);
		if (calc_t(map, i) > 0 && (map->ray[i].t <= 1))
			return (map->ray[i].t);
		return ((map->ray[i].t = 0));
	}
	if (c == 'S')
	{
		map->ray[i].wallpos[0] = set_wall_pos(rp[0].x + 1, rp[0].y);
		map->ray[i].wallpos[1] = set_wall_pos(rp[0].x + 1, rp[0].y + 1);
		if (calc_t(map, i) > 0 && (map->ray[i].t <= 1))
			return (map->ray[i].t);
		return ((map->ray[i].t = 0));
	}
	map->ray[i].wallpos[0] = set_wall_pos(rp[0].x, rp[0].y + ceilf(op));
	map->ray[i].wallpos[1] = set_wall_pos(rp[0].x + 1, rp[0].y + ceilf(op));
	if (calc_t(map, i) > 0 && (map->ray[i].t <= 1))
		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

float	check_wall_north_south_side(t_cub *map,  int i)
{
	map->ray[i].wallpos[0].x = (int)map->ray[i].raypos[0].x;
	map->ray[i].wallpos[0].y = (int)map->ray[i].raypos[0].y + ceilf(map->ray[i].oppose);
	map->ray[i].wallpos[1].x = (int)map->ray[i].raypos[0].x + 1;
	map->ray[i].wallpos[1].y = (int)map->ray[i].raypos[0].y + ceilf(map->ray[i].oppose);
	if (calc_t(map, i) > 0 && (map->ray[i].t <= 1))
		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

float	check_wall_east_west_up(t_cub *map,  int i)
{
	map->ray[i].wallpos[0] = set_wall_pos(map->ray[i].raypos[0].x +
	ceilf(map->ray[i].oppose), map->ray[i].raypos[0].y);
	map->ray[i].wallpos[1] = set_wall_pos(map->ray[i].raypos[0].x +
	ceilf(map->ray[i].oppose), map->ray[i].raypos[0].y + 1);
	if (calc_t(map, i) > 0 && (map->ray[i].t <= 1))
		return (map->ray[i].t);
	return ((map->ray[i].t = 0));
}

float	check_wall_east_west_side(t_cub *map,  int i,char c)
{
	if (c == 'W')
	{
		map->ray[i].wallpos[0].x = (int)map->ray[i].raypos[0].x;
		map->ray[i].wallpos[0].y = (int)map->ray[i].raypos[0].y;
		map->ray[i].wallpos[1].x = (int)map->ray[i].raypos[0].x + 1;
		map->ray[i].wallpos[1].y = (int)map->ray[i].raypos[0].y;
		if (calc_t(map, i) > 0 && (map->ray[i].t <= 1))
			return (map->ray[i].t);
		return ((map->ray[i].t = 0));
	}
	if (c == 'E')
	{
		map->ray[i].wallpos[0].x = (int)map->ray[i].raypos[0].x;
		map->ray[i].wallpos[0].y = (int)map->ray[i].raypos[0].y + 1;
		map->ray[i].wallpos[1].x = (int)map->ray[i].raypos[0].x + 1;
		map->ray[i].wallpos[1].y = (int)map->ray[i].raypos[0].y + 1;
		if (calc_t(map, i) > 0 && (map->ray[i].t <= 1))
			return (map->ray[i].t);
		return ((map->ray[i].t = 0));
	}
	return (0);
}

t_ray	check_wall_north_south(t_ray r,t_cub *map, int j,char c)
{
	while (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[0].y] != '1')
	{
		map->ray[i].raypos[1] = set_ray_pos(map->ray[i].raypos[0].x + j, map->ray[i].raypos[0].y + map->ray[i].oppose);
		if ((int)map->ray[i].raypos[1].y != (int)map->ray[i].raypos[0].y)
		{
			if (map->map[(int)map->ray[i].raypos[1].x][(int)map->ray[i].raypos[0].y] == '1')
				if (set_wall_north_south(map, i, c) != 0)
					break ;
			if (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[1].y] == '1')
				if (set_wall_north_south(map, i, 0) != 0)
					break ;
		}
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x, map->ray[i].raypos[1].y);
	}
	if (map->ray[i].t == 0)
	{
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x - j, map->ray[i].raypos[1].y);
		set_wall_north_south(map, i, c);
		if (map->ray[i].t == 0 && map->ray[i].angle != 45)
		{
			map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x, (map->ray[i].raypos[1].y + calc_del(map->ray[i])));
			set_wall_north_south(map, i,0);
		}
	}
	return(r);
}

t_ray	check_wall_east_west(t_ray r,t_cub *map int j,char c)
{
	while (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[0].y] != '1')
	{
		map->ray[i].raypos[1] = set_ray_pos(map->ray[i].raypos[0].x + map->ray[i].oppose, map->ray[i].raypos[0].y + j);
		if ((int)map->ray[i].raypos[1].x != (int)map->ray[i].raypos[0].x)
		{
			if (map->map[(int)map->ray[i].raypos[1].x][(int)map->ray[i].raypos[0].y] == '1')
				if (check_wall_east_west_up(map, i) != 0)
					break ;
			if (map->map[(int)map->ray[i].raypos[0].x][(int)map->ray[i].raypos[1].y] == '1')
				if (check_wall_east_west_side(map, i,c) != 0)
					break ;
		}
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x, map->ray[i].raypos[1].y);
	}
	if (map->ray[i].t == 0)
	{
		map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x + calc_del(map->ray[i]), map->ray[i].raypos[1].y);
		check_wall_east_west_up(map, i);
		if (map->ray[i].t == 0 && map->ray[i].angle != 45)
		{
			map->ray[i].raypos[0] = set_ray_pos(map->ray[i].raypos[1].x ,map->ray[i].raypos[1].y - j);
			check_wall_east_west_side(map, i,c);
		}
	}
}

int		check_wall_dist(t_cub *map,  int i)
{
	t_float		p[5];

	p[1] = map->ray[i].wallpos[0];
	p[2] = map->ray[i].wallpos[1];
	p[3] = map->player_pos;
	map->ray[i].pointpos.x = p[1].x + (map->ray[i].t * (p[2].x - p[1].x));
	map->ray[i].pointpos.y = p[1].y + (map->ray[i].t * (p[2].y - p[1].y));
	p[4] = map->ray[i].pointpos;
	map->ray[i].walldist = sqrt(((p[4].x - p[3].x) * (p[4].x - p[3].x) + 
	((p[4].y - p[3].y) * (p[4].y - p[3].y))));
	map->ray[i].wheight = (0.5 / map->ray[i].walldist) * map->projectiondist;
	map->ray[i].color = ft_calloc((int)map->ray[i].wheight,sizeof(int*));
}

int		check_wall_pos(t_cub *map, int i)
{
	const double	angle = map->ray[i].angle;
	const			t_ray ray = map->ray[i];

	map->ray[i].raypos[0] = map->player_pos;
	map->ray[i].raypos[1] = map->ray[i].raypos[0];
	if (angle >= 0 && angle < 45 || angle >= 315 && angle < 360)
		map->ray[i] = check_wall_north_south(ray,map, -1, 'N');
	if (angle >= 45 && angle < 135)
		map->ray[i] = check_wall_east_west(ray,map, 1, 'E');
	if (angle >= 135 && angle < 225)
		map->ray[i] = check_wall_north_south(ray,map, 1, 'S');
	if (angle >= 225 && angle < 315)
		map->ray[i] = check_wall_east_west(ray,map, -1, 'W');
	return (0);
}

void	draw_raytab(t_cub *map)
{
	int			i;
	double		k;

	i = 0;
	k = 0;
	while ((k += map->diffangle) < 360)
		i++;
	map->tabsize = i;
	map->raytab = malloc(sizeof(t_raytab) * (i + 1));
	while (i > 0 && (k -= map->diffangle) >= 0)
	{
		map->raytab[i].angle = k;
		i--;
	}
	map->raytab[0].angle = 0;
	i = 0;
	k = 0;
	while (i < map->tabsize - 1 && map->raytab[i + 1].angle > 0)
	{
		if (map->raytab[i].angle >= 45 && map->raytab[i - 1].angle < 45 ||
		map->raytab[i].angle >= 135 && map->raytab[i - 1].angle < 135 ||
		map->raytab[i].angle >= 225 && map->raytab[i - 1].angle < 225 ||
		map->raytab[i].angle >= 315 && map->raytab[i - 1].angle < 315)
			k += 2;
		map->raytab[i].oppose = tan((map->raytab[i].angle - (k*45)) * (PI / 180));
		if (map->raytab[i].angle > 135 && map->raytab[i].angle < 315)
			map->raytab[i].oppose *= -1;
		i++;
	}
}

void	draw_base_ray(t_cub *map)
{
	int			i;
	int			start;

	i = 1;
	while (i < map->tabsize && map->raytab[i].angle <= map->player_orientation)
		i++;
	if (map->screen.x % 2 != 0 && map->raytab[i - 1].angle != map->player_orientation)
		map->player_orientation = set_player_orientation(map, map->raytab[i].angle + map->diffangle);

	start = i - (map->screen.x / 2) - 1;
	if (start < 0)
		start += map->tabsize;
	i = 0;
	while (i < map->screen.x)
	{
		map->ray[i].angle = map->raytab[start].angle;
		map->ray[i].oppose = map->raytab[start].oppose;
		check_wall_pos(map, i);
		check_wall_dist(map, i);
		start++;
		if (start == map->tabsize)
			start = 0;
		i++;
	}
}

void	draw_ray(t_cub *map, int i, int j)
{
	while (i < j)
	{
		check_wall_pos(map, i);
		check_wall_dist(map, i);
	}
}

int		raytracing(t_cub *map)
{
	map->player_pos.x = map->player_pos_base.x + 0.5;
	map->player_pos.y = map->player_pos_base.y + 0.5;
	map->projectiondist = (map->screen.x / 2) / tanf((30 * (PI / 180)));
	map->diffangle = (FOV / (double)map->screen.x);
	map->player_orientation = set_player_orientation(map, 0);
	draw_raytab(map);
	draw_base_ray(map);
	return (0);
}
