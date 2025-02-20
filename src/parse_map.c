/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:51:17 by wshee             #+#    #+#             */
/*   Updated: 2025/02/20 22:13:40 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
	if (!width_line)
		error_and_exit(SPLIT_ERROR);
	column = 0;
	while(width_line[column] != NULL)
		column++;
	if (map->column == 0)
		map->column = column;
	else if (map->column != column)
	{
		close(*fd);
		error_and_exit("Error: Inconsistent row lengths in map");
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

t_point	**parse_maps(char **av, t_map *map)
{
	t_point **arr;

	ft_memset(map, 0, sizeof(t_map));
	if (check_file_extension(av[1]) == 0)
		error_and_exit("Incorrect file extension\n");
	set_map_row_and_column(av, map);
	init_point(av, map, &arr);
	return(arr);
}
