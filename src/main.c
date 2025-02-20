/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/02/20 22:37:37 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// void init_data(t_map *map)
// {
// 	// map = (t_map *)malloc(sizeof(t_map));
// 	// if(!map)
// 	// 	error_and_exit("Failed to allocate memory for map");
// }

t_fdf *init_fdf(t_fdf *fdf, t_data *data)
{
	(void)data;
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		error_and_exit("Failed to allocate memory for fdf");
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "FDF");
	return(fdf);
}

void scaling(t_point **arr, t_map *map)
{
	int row;
	int column;

	row = 0;
	while (row < map->row)
	{
		column = 0;
		while (column < map->column)
		{
			(*arr)->x *= SCALE;
			(*arr)->y *= SCALE;
			column++;
		}
		row++;
	}
	for (int i = 0; i < map->row; i++)
	{
		for (int j = 0; j < map->column; j++)
		{
			printf("%d ", (arr)[i][j].x);
		}
		printf("\n");
	}
}

int main(int ac, char **av)
{
	t_map map;
	//t_fdf *fdf;
	t_point **arr;
	//t_data *data;

	(void)av;
	if (ac != 2)
		error_and_exit("Usage: ./fdf test_map.fdf\n");
	arr = parse_maps(av, &map);
	scaling(arr, &map);
	// isometric
	// draw_line
	// fdf = init_fdf(fdf, data);
	//free(map);
}
