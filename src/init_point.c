/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:59:06 by wshee             #+#    #+#             */
/*   Updated: 2025/03/11 15:06:02 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// use calloc to assign memory and initialized it to 0
void	allocate_map(t_map *map, t_point ***arr)
{
	int	i;

	*arr = (t_point **)ft_calloc(map->row, sizeof(t_point *));
	if (!*arr)
	{
		free_2d_array((void **)(*arr));
		free_map(map);
		error_and_exit("Failed to allocate rows");
	}
	i = 0;
	while (i < map->row)
	{
		(*arr)[i] = (t_point *)ft_calloc(map->column, sizeof(t_point));
		if (!(*arr)[i])
		{
			free_2d_array((void **)(*arr));
			free_map(map);
			error_and_exit("Failed to allocate columns");
		}
		i++;
	}
}

//ft_atoi_base convert string to integer (base 16 to 10)
int	get_color(char *column_line, t_map *map)
{
	int		i;
	char	**color_arr;
	int		color;

	i = 0;
	color_arr = NULL;
	while (column_line[i])
	{
		if (column_line[i] == ',')
		{
			color_arr = ft_split(column_line, ',');
			if (!color_arr)
			{
				free_map(map);
				error_and_exit(SPLIT_ERROR);
			}
			color = ft_atoi_base(color_arr[1], 16);
			free_2d_array((void **)color_arr);
			return (color);
		}
		i++;
	}
	return (DEFAULT_COLOR);
}

void	extract_data(char *line, t_point ***arr, t_map *map, int row)
{
	char	**column_line;
	int		col;

	column_line = ft_split(line, ' ');
	if (!column_line)
		error_and_exit(SPLIT_ERROR);
	col = 0;
	while (column_line[col] && col < map->column)
	{
		(*arr)[row][col].x = col;
		(*arr)[row][col].y = row;
		(*arr)[row][col].z = ft_atoi(column_line[col]);
		(*arr)[row][col].color = get_color(column_line[col], map);
		(*arr)[row][col].ori_color = (*arr)[row][col].color;
		col++;
	}
	free_2d_array((void **)column_line);
}

// this function is used to plot the point on the map
t_point	**init_point(char **av, t_map *map)
{
	int		fd;
	char	*line;
	int		row;
	t_point	**arr;

	arr = NULL;
	if (map == NULL)
		return (NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_and_exit("Failed to open file\n");
	allocate_map(map, &arr);
	line = get_next_line(fd);
	row = 0;
	while (line != NULL && row < map->row)
	{
		extract_data(line, &arr, map, row);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close (fd);
	return (arr);
}
