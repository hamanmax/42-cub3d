/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:01:35 by mhaman            #+#    #+#             */
/*   Updated: 2021/01/21 16:15:01 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	check_file_validity(t_cub *map, char **argv, int argc)
{
	int				fd;
	char			*file;

	if (argc < 2)
		error_str_return("Missing map file");
	if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 8) != 0)
			error_str_return("Bad option here only --save available");
	if ((file = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) == NULL)
		error_str_return("No .cub format found");
	else
	{
		file -= 1;
		if (*file == 0)
			error_str_return("File need name");
		file += 5;
		if (*file != 0)
			error_str_return("Bad Format File");
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error_str_return("Could not open file");
	else
		close(fd);
	return (1);
}

int	check_instruction_validity(t_cub *map, char **line)
{
	char		*found;
	const char	*top = *line;

	while ((*line && (found = ft_strsep(line, "\n"))))
	{
		if (found[0])
		{
			if (ft_strnstr(found, "R ", 3))
				check_resolution_validity(map, found);
			else if (ft_strnstr(found, "C ", 3))
				map->colorsky = check_color_validity(map, found, 0);
			else if (ft_strnstr(found, "F ", 3))
				map->colorfloor = check_color_validity(map, found, 1);
			else if (check_type_texture(found) != -1)
				check_texture_validity(map, found);
			else if (ft_strnstr(found, "1", 1) || ft_strnstr(found, " ", 1))
				check_map_validity(map, found, line);
			else
				error_str_return("Unreconized Arguments");
		}
	}
	free((char *)top);
	return (1);
}

int	check_struct_validity(t_cub *map, size_t i)
{
	if (!map->screen.x || !map->screen.y)
		error_str_return("Resolution not set");
	if (map->colorfloor == -1)
		error_str_return("Color Floor not set");
	if (!map->colorsky == -1)
		error_str_return("Color sky not set");
	if (!map->text[NO])
		error_str_return("NORTH texture not set");
	if (!map->text[SO])
		error_str_return("SOUTH texture not set");
	if (!map->text[WE])
		error_str_return("WEST texture not set");
	if (!map->text[EA])
		error_str_return("EAST texture not set");
	if (!map->text[SPRITE])
		error_str_return("SPRITE texture not set");
	if (i == 1 && !map->map)
		error_str_return("Map description not set");
	return (0);
}

int	check_resolution_validity(t_cub *map, char *line)
{
	char		*found;
	size_t		i;

	i = 0;
	if (map->screen.x != 0 || map->screen.y != 0)
		error_str_return("Multiple times Resolution instruction");
	while ((found = ft_strsep(&line, " ")) && i != 5)
	{
		if (found[0] != 0 && i == 1)
			map->screen.x = ft_atoi(found);
		else if (found[0] != 0 && i == 2)
			map->screen.y = ft_atoi(found);
		if (found[0] != 0)
			i++;
		if (ft_str_isdigit(found) == 0 && i > 1 && i < 4)
			error_str_return("Resolution must be digits");
	}
	if (i > 3)
		error_str_return("Too many arguments, resolution need 3 got more");
	if (i < 3)
		error_str_return("Not enought arguments, resolution need 3 got less");
	resizing_map(map);
	return (1);
}

int	check_color_validity(t_cub *map, char *line, int i)
{
	char		*found;
	int			j;
	int			rgb;

	rgb = 0;
	j = 24;
	if (i == 0 && map->colorsky != -1 || i == 1 && map->colorfloor != -1)
		error_str_return("Multiple times Color instruction");
	if (ft_str_char_occur(line, ',') != 2)
		error_str_return("to much/not enought ',' in instruction");
	while ((found = ft_strsep(&line, " ,")))
		if (found[0] != 0)
		{
			rgb += ft_atoi(found) << j;
			if (ft_atoi(found) < 0 || ft_atoi(found) > 255)
				error_str_return("Color Must be between 0 and 255");
			if (ft_str_isdigit(found) == 0 && j < 24)
				error_str_return("Color must be digits");
			j -= 8;
		}
	if (j != -8)
		error_str_return("Too many/not enought arguments, color need 4");
	return (rgb);
}
