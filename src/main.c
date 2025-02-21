/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/02/21 21:27:15 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// void init_data(t_map *map)
// {
// 	// map = (t_map *)malloc(sizeof(t_map));
// 	// if(!map)
// 	// 	error_and_exit("Failed to allocate memory for map");
// }

t_fdf	*init_fdf(t_fdf *fdf, t_data *data)
{
	(void)data;
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		error_and_exit("Failed to allocate memory for fdf");
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_and_exit("Failed to allocate memory for data");
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		printf("Failed mlx init\n");
	fdf->win = mlx_new_window(fdf->mlx, HEIGHT, WIDTH, "FDF");
	if (!fdf->win)
		printf("Failed to create window\n");
	data->img = mlx_new_image(fdf->mlx, HEIGHT, WIDTH);
	if (!data->img)
		printf("Failed to new image\n");
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	if (!data->addr)
		printf("Failed to get data address\n");
	//mlx_put_image_to_window(fdf->mlx, fdf->win, data->img, 0, 0);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
	mlx_loop(fdf->mlx);
	return(fdf);
}

void	scaling(t_point **arr, t_map *map)
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
	t_fdf *fdf;
	t_point **arr;
	t_data *data;

	(void)av;
	fdf = NULL;
	data = NULL;
	if (ac != 2)
		error_and_exit("Usage: ./fdf test_map.fdf\n");
	arr = parse_maps(av, &map);
	fdf = init_fdf(fdf, data);
	draw_map(&map, fdf, data, arr);
	// scaling(arr, &map);
	// isometric
	//free(map);
}
