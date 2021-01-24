/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 10:21:56 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/24 11:05:30 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ft_bitmap_image(t_cub *map, int fd, t_bpm2 bih)
{
	int				x;
	int				y;
	int				ble;
	unsigned char	color[3];

	write(fd, &bih, sizeof(bih));
	y = map->screen.y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < map->screen.x)
		{
			ble = map->mlx.data[y * map->screen.x + x];
			color[0] = ble % 256;
			ble /= 256;
			color[1] = ble % 256;
			ble /= 256;
			color[2] = ble % 256;
			write(fd, &color, sizeof(color));
			x++;
		}
		y--;
	}
}

void		ft_save_bitmap(const char *filename, t_cub *map)
{
	int			fd;
	t_bpm		bfh;
	t_bpm2		bih;

	ft_memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size = map->screen.x * map->screen.y * 4 + 54;
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.offset_bits = 0;
	bih.size_header = sizeof(bih);
	bih.width = map->screen.x;
	bih.height = map->screen.y;
	bih.planes = 1;
	bih.bit_count = 24;
	bih.compression = 0;
	bih.image_size = map->screen.x * map->screen.y * 4 + 54;
	bih.ppm_x = 2;
	bih.ppm_y = 2;
	bih.clr_used = 0;
	bih.clr_important = 0;
	close(open(filename, O_RDONLY | O_CREAT, S_IRWXU));
	fd = open(filename, O_RDWR);
	write(fd, &bfh, 14);
	ft_bitmap_image(map, fd, bih);
	closecub(map, 1);
}
