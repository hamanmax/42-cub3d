/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:39:04 by mhaman            #+#    #+#             */
/*   Updated: 2020/09/24 12:13:56 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"

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
	int i;
	int j;
	int k;
	int l;

	l = 0;
	i = 0;
	j = (map->screen.y - (int)map->ray[i].wheight) / 2;
	if (j < 0)
		j = 0;
	k = j + (int)map->ray[i].wheight;
	if (k > map->screen.y)
		k = map->screen.y - 1;
	while (i < map->screen.x)
	{
		while (l <= (int)map->ray[i].wheight && j <= k + 1)
		{
			map->mlx.data[j * map->screen.x + i] = map->ray[i].color[l];
			if ((int)map->ray[i].wheight == 218)
			dprintf(1,"%d\t%d\t%d\n",map->ray[i].color[l],l,(int)map->ray[i].wheight);
			l++;
			j++;
		}
		l = 0;
		i++;
		j = (map->screen.y - (int)map->ray[i].wheight) / 2;
		if (j < 0)
			j = 0;
		k = j + (int)map->ray[i].wheight;
		if (k > map->screen.y)
			k = map->screen.y - 1;
	}
}

void move_forward(t_cub *map)
{

	map->player_pos.x += 0.3;
	//map->mlx.data = (int *)mlx_get_data_addr(map->mlx.img2,bpp,&size_line,&endian);
	print_backround(map);
	print_front(map);
	mlx_destroy_image(map->mlx.ptr, map->mlx.img);
	//mlx_put_image_to_window(map->mlx.ptr,map->mlx.win,map->mlx.img2,0,0);
}

int deal_key(int key, void *params)
{
	t_cub *map;

	map = params;
	printf("%d\n", key);
	if (key == 119)
	{
		mlx_destroy_image(map->mlx.ptr, map->mlx.img);
		//move_forward(map);
		return (1);
	}
	return (0);
}

void create_new_black_window(t_cub *map)
{
	
	map->mlx.win = mlx_new_window(map->mlx.ptr, map->screen.x, map->screen.y, "Test N1");
	map->mlx.img = mlx_new_image(map->mlx.ptr, map->screen.x, map->screen.y);
	map->mlx.data = (int *)mlx_get_data_addr(map->mlx.img, &map->mlx.bpp, &map->mlx.line_size, &map->mlx.endian);
	//map->mlx.img2 = mlx_xpm_file_to_image(map->mlx.ptr,map->text[NO],&width,&height);
	//map->mlx.data2 = (int *)mlx_get_data_addr(map->mlx.img2,bpp2,&size_line2,&endian2);
	//printf("%d\n",size_line2);
	print_backround(map);
	print_front(map);
	mlx_put_image_to_window(map->mlx.ptr, map->mlx.win, map->mlx.img, 0, 0);
	//mlx_put_image_to_window(map->mlx.ptr,map->mlx.win,map->mlx.img2,0,0);
	mlx_key_hook(map->mlx.win, deal_key, map);
}
