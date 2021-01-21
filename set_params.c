/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:12:49 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 15:46:25 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	set_dir_plane_vector(t_cub *map)
{
	const char c= map->player.orientation;

	if (c == 'N')
	{
		map->player.dir.x = -1.0;
		map->player.plane.y = 0.66;
	}
	else if (c == 'S')
	{
		map->player.dir.x = 1;
		map->player.plane.y = -0.66;
	}
	else if (c == 'E')
	{
		map->player.dir.y = 1;
		map->player.plane.x = 0.66;
	}
	else if (c == 'W')
	{
		map->player.dir.y = -1.0;
		map->player.plane.x = -0.66;
	}
}

void	set_data(t_cub *map)
{
	int		v;
	int		i;
	void	*img_txt;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		img_txt = 
		mlx_xpm_file_to_image(map->mlx.ptr, 
		map->text[i], &map->mlx.w[i], &map->mlx.h[i]);
		map->mlx.data_text[i] = 
		(int *)mlx_get_data_addr(img_txt, &v, &v, &v);
		i++;
	}
}

void	set_sprite(t_cub *map)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	map->sprite = malloc(map->nbsprite * sizeof(t_sprite));
	while (i <= map->mapsize.y)
	{
		while (j <= map->mapsize.x)
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