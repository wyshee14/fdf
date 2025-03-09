/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:48:18 by wshee             #+#    #+#             */
/*   Updated: 2025/03/08 23:18:23 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void isometric_projection(t_point *point, t_fdf *fdf)
{
	double iso_radian;
	int previous_x = point->x;
	// double previous_y = point->y;

	iso_radian = 30 * M_PI / 180;
	// printf("%f\n", iso_radian);
	point->x = (previous_x - point->y) * cos(iso_radian);
	point->y = ((previous_x + point->y) * sin(iso_radian)) - (point->z * fdf->move->z_factor);
}

// 1. zoom the point to according to its scale
// 2. centre of the map become the new origin (0,0)
// 3. convert to isometric
// 4. move to centre of window
t_point	ft_scale(t_point point, t_fdf *fdf)
{
	// printf("Ori point: x[%d], y[%d], z[%f]\n", point.x, point.y, point.z);
	point.x *= fdf->move->scale;
	point.y *= fdf->move->scale;
	point.z *= fdf->move->scale;
	// printf("After point: x[%d], y[%d], z[%f]\n", point.x, point.y, point.z);
	point.x -= (fdf->map->column * fdf->move->scale) / 2;
	point.y -= (fdf->map->row * fdf->move->scale) / 2;
	if (fdf->move->is_iso == 1)
		isometric_projection(&point, fdf);
	// printf("Transformed  x: %d, y: %d, z: %d\n", point.x, point.y, point.z);
	// printf("Before projection: x=%d, y=%d, z=%d\n", point.x, point.y, point.z);
	rotate_x(&point, fdf->move);
	rotate_y(&point, fdf->move);
	rotate_z(&point, fdf->move);
	// printf("After projection: x=%d, y=%d, z=%d\n", point.x, point.y, point.z);
	point.x += WIDTH / 2 + fdf->move->offset_x;
	point.y += HEIGHT / 2 + fdf->move->offset_y;
	return(point);
}

// p1 is the begin point and scale before draw
// x draw to the right until the last column
// y draw to downwards until the last row
void	draw_array(t_fdf *fdf, int x, int y)
{
	t_point p1;
	t_point p2;
	t_point p3;

	p1 = ft_scale(fdf->arr[y][x], fdf);
	if(x != fdf->map->column - 1) 
	{
		p3 = ft_scale(fdf->arr[y][x + 1], fdf);
		// printf("p1: x[%d] y[%d], p3: x[%d] y[%d]\n", p1.x, p1.y, p3.x, p3.y);
		draw_line_bresenham(fdf->img, &p1, &p3);
	}
	if(y != fdf->map->row - 1) 
	{
		p2 = ft_scale(fdf->arr[y + 1][x], fdf);
		// printf("p1: x[%d] y[%d], p2: x[%d] y[%d]\n", p1.x, p1.y, p2.x, p2.y);
		draw_line_bresenham(fdf->img, &p1, &p2);
	}
}

// first resets the image buffer before drawing a new frame
// to prevent leftover pixels from previous frames, ensure clean display
// which can cause unwanted artifacts or ghosting effects
// int *bits_per_pixel: Pointer to an integer where the function stores the number of bits per pixel.
// WIDTH * HEIGHT -> Total number of pixels in the image
//(fdf->bits_per_pixel / 8) -> Converts bits to bytes
// calculates total number of bytes to clear in image buffer
// ft_bzero sets all bytes to 0, sets entire image buffer to black
int	draw_map(t_fdf *fdf)
{
	int x;
	int y;

	clear_image(fdf);
	y = 0;
	while(y < fdf->map->row)
	{
		x = 0;
		while(x < fdf->map->column)
		{
			draw_array(fdf, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	return(0);
}
