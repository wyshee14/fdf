/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:51:17 by wshee             #+#    #+#             */
/*   Updated: 2025/03/03 18:37:47 by wshee            ###   ########.fr       */
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
	(void)fd;

	width_line = ft_split(line, ' ');
	if (!width_line)
		error_and_exit(SPLIT_ERROR);

	column = 0;
	while (width_line[column] != NULL)
		column++;

	// Check if the last character in `line` is a space and adjust `column`
	if (line[strlen(line) - 1] == ' ')
		column--;

	if (map->column == 0)
	{
		map->column = column;
		// printf("col: %d\n", map->column);
	}
	else if (map->column != column)
	{
		//printf("col: %d\n", map->column);
		close(*fd);
		error_and_exit("Error: Inconsistent row lengths in map");
	}

	// Free allocated memory
	for (int i = 0; width_line[i] != NULL; i++)
		free(width_line[i]);
	free(width_line);
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
	map->row = rows;
	close(fd);
}

t_map	*parse_maps(char **av)
{
	// t_point **arr;
	t_map *map;

	map = ft_calloc(1, sizeof(t_move));
	if (!map)
		error_and_exit("Failed to allocate memory for map");
	//ft_memset(map, 0, sizeof(t_map));
	if (check_file_extension(av[1]) == 0)
		error_and_exit("Incorrect file extension\n");
	set_map_row_and_column(av, map);

	return(map);
}
