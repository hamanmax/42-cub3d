/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:39:04 by mhaman            #+#    #+#             */
/*   Updated: 2020/10/20 10:51:46 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "timecheck.h"
#include "cub3d.h"

void print_backround(t_cub *map)
{
	int i;
	int j;

	i = 0;
	while (i < ((map->screen.x) * (map->screen.y)))
	{
		map->mlx.data[i] = map->colorsky;
		if (i >= (map->screen.x * map->screen.y) / 2)
			map->mlx.data[i] = map->colorfloor;
		i++;
	}
}

void print_front(t_cub *map)
{
	t_ray r;
	const t_int s = map->screen;
	int i;
	int j;
	double k;
	i = 0;
	while (i < s.x)
	{
		j = 0;
		r = map->ray[i];
		k = 0;
		while (j <= r.wheight / 2)
		{
			map->mlx.data[(s.y / 2 + j) * s.x + i]= r.data[(r.w / 2 + (int)k) * r.w + r.textpos];
			map->mlx.data[(s.y / 2 - j) * s.x + i] = r.data[(r.w / 2 - (int)k) * r.w + r.textpos];
			j++;
			k += r.diffangle;
		}
		i++;
	}
	i = 0;
	while (i < s.x)
	{
	j = 0;
		if (map->spr[0].ray[i].wheight != 0)
		{
			while(j <= map->spr[0].ray[i].wheight / 2)
			{
				map->mlx.data[(s.y / 2 + j) * s.x + i]= 2520205;
				map->mlx.data[(s.y / 2 - j) * s.x + i] = 2555151;
				j++;
			}
		}
		i++;
	}
}

void set_player_dir(t_cub *map, double angle)
{
	map->player.dir.x = -1 * cos(angle*RAD) * MVS;
	map->player.dir.y = sin(angle*RAD) * MVS;
}

void  move_forward(t_cub *map)
{
	if (map->kp == 119)
	{
		set_player_dir(map,map->player.orientation);
		map->player.pos.x += map->player.dir.x;
		map->player.pos.y += map->player.dir.y;
		if (map->map[(int)map->player.pos.x][(int)map->player.pos.y] == '1')
		{
		map->player.pos.x -= map->player.dir.x;
		map->player.pos.y -= map->player.dir.y;
		}
	}
	if (map->kp == 115)
	{
		set_player_dir(map,map->player.orientation);
		map->player.pos.x -= map->player.dir.x;
		map->player.pos.y -= map->player.dir.y;
		if (map->map[(int)map->player.pos.x][(int)map->player.pos.y] == '1')
		{
		map->player.pos.x += map->player.dir.x;
		map->player.pos.y += map->player.dir.y;
		}
	}
	if (map->kp == 97)
	{
		set_player_dir(map,map->player.orientation - 90);
		map->player.pos.x += map->player.dir.x;
		map->player.pos.y += map->player.dir.y;
		if (map->map[(int)map->player.pos.x][(int)map->player.pos.y] == '1')
		{
		map->player.pos.x -= map->player.dir.x + 0.005;
		map->player.pos.y -= map->player.dir.y + 0.005;
		}
	}
	if (map->kp == 100)
	{
		set_player_dir(map,map->player.orientation - 90);
		map->player.pos.x -= map->player.dir.x;
		map->player.pos.y -= map->player.dir.y;
		if (map->map[(int)map->player.pos.x][(int)map->player.pos.y] == '1')
		{
		map->player.pos.x += map->player.dir.x *2;
		map->player.pos.y += map->player.dir.y *2;
		}
	}
	if (map->kp == 101)
	{
		map->player.orientation += 1;
		if (map->player.orientation >= 360)
		map->player.orientation = 0;
	}
	if (map->kp == 113)
	{
		map->player.orientation -= 1;
		if (map->player.orientation <= 0)
		map->player.orientation = 360;
	}
}

int deal_key(int key, void *params)
{
	t_cub *map;

	map = params;
	dprintf(1,"%d\n", key);
	if (key == 119)
	{
		map->kp = key;
		return (1);
	}
	if (key == 115)
	{
		map->kp = key;
		return (1);
	}
	if (key == 100)
	{
		map->kp = 100;
	}
	if (key == 97)
	{
		map->kp = 97;
	}
	if (key == 101)
	{
		map->kp = 101;
	}
	if (key == 113)
	{
		map->kp = 113;
	}
	if (key == 32)
	{
		map->kp = 0;
	}
	if (key == 114)
	{
		map->kp = key;
		return (1);
	}
	return (0);
}

int main_loop(t_cub *map)
{
	//map->kp++;
	move_forward(map);
	ft_bzero(map->ray,sizeof(t_ray)* map->screen.x - 1);
	ft_bzero(map->spr[0].ray,sizeof(t_ray)* map->screen.x - 1);
	draw_base_ray(map);
	get_wall_lenght(map);
	print_backround(map);
	print_front(map);
	mlx_put_image_to_window(map->mlx.ptr, map->mlx.win, map->mlx.img, 0, 0);
	if (map->kp == 114)
		exit(1);
}

void create_new_black_window(t_cub *map)
{
	int bpp;
	int line_size;
	int endien;

	map->mlx.win = mlx_new_window(map->mlx.ptr, map->screen.x, map->screen.y, "Cub3d");
	map->mlx.img = mlx_new_image(map->mlx.ptr, map->screen.x, map->screen.y);
	map->mlx.data = (int *)mlx_get_data_addr(map->mlx.img, &bpp, &line_size, &endien);
	mlx_loop_hook(map->mlx.ptr, &main_loop,map);
	mlx_key_hook(map->mlx.win, deal_key, map);
}
