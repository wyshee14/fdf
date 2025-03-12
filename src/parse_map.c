/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:51:17 by wshee             #+#    #+#             */
/*   Updated: 2025/03/12 13:17:07 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// check whether the av[1] extension is .fdf
int	check_file_extension(char *filename)
{
	const char	*extension = ".fdf";
	int			ext_len;
	int			filename_len;

	ext_len = ft_strlen(extension);
	filename_len = ft_strlen(filename);
	if (filename_len == 0 || filename_len <= ext_len)
		return (1);
	while (ext_len > 0)
	{
		if (filename[filename_len - 1] != extension[ext_len - 1])
			return (1);
		ext_len--;
		filename_len--;
	}
	return (0);
}

// find the number of column using ft_split
// check whether the number of column is consistent in every row
void	find_column(char *line, int *fd, t_map *map)
{
	char	**width_line;
	int		column;

	width_line = ft_split(line, ' ');
	if (!width_line)
	{
		free_map(map);
		error_and_exit(SPLIT_ERROR);
	}
	column = 0;
	while (width_line[column] != NULL)
	{
		if (width_line[column][0] == '\n')
			break ;
		column++;
	}
	if (map->column == 0)
		map->column = column;
	else if (map->column != column)
	{
		close(*fd);
		free_map(map);
		error_and_exit("Error: Inconsistent row lengths in map");
	}
	free_2d_array((void **)width_line);
}

// read the file until next line
// count the number of rows from the input file
// iterate through the file using get next line
void	set_map_row_and_column(char **av, t_map *map)
{
	int		rows;
	int		fd;
	char	*line;

	rows = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		free_map(map);
		error_and_exit("Failed to open file\n");
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		rows++;
		find_column(line, &fd, map);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map->row = rows;
	close(fd);
}

// get the number of rows and column from the map
t_map	*parse_maps(char **av)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_move));
	if (!map)
	{
		free_map(map);
		error_and_exit("Failed to allocate memory for map");
	}
	if (check_file_extension(av[1]))
	{
		free_map(map);
		error_and_exit("Incorrect file extension");
	}
	set_map_row_and_column(av, map);
	return (map);
}
