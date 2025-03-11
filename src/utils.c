/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:56:22 by wshee             #+#    #+#             */
/*   Updated: 2025/03/11 23:04:03 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// first resets the image buffer before drawing a new frame when moving
// to prevent leftover pixels from previous frames, ensure clean display
// which can cause unwanted artifacts or ghosting effects
// int *bits_per_pixel: Pointer to an integer where the function
// stores the number of bits per pixel.
// WIDTH * HEIGHT -> Total number of pixels in the image
//(fdf->bits_per_pixel / 8) -> Converts bits to bytes
// calculates total number of bytes to clear in image buffer
// ft_bzero sets all bytes to 0, sets entire image buffer to black
//ft_bzero(fdf->img->addr, HEIGHT * WIDTH * (fdf->img->bits_per_pixel / 8));
void	clear_image(t_fdf *fdf)
{
	int	x;
	int	y;

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

//TODO error handling if value is 0
int	get_scale(t_fdf *fdf, t_move *move)
{
	int	min;
	int	x = 0;
	int	y = 0;
	int	z = 0;

	// if (!fdf->map->column || !fdf->map->row || !move->z_max)
	// 	return (0);
	// fdf->map->column = 0;
	// fdf->map->row = 0;
	// move->z_max = 0;
	if (fdf->map->column > 0)
		x = WIDTH / fdf->map->column / 5;
	if (fdf->map->row > 0)
		y = HEIGHT / fdf->map->row / 5;
	if (move->z_max > 0)
		z = HEIGHT / move->z_max / 5;
	else
		z = x;
	printf("x: %d, y: %d, z %d\n", x, y, z);
	min = x;
	if (min > y)
		min = y;
	if (min > z)
		min = z;
	if (min == 0)
		min = 2;
	printf("min: %d\n", min);
	return (min);
}

int	find_z_max(t_fdf *fdf)
{
	int	max;
	int	i;
	int	j;

	max = fdf->arr[0][0].z;
	j = 0;
	while (j < fdf->map->row)
	{
		i = 0;
		while (i < fdf->map->column)
		{
			if (max < fdf->arr[j][i].z)
				max = fdf->arr[j][i].z;
			i++;
		}
		j++;
	}
	return (max);
}

// to put a pixel on window at x & y coordinate
// the grid of pixels is sotred in 1D array in memory
// Each pixel is stored in 4 bytes
// t_img *img: A pointer to an img structure that contains image data
// char dst is used to calculate the exact memory location of the pixel
// img->addr is a pointer to the first pixel in the image
// img->line_length is the number of bytes per row of pixels (WIDTH x 4)
// img->bits_per_pixel / 8 converts bits per pixel into bytes per pixel
// dst is cast to an unsigned int * to store a 32-bit color value.
// and assign the color to the pixel at (x, y).
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr)
	{
		perror("Error: Invalid image pointer\n");
		return ;
	}
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	free_2d_array(void **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free (arr);
}
