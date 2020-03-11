/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:53:46 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/10 22:11:29 by mhaman           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "libft/libft.h"

enum			e_text
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	SPRITE,
	TEXTURE_COUNT
};

typedef	struct	s_float
{
	double	x;
	double	y;
}				t_float;

typedef	struct	s_int
{
	int		x;
	int		y;
}				t_int;

typedef struct	s_cub
{
	int screenlength;
	int screenwidth;
	int colorsky[3];
	int colorfloor[3];
	int northtexture;
	int southtexture;
	int easttexture;
	int westtexture;
	int spritetexture;
	char **map;
	t_int	player_pos;
	char *text[TEXTURE_COUNT];
}				t_cub;

int parse_file_cub(t_cub *map, char **argv, int argc)
{
	int fd;
	char *line;
	check_file_validity(map,argv, argc);
	check_instruction_validity(map,argv);
return(0);
}

int	check_instruction_validity(t_cub *map, char ** argv)
{
	int fd;
	char *line;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) != 0)
	{
		if (line[0] != 0)
		{
			if (ft_strnstr(line,"R ",3) != NULL)
			{
				check_resolution_validity(map, line);
			}
			else if (ft_strnstr(line,"C ",3) != NULL)
			{
				check_sky_validity(map, line);
			}
			else if (ft_strnstr(line,"F ",3) != NULL)
			{
				check_floor_validity(map, line);
			}
			free(line);
		}
	}
}

int check_floor_validity(t_cub *map, char *line)
{

	printf("IN FLOOR%s\n",line);
	char *found;
	char *colorfloor[5];
	size_t i;

	i = 0;
	if (map->colorfloor[0] != 0 && map->colorfloor[1] != 0 &&
	map->colorfloor[2] != 0)
		error_str_return("Multiple times Color floor instruction");
	while ((found = ft_strsep(&line," ,")) != NULL &&  i != 5)
		if (found[0] != 0)
			colorfloor[i++] = found;
	if (i > 4)
		error_str_return("Too many arguments, colorfloor need 3 got more ");
	if (i < 4)
		error_str_return("Not enought arguments, colorfloor need 3 got less ");
	while (--i >= 1)
		map->colorfloor[i - 1] = ft_atoi(colorfloor[i]);
	if (map->colorfloor[0] < 0 || map->colorfloor[0] > 255 ||
	map->colorfloor[1] < 0 || map->colorfloor[1] > 255 ||
	map->colorfloor[2] < 0 || map->colorfloor[2] > 255)
		error_str_return("Color floor Must be between 0 and 255");
	return (1);
}

int check_sky_validity(t_cub *map, char *line)
{
	char *found;
	char *colorsky[5];
	size_t i;

	printf("IN SKY\t%s\n",line);
	i = 0;
	if (map->colorsky[0] != 0 && map->colorsky[1] != 0 &&
	map->colorsky[2] != 0)
		error_str_return("Multiple times Color sky instruction");
	while ((found = ft_strsep(&line," ,")) != NULL &&  i != 5)
		if (found[0] != 0)
		{
			colorsky[i++] = found;
			printf("%s\n",found);
		}
	if (i > 4)
		error_str_return("Too many arguments, colorsky need 3 got more ");
	if (i < 4)
		error_str_return("Not enought arguments, colorsky need 3 got less ");
	while (--i >= 1)
		map->colorsky[i - 1] = ft_atoi(colorsky[i]);
	if (map->colorsky[0] < 0 || map->colorsky[0] > 255 ||
	map->colorsky[1] < 0 || map->colorsky[1] > 255 ||
	map->colorsky[2] < 0 || map->colorsky[2] > 255)
		error_str_return("Color sky Must be between 0 and 255");
	return (1);
}

int check_resolution_validity(t_cub *map, char *line)
{
	char *found;
	char *resolution[4];
	size_t i;

	i = 0;
	if (map->screenlength != 0 || map->screenwidth != 0)
		error_str_return("Multiple times Resolution instruction");
	while ((found = ft_strsep(&line," ")) != NULL &&  i != 4)
		if (found[0] != 0)
			resolution[i++] = found;
	if (i > 3)
		error_str_return("Too many arguments, resolution need 3 got more ");
	if (i < 3)
		error_str_return("Not enought arguments, resolution need 3 got less ");
	map->screenlength = ft_atoi(resolution[1]);
	map->screenwidth = ft_atoi(resolution[2]);
	if (map->screenwidth <= 0 || map->screenlength <= 0)
		error_str_return("Resolution width or length can't be 0 or negativ");
	if (map->screenwidth > 3840 || map->screenlength > 2160)
	{
		printf("Resizing screen resolution\n");
		map->screenlength = 3840;
		map->screenwidth = 2160;
	}
}

int	check_file_validity(t_cub *map,char **argv,int argc)
{
	int fd;
	char *file;

	if (argc < 2)
		error_str_return("Missing map file");
	if(argc == 3)
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
	if ((fd = open(argv[1],O_RDONLY)) == -1)
		error_str_return("Could not open file");
	else
		close(fd);
	return (1);
}

int error_str_return(char *str)
{
	printf("ERROR\n%s", str);
	exit(-1);
}

int main(int argc, char** argv)
{
	char *line;
	char	buff[1024];

	t_cub *map;
	ft_bzero((map = malloc(sizeof(t_cub))), sizeof(t_cub));
	parse_file_cub(map, argv, argc);
	printf("file valid\n");
	free(map);
	return (0);
}