/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:48:18 by wshee             #+#    #+#             */
/*   Updated: 2025/02/24 22:40:17 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void isometric_projection(t_point *point)
{
	double iso_radian;
	int previous_x = point->x;
	// double previous_y = point->y;

	iso_radian = (30) * M_PI / 180;
	// printf("%f\n", iso_radian);
	point->x = (previous_x - point->y) * cos(iso_radian);
	point->y = ((previous_x + point->y) * sin(iso_radian)) - point->z;
}

t_point	ft_scale(t_point point, t_map *map)
{
	// int previous_x;
	(void)map;

	//printf("Ori point: x[%d], y[%d], z[%d]\n", point.x, point.y, point.z);
	point.x *= SCALE;
	point.y *= SCALE;
	point.z *= SCALE;
	//centre of the map become the new origin (0,0)
	// point.x -= (map->column * SCALE) / 2;
	// point.y -= (map->row * SCALE) / 2;
	//convert to isometric
	//printf("Before projection: x=%d, y=%d, z=%d\n", point.x, point.y, point.z);
	// isometric_projection(&point);
	//printf("After projection: x=%d, y=%d, z=%d\n", point.x, point.y, point.z);
	// previous_x = point.x;
	// point.x = (point.x - point.y) * cos(0.52359877559);
	// point.y = (previous_x + point.y) * sin(0.52359877559) - point.z;
	// printf("Transformed  x: %d, y: %d, z: %d\n", point.x, point.y, point.z);
	// printf("py: %d\n", point.y);
	//move to centre
	// point.x += WIDTH / 2;
	// point.y += HEIGHT / 2;
	return(point);
}

// first resets the image buffer before drawing a new frame
// to prevent leftover pixels from previous frames, ensure clean display
// which can cause unwanted artifacts or ghosting effects
// int *bits_per_pixel: Pointer to an integer where the function stores the number of bits per pixel.
// WIDTH * HEIGHT -> Total number of pixels in the image
//(fdf->bits_per_pixel / 8) -> Converts bits to bytes
// calculates total number of bytes to clear in image buffer
// ft_bzero sets all bytes to 0, sets entire image buffer to black
void	draw_map(t_map *map, t_fdf *fdf, t_point **arr)
{
	int x;
	int y;

	ft_bzero(fdf->img->addr, HEIGHT * WIDTH * (fdf->img->bits_per_pixel / 8)); //clear image
	//printf("Drawing...\n");
	// printf("2 row: %d, column: %d\n", map->row, map->column);
	y = 0;
	while(y < map->row)
	{
		x = 0;
		while(x < map->column)
		{
			t_point p1 = ft_scale(arr[y][x], map); //project the current point
			// printf("p1: %d\n", p1.x);
			if(x < map->column - 1) //draw to the right until the last
			{
				t_point p3 = ft_scale(arr[y][x + 1], map);
				// printf("p1x: %d, p3x: %d\n", p1.x, p3.x);
				draw_line_bresenham(fdf->img, &p1, &p3);
			}
			if(y < map->row - 1) //draw to downwards
			{
				t_point p2 = ft_scale(arr[y + 1][x], map);
				// printf("p1y: %d, p3y: %d\n", p1.y, p2.y);
				draw_line_bresenham(fdf->img, &p1, &p2);
			}
			x++; //Move to the right
		}
		y++; //Move down to next line
	}
}

void slope_less_than_one(t_point *begin, t_point *end, int *dx, int *dy, t_img *img)
{
	int p;
	int i;
	(void)end;

	 i = 0;
	 p = 2 * abs(*dy) - abs(*dx);
	 my_mlx_pixel_put(img, begin->x, begin->y, DEFAULT_COLOR);
	 while (i < abs(*dx))
	 {
		if((*dx) > 0)
	  		begin->x += 1;
		else
			begin->x -= 1;
		//printf("beginx: %d\n", begin->x);
	  if (p < 0)
	   p = p + 2 * abs(*dy);
	  else
	  {
		if ((*dy) > 0)
			begin->y += 1;
		else
			begin->y -= 1;
		//printf("beginy: %d\n", begin->y);
	   	p = p + 2 * abs(*dy) - 2 * abs(*dx);
	  }
	  my_mlx_pixel_put(img, begin->x, begin->y, DEFAULT_COLOR);
	  i++;
	 }
	// int p;
	// int x;
	// int y;

	// p = 2 * (*dy) - (*dx);
	// x = begin->x;
	// y = begin->y;
	// while (x <= end->x)
	// {
	// 	my_mlx_pixel_put(img, x, y, begin->color);
	// 	x++;
	// 	if (p < 0)
	// 		p += 2 * (*dy);
	// 	else
	// 	{
	// 		p += 2 * (*dy) - 2 * (*dx);
	// 		y++;
	// 	}
	// }
}

void slope_bigger_than_one(t_point *begin, t_point *end, int *dx, int *dy, t_img *img)
{
	int p;
	int i;
	(void)end;

	printf("[2]dx2: %d, dy2: %d\n", *dx, *dy);
	i = 0;
	p = 2 * abs(*dx) - abs(*dy);
	// printf("beginx: %d, begin.y: %d\n", begin->x, begin->y);
	my_mlx_pixel_put(img, begin->x, begin->y, DEFAULT_COLOR);
	if (*dx == 0)
	{
		int y = begin->y;
		int end_y = end->y;
		int step = (*dy > 0) ? 1 : -1;
		while(y != end_y)
		{
			my_mlx_pixel_put(img, begin->x, y, DEFAULT_COLOR);
			y += step;
		}
		my_mlx_pixel_put(img, begin->x, end_y, DEFAULT_COLOR);
		return ;
	}
	while (i < abs(*dy))
	{
		if((*dy) > 0)
			begin->y += 1;
		else if ((*dy) < 0)
			begin->y -= 1;
		// printf("beginy: %d\n", begin->y);
		if (p < 0)
			p = p + 2 * abs(*dx);
		else
		{
			if ((*dx) > 0)
				begin->x += 1;
			else if ((*dx) < 0)
				begin->x -= 1;
			// printf("beginx: %d\n", begin->x);
			p = p + 2 * abs(*dx) - 2 * abs(*dy);
		}
		// printf("p: %d\n", p);
		// printf("beginx2: %d, beginy2: %d\n", begin->x, begin->y);
		my_mlx_pixel_put(img, begin->x, begin->y, DEFAULT_COLOR);
		i++;
	}
	// int p;
	// int x;
	// int y;

	// p = 2 * (*dx) - (*dy);
	// x = begin->x;
	// y = begin->y;
	// while (y <= end->y)
	// {
	// 	my_mlx_pixel_put(img, x, y, begin->color);
	// 	y++;
	// 	if (p < 0)
	// 		p += 2 * (*dx);
	// 	else
	// 	{
	// 		p += 2 * (*dx) - 2 * (*dy);
	// 		x++;
	// 	}
	// }
}

void	draw_line_bresenham(t_img *img, t_point *begin, t_point *end)
{
	int dx;
	int dy;

	dx = (end->x - begin->x); // abs (returns positive number) using stdlib.h, forbidden -- need to create a new function
	dy = (end->y - begin->y);
	printf("[1]dx: %d, dy: %d\n", dx, dy);
	if (abs(dx) > abs(dy))
		slope_less_than_one(begin, end, &dx, &dy, img); //shallow lines
	else
		slope_bigger_than_one(begin, end, &dx, &dy, img); //steep lines

}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
