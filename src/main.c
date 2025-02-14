/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/02/14 23:02:15 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void error_and_exit(char *message)
{
	perror(message);
	exit(1);
}

int check_file_extension(char *filename)
{
	const char *extension;
	size_t filename_len;
	size_t	ext_len;
	const char *file_ext;

	extension = ".fdf";
	filename_len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	if (!filename)
		return(0);
	file_ext = filename + (filename_len - ext_len);
	if (strncmp(file_ext, extension, ext_len) == 0 && file_ext[-1] != '\0')
		return (1);
	return(0);
}

void	find_map_height(char **av, t_map *map)
{
	int height;
	// int width;
	int fd;
	char *line;

	height = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_and_exit("Failed to open file\n");
	printf("fd: %d\n", fd);
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		printf("line: %s", line);
		while (line != NULL)
		{
			char **width_line = ft_split(line, ' ');
			for (int i = 0; width_line != NULL; i++)
				printf("i: %d", i);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("height: %d\n", height);
	map->height = height;
	printf("height: %d\n", map->height);
	close(fd);
}

void parse_maps(char **av, t_map *map)
{

	if (check_file_extension(av[1]) == 0)
		error_and_exit("Incorrect file extension\n");
	find_map_height(av, map);
}

void init_data(t_map *map)
{
	// map = (t_map *)malloc(sizeof(t_map));
	// if(!map)
	// 	error_and_exit("Failed to allocate memory for map");
	ft_memset(map, 0, sizeof(t_map));
	//printf("height: %d\n", map->height);
}

int main(int ac, char **av)
{
	t_map map;

	(void)av;
	if (ac != 2)
		error_and_exit("Usage: ./fdf test_map.fdf\n");
	init_data(&map);
	parse_maps(av, &map);
	//free(map);
}
