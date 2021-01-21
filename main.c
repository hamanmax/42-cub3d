/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:40:25 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 10:49:43 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_dir_plane_vector(t_cub *map)
{
	const char c = map->player.orientation;

	if (c == 'N')
	{
		map->player.dir.x = -1.0;
		map->player.plane.y = 0.66;
	}
	if (c == 'S')
	{
		map->player.dir.x = 1;
		map->player.plane.y = -0.66;
	}
	if (c == 'E')
	{
		map->player.dir.y = 1;
		map->player.plane.x = 0.66;
	}
	if (c == 'W')
	{
		map->player.dir.y = -1.0;
		map->player.plane.x = -0.66;
	}
}

void set_data(t_cub *map)
{
	int bpp;
	int endian;
	int line_size;
	int i;
	void *img_txt;

	i = 0;

	while (i < TEXTURE_COUNT)
	{
		img_txt = mlx_xpm_file_to_image(map->mlx.ptr,map->text[i],&map->mlx.w[i],&map->mlx.h[i]);
		map->mlx.data_text[i] = (int *)mlx_get_data_addr(img_txt,&bpp,&line_size,&endian);
		i++;
	}
}

void free_all(t_cub *map)
{
	int i;

	i = 0;
	while (i <= map->mapsize.y)
	{
		free(map->map[i]);
		i++;
	}
	free(map->sprite);
	free(map->screenpx);
	free(map);
}

void set_sprite(t_cub *map)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	map->sprite = malloc(map->nbsprite * sizeof(t_sprite));
	dprintf(1,"%d\t%d\n",map->nbsprite,map->mapsize.y);
	while (i <= map->mapsize.y)
	{
		while(j <= map->mapsize.x)
		{
			if (map->map[i][j] == '2')
			{
				map->sprite[k].pos.x = i + 0.5;
				map->sprite[k].pos.y = j + 0.5;
				k++;
			} 
			j++;
		}
		i++;
		j = 0;
	}
}

void ft_init_struct(t_cub *map, int code)
{
	if (code == 0)
	{
		map->colorfloor = -1;
		map->colorsky = -1;
		map->mlx.ptr = mlx_init();
	}
	if (code == 1)
	{
		map->player.orientation = 
		map->map[(int)map->player.pos.x][(int)map->player.pos.y];
		map->player.pos.x += 0.5;
		map->player.pos.y += 0.5;
		set_dir_plane_vector(map);
		set_data(map);
		set_sprite(map);
		map->mlx.img = mlx_new_image(map->mlx.ptr, map->screen.x, map->screen.y);
		map->mlx.data = (int *)mlx_get_data_addr(map->mlx.img, &map->mlx.bpp, &map->mlx.line_size, &map->mlx.endien);
		map->mlx.win = mlx_new_window(map->mlx.ptr, map->screen.x, map->screen.y, "Cub3d");
	}
}

int				ft_key_press(int keycode, t_cub *map)
{
	if(keycode == K_W)
	map->move.forward = 1;
	if(keycode == K_S)
	map->move.backward = 1;
	if(keycode == K_A)
	map->move.leftside = 1;
	if(keycode == K_D)
	map->move.rightside = 1;
	if(keycode == K_Q)
	map->move.leftrot = 1;
	if(keycode == K_E)
	map->move.rightrot = 1;
	if(keycode == K_ESC)
	map->move.close = 1;
	return (1);
}

int				ft_key_release(int keycode, t_cub *map)
{
	if(keycode == K_W)
		map->move.forward = 0;
	if(keycode == K_S)
		map->move.backward = 0;
	if(keycode == K_A)
		map->move.leftside = 0;
	if(keycode == K_D)
		map->move.rightside = 0;
	if(keycode == K_Q)
		map->move.leftrot = 0;
	if(keycode == K_E)
		map->move.rightrot = 0;
	return (1);
}

int		main(int argc, char **argv)
{
	int i;

	i = 0;
	t_cub			*map;

	map = ft_calloc(1,sizeof(t_cub));
	ft_init_struct(map, 0);
	parse_file_cub(map, argv, argc);
	ft_init_struct(map, 1);
	printf("file valid\n");
	//raycasting(map);
	map->screenpx = malloc(map->screen.x * map->screen.y * sizeof(int));
	mlx_hook(map->mlx.win, 2, 1L << 0, &ft_key_press, map);
	mlx_hook(map->mlx.win, 3, 1L << 1, &ft_key_release, map);
	mlx_loop_hook(map->mlx.ptr, &main_loop, map);
	mlx_loop(map->mlx.ptr);
	free_all(map);
	return (0);
}
