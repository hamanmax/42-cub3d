/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:08:02 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 16:10:55 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	check_texture_validity(t_cub *map, char *line)
{
	char	*found;
	char	*texture[3];
	int		i;

	i = 0;
	if (map->text[check_type_texture(line)])
		error_str_return("Textures Indication given twice");
	while ((found = ft_strsep(&line, " ")) && i <= 2)
		if (found[0])
			texture[i++] = found;
	if (i < 2 || i > 2)
		error_str_return("Too many/not enought information");
	map->text[check_type_texture(texture[0])] = ft_strdup(texture[1]);
	if ((i = open(map->text[check_type_texture(texture[0])], O_RDONLY)) == -1)
		error_str_return("can't open texture files");
	map->texture[check_type_texture(texture[0])] = i;
	return (1);
}

int	check_type_texture(char *line)
{
	if (ft_strnstr(line, "NO", 2))
		return (0);
	else if (ft_strnstr(line, "SO", 2))
		return (1);
	else if (ft_strnstr(line, "EA", 2))
		return (2);
	else if (ft_strnstr(line, "WE", 2))
		return (3);
	else if (ft_strnstr(line, "S", 1))
		return (4);
	return (-1);
}
