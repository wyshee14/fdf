/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/02/18 22:09:49 by wshee            ###   ########.fr       */
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

// use calloc to assign memory and initialized it to 0
void	allocate_map(t_map *map, t_point ***arr)
{
	int i;

	printf("Malloc...\n");
	printf("row: %d, column: %d\n", map->row, map->column);
	printf("ptr_alloc_map: %p\n", *arr);
	*arr = ft_calloc(map->row, sizeof(t_point *));
	printf("ptr_alloc_map2: %p\n", *arr);
	if (!*arr)
		error_and_exit("Failed to allocate rows");
	i = 0;
	while (i < map->row)
	{
		(*arr)[i] = ft_calloc(map->column, sizeof(t_point));
		if (!(*arr)[i])
			error_and_exit("Failed to allocate columns");
		i++;
	}
}

//convert string to integer (base 16 to 10)
int ft_atoi_base(const char *str, int base)
{
	int i = 0;
	int sign = 1;
	int res = 0;
	int c;

	if(str[i] == '\0' || base < 2 || base > 16)
		return(0);
	if(str[i] == '-')
		i++;
	while (str[i])
	{
		if(str[i] >= '0' && str[i] <= '9')
			c = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			c = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			c = str[i] - 'A' + 10;
		res = res * base + c;
		i++;
	}
	return (res * sign);
}

int get_color(char *column_line)
{
	int i;

	i = 0;
	while (column_line[i])
	{
		if(column_line[i] == ',')
		{
			char **color_arr = ft_split(column_line, ',');
			for(int i = 0; color_arr[i] != NULL; i++)
				printf("color: %s\n", color_arr[i]);
			int color = ft_atoi_base(color_arr[1], 16);
			return(color);
		}
		i++;
	}
	return(DEFAULT_COLOR);
}

void set_z_arr(char **av, t_map *map, t_point ***arr)
{
	int fd;
	//int i;
	char *line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_and_exit("Failed to open file\n");
	//i = 0;
	printf("ptr_set_z_arr: %p\n", *arr);
	allocate_map(map, arr);
	printf("ptr_post_alloc: %p\n", *arr);
	// ft_calloc(&arr, 0, sizeof(t_point));
	// for (int i = 0; i < map->row; i++)
    // {
	// 	// printf("i: %d\n", i);
    //     for (int j = 0; j < map->column; j++)
    //     {
    //         // printf("j: %d\n", j);
	// 		printf("%d ", (*arr)[i][j].x);
    //     }
    //     printf("\n");
    // }
	line = get_next_line(fd);
	while (line != NULL)
	{
		char **column_line = ft_split(line, ' ');
		int width = 0;
		while(column_line[width])
		{
			(**arr)->z = ft_atoi(column_line[width]);
			(**arr)->color = get_color(column_line[width]);
			//printf("%d ", (**arr)->z);
			width++;
		}
		//arr[map->row][map->column];
		free(line);
		line = get_next_line(fd);
		printf("\n");
	}
	close(fd);
}

void	parse_maps(char **av, t_map *map)
{
	t_point **arr;

	if (check_file_extension(av[1]) == 0)
		error_and_exit("Incorrect file extension\n");
	set_map_row_and_column(av, map);
	set_z_arr(av, map, &arr);
	//set_color();
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
