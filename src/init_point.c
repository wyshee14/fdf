/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:59:06 by wshee             #+#    #+#             */
/*   Updated: 2025/02/20 22:29:30 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// use calloc to assign memory and initialized it to 0
void allocate_map(t_map *map, t_point ***arr)
{
	int i;

	printf("Malloc...\n");
	printf("row: %d, column: %d\n", map->row, map->column);
	printf("ptr_alloc_map: %p\n", *arr);

	// Allocate row pointers
	*arr = (t_point **)ft_calloc(map->row, sizeof(t_point *));
	if (!*arr)
		error_and_exit("Failed to allocate rows");

	printf("ptr_alloc_map2: %p\n", *arr);

	// Allocate columns
	for (i = 0; i < map->row; i++)
	{
		(*arr)[i] = (t_point *)ft_calloc(map->column, sizeof(t_point));
		if (!(*arr)[i])
		{
			// Free previously allocated rows before exiting
			while (--i >= 0)
				free((*arr)[i]);
			free(*arr);
			error_and_exit("Failed to allocate columns");
		}
	}
}

//ft_atoi_base convert string to integer (base 16 to 10)
int get_color(char *column_line)
{
	int	i;
	char **color_arr;
	int	color;

	i = 0;
	while (column_line[i])
	{
		if(column_line[i] == ',')
		{
			color_arr = ft_split(column_line, ',');
			if (!color_arr)
				error_and_exit(SPLIT_ERROR);
			// for(int i = 0; color_arr[i] != NULL; i++)
			// 	printf("color: %s\n", color_arr[i]);
			color = ft_atoi_base(color_arr[1], 16);
			return(color);
		}
		i++;
	}
	return(DEFAULT_COLOR);
}

//this function is used to plot the point on the map
void init_point(char **av, t_map *map, t_point ***arr)
{
	int fd;
	char *line;
	int row = 0;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_and_exit("Failed to open file\n");

	allocate_map(map, arr);  // Ensure memory is allocated
	printf("ptr_post_alloc: %p\n", *arr);

	line = get_next_line(fd);
	while (line != NULL && row < map->row)
	{
		char **column_line = ft_split(line, ' ');
		if (!column_line)
			error_and_exit(SPLIT_ERROR);
		int col = 0;
		while (column_line[col] && col < map->column)
		{
			(*arr)[row][col].x = col;
			(*arr)[row][col].y = row;
			(*arr)[row][col].z = ft_atoi(column_line[col]);
			(*arr)[row][col].color = get_color(column_line[col]);
			col++;
		}
		free_2d_array(column_line);
		free(line);
		line = get_next_line(fd);
		row++;  // Move to the next row
	}

	close(fd);

	//Debugging print
	// for (int i = 0; i < map->row; i++)
	// {
	// 	for (int j = 0; j < map->column; j++)
	// 	{
	// 		printf("%d ", (*arr)[i][j].x);
	// 	}
	// 	printf("\n");
	// }
}
