/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:53:46 by mhaman            #+#    #+#             */
/*   Updated: 2020/03/08 20:29:51 by mhaman           ###   ########lyon.fr   */
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

typedef	struct s_float
{
	double	x;
	double	y;
}				t_float;

typedef	struct s_int
{
	int		x;
	int		y;
}				t_int;

typedef struct s_cub
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

int parse_file_cub(t_cub map, char **argv, int argc)
{
	int fd;
	char *line;
	check_file_validity(map,argv, argc);
	check_instruction_validity(map,argv);
return(0);
}

int	check_instruction_validity(t_cub map, char ** argv)
{
	int fd;
	char *line;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) != 0)
	{
		if (line[0] != 0)
		{

		}
	}
}
int	check_file_validity(t_cub map,char **argv,int argc)
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
	parse_file_cub(*map, argv, argc);
	printf("file valid\n");
	free(map);
	return (0);
}