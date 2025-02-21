/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:48:18 by wshee             #+#    #+#             */
/*   Updated: 2025/02/21 21:29:32 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// first resets the image buffer before drawing a new frame
// to prevent leftover pixels from previous frames, ensure clean display
// which can cause unwanted artifacts or ghosting effects
// int *bits_per_pixel: Pointer to an integer where the function stores the number of bits per pixel.
// WIDTH * HEIGHT -> Total number of pixels in the image
//(fdf->bits_per_pixel / 8) -> Converts bits to bytes
// calculates total number of bytes to clear in image buffer
// ft_bzero sets all bytes to 0, sets entire image buffer to black
void	draw_map(t_map *map, t_fdf *fdf, t_data *data, t_point **arr)
{
	int row;
	int column;

	ft_bzero(data->addr, HEIGHT * WIDTH * (data->bits_per_pixel / 8));
	column = 0;
	while(column < map->column)
	{
		column = 0;
		while(row < map->row)
		{
			draw_line((*arr)->x, (*arr)->y, (*arr)->(x + 1), (*arr)->y);
			draw_line((*arr)->x, (*arr)->y, (*arr)->x, (*arr)->(y + 1));
			row++;
		}
		column++;
	}
}

void	draw_line(t_data *data, int begin_x, int begin_y, int end_x, int end_y, int color)
{
	int dx;
	int dy;

	dx = end_x - begin_x;
	dy = end_y - begin_y;
	if ()

}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
