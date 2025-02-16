/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/02/16 22:35:39 by wshee            ###   ########.fr       */
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

void	find_column(char *line, int *fd, t_map *map)
{
	char **width_line;
	int column;

	width_line = ft_split(line, ' ');
	column = 0;
	while(width_line[column] != NULL)
		column++;
	//remember to free
	if (map->column == 0)
		map->column = column;
	else if (map->column != column)
	{
		error_and_exit("Error: Inconsistent row lengths in map");
		close(*fd);
		exit(1);
	}
}

void	set_map_row_and_column(char **av, t_map *map)
{
	int rows;
	int fd;
	char *line;

	rows = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_and_exit("Failed to open file\n");
	// printf("fd: %d\n", fd);
	line = get_next_line(fd);
	while (line != NULL)
	{
		rows++;
		//printf("line: %s", line);
		find_column(line, &fd, map);
		free(line);
		line = get_next_line(fd);
		//printf("line2: %s\n", line);
	}
	free(line);
	// printf("rows: %d\n", rows);
	map->row = rows;
	// printf("rows: %d\n", map->rows);
	// printf("width: %d\n", map->width);
	close(fd);
}

void	allocate_map(t_map *map)
{
	int i;

	map->arr_2d = (int **)malloc(map->row * sizeof(int *));
	if (!map->arr_2d)
		error_and_exit("Failed to allocate rows");
	i = 0;
	while (i < map->row)
	{
		map->arr_2d[i] = (int *)malloc(map->column * sizeof(int));
		if (!map->arr_2d[i])
			error_and_exit("Failed to allocate columns");
		i++;
	}
}

void set_z(char **av, t_map *map)
{
	int fd;
	//int i;
	char *line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_and_exit("Failed to open file\n");
	//i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->arr_2d[map->row][map->column].z;
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_maps(char **av, t_map *map)
{
	if (check_file_extension(av[1]) == 0)
		error_and_exit("Incorrect file extension\n");
	set_map_row_and_column(av, map);
	allocate_map(map);
	set_z(av, map);
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
