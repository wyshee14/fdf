/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/03/05 17:55:01 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_img *init_img(t_fdf *fdf)
{
	t_img *img;

	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		error_and_exit("Failed to allocate memory for img");
	img->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	//printf("img: %p\n", img->img);
	if (!img->img)
		error_and_exit("Failed to allocate new image\n");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		error_and_exit("Failed to get img address\n");
	return(img);
}

int get_scale(t_fdf *fdf, t_move *move)
{
	int min;
	int x;
	int y;
	int z;

	x = WIDTH / fdf->map->column / 5;
	y = HEIGHT / fdf->map->row / 5;
	z = HEIGHT / move->z_max / 5;
	printf("x[%d], y[%d], z[%d]\n", x, y, z);
	min = x;
	if (min > y)
		min = y;
	if (min > z)
		min = z;
	if (min == 0)
		min = 2;
	printf("min: %d\n", min);
	// if ((WIDTH / fdf->map->column) < (HEIGHT / fdf->map->row))
	// 	return(WIDTH / fdf->map->column / 3);
	// return (HEIGHT / fdf->map->row / 3);
	return(min);
}

int find_z_min(t_fdf *fdf)
{
	int min;
	int i;
	int j;

	min = fdf->arr[0][0].z;
	j = 0;
	while(j < fdf->map->row)
	{
		i = 0;
		while(i < fdf->map->column)
		{
			if (min > fdf->arr[j][i].z)
				min = fdf->arr[j][i].z;
			i++;
		}
		j++;
	}
	// printf("zmin: %d\n", min);
	return(min);
}

int find_z_max(t_fdf *fdf)
{
	int max;
	int i;
	int j;

	max = fdf->arr[0][0].z;
	j = 0;
	while(j < fdf->map->row)
	{
		i = 0;
		while(i < fdf->map->column)
		{
			if(max < fdf->arr[j][i].z)
				max = fdf->arr[j][i].z;
			i++;
		}
		j++;
	}
	// printf("zmax: %d\n", max);
	return(max);
}

t_move *init_move(t_fdf *fdf)
{
	t_move *move;
	(void)fdf;

	move = ft_calloc(1, sizeof(t_move));
	if (!move)
		error_and_exit("Failed to allocate memory for move");
	move->z_min = find_z_min(fdf);
	// printf("zmin[%d]\n", move->z_min);
	move->z_max = find_z_max(fdf);
	// printf("zmax[%d]\n", move->z_max);
	move->z_elevation = move->z_max - move->z_min;
	// move->scale = SCALE;
	move->scale = get_scale(fdf, move);
	// printf("scale %d\n",move->scale);
	move->offset_x = 0;
	move->offset_y = 0;
	move->is_iso = 1;
	// printf("gamma: %f\n", move->gamma_z);
	//printf("offset_x: %d, step: %d\n", move->offset_x, move->step);
	return(move);
}

t_fdf	*init_fdf(t_fdf *fdf, char **av)
{
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		error_and_exit("Failed to allocate memory for fdf");
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		printf("Failed mlx init\n");
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	if (!fdf->win)
		printf("Failed to create window\n");
	fdf->img = init_img(fdf);
	fdf->map = parse_maps(av);
	fdf->arr = init_point(av, fdf->map);
	fdf->move = init_move(fdf);
	return(fdf);
}

int main(int ac, char **av)
{
	t_fdf *fdf;

	fdf = NULL;
	if (ac != 2)
		error_and_exit("Usage: ./fdf test_map.fdf\n");
	fdf = init_fdf(fdf, av);
	draw_map(fdf);
	setup_hook(fdf);
	mlx_loop(fdf->mlx);
}
