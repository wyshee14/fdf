/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:56:22 by wshee             #+#    #+#             */
/*   Updated: 2025/03/05 20:56:24 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	clear_image(t_fdf *fdf)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(fdf->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
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
