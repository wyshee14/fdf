/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:48:18 by wshee             #+#    #+#             */
/*   Updated: 2025/02/26 21:48:06 by wshee            ###   ########.fr       */
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

void	rotate_z(t_point *point)
{
	double rad_45 = M_PI / 4;
	double prev_x = point->x;
	double prev_y = point->y;
	point->x = prev_x * cos(rad_45) - prev_y * sin(rad_45);
	point->y = prev_x * sin(rad_45) + prev_y * cos(rad_45);
}

void	rotate_x(t_point *point)
{
	//double rad = atan(sqrt(2));
	double cos_theta = 1 / sqrt(3);
	double sin_theta = sqrt(2) / sqrt(3);

	point->y = point->y * cos_theta - point->z * sin_theta;
	point->z = point->y * sin_theta + point->z * cos_theta;
}

t_point	ft_scale(t_point point, t_fdf *fdf)
{
	// (void)map;

	//printf("Ori point: x[%d], y[%d], z[%d]\n", point.x, point.y, point.z);
	point.x *= fdf->move->scale;
	point.y *= fdf->move->scale;
	point.z *= fdf->move->scale;
	//centre of the map become the new origin (0,0)
	point.x -= (fdf->map->column * fdf->move->scale) / 2;
	point.y -= (fdf->map->row * fdf->move->scale) / 2;
	//convert to isometric
	isometric_projection(&point);
	// printf("Transformed  x: %d, y: %d, z: %d\n", point.x, point.y, point.z);
	// printf("py: %d\n", point.y);
	// printf("Before projection: x=%d, y=%d, z=%d\n", point.x, point.y, point.z);
	// rotate_z(&point);
	// rotate_x(&point);
	// printf("After projection: x=%d, y=%d, z=%d\n", point.x, point.y, point.z);
	//move to centre
	point.x += fdf->move->offset_x;
	point.y += fdf->move->offset_y;
	// printf("[2] p1: %d\n", point.x);
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
int	draw_map(t_fdf *fdf)
{
	int x;
	int y;

	ft_bzero(fdf->img->addr, HEIGHT * WIDTH * (fdf->img->bits_per_pixel / 8)); //clear image
	//printf("Drawing...\n");
	// printf("2 row: %d, column: %d\n", map->row, map->column);
	y = 0;
	while(y < fdf->map->row)
	{
		x = 0;
		while(x < fdf->map->column)
		{
			t_point p1 = ft_scale(fdf->arr[y][x], fdf); //project the current point
			// printf("p1: %d\n", p1.x);
			if(x != fdf->map->column - 1) //draw to the right until the last
			{
				t_point p3 = ft_scale(fdf->arr[y][x + 1], fdf);
				// printf("p1x: %d, p3x: %d\n", p1.x, p3.x);
				draw_line_bresenham(fdf->img, &p1, &p3);
			}
			if(y != fdf->map->row - 1) //draw to downwards
			{
				t_point p2 = ft_scale(fdf->arr[y + 1][x], fdf);
				// printf("p1y: %d, p3y: %d\n", p1.y, p2.y);
				draw_line_bresenham(fdf->img, &p1, &p2);
			}
			x++; //Move to the right
		}
		y++; //Move down to next line
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	return(0);
}

void slope_less_than_one(t_point *begin, t_point *end, int *dx, int *dy, t_img *img)
{
	int p;
	//int i;
	(void)end;
	t_point current = *begin;

	//i = 0;
	p = 2 * abs(*dy) - abs(*dx);
	if (*dy == 0)
	{
		int end_x = end->x;
		int step = (*dx > 0) ? 1 : -1;
		while(current.x != end_x)
		{
			current.color = get_gradient_color(&current, begin, end, dx, dy);
			my_mlx_pixel_put(img, current.x, begin->y, current.color);
			current.x += step;
		}
		// printf("[2]beginx: %d, beginy: %d\n", end_x, begin->y);
		my_mlx_pixel_put(img, end_x, end->y, end->color);
		return ;
	}
	// printf("begin: x[%d], y[%d]", begin->x, begin->y);
	// printf("current: x[%d], y[%d]", current.x, current.y);
	while (current.x != end->x || current.y != end->y)
	{
		current.color = get_gradient_color(&current, begin, end, dx, dy);
		my_mlx_pixel_put(img, current.x, current.y, current.color);
		if((*dx) > 0)
		current.x += 1;
		else
		current.x -= 1;
		//printf("beginx: %d\n", begin->x);
		if (p < 0)
		p = p + 2 * abs(*dy);
	  	else
	  	{
			if ((*dy) > 0)
			current.y += 1;
			else
			current.y -= 1;
			//printf("beginy: %d\n", begin->y);
			p = p + 2 * abs(*dy) - 2 * abs(*dx);
		}
		// my_mlx_pixel_put(img, current.x, current.y, DEFAULT_COLOR);
	  	// i++;
	 }
	my_mlx_pixel_put(img, end->x, end->y, end->color);
}

void	slope_bigger_than_one(t_point *begin, t_point *end, int *dx, int *dy, t_img *img)
{
	int p;
	// int i;
	(void)end;
	t_point current = *begin;

	// printf("[2]dx2: %d, dy2: %d\n", *dx, *dy);
	// i = 0;
	p = 2 * abs(*dx) - abs(*dy);
	// printf("[1]beginx: %d, begin.y: %d\n", begin->x, begin->y);
	if (*dx == 0)
	{
		int end_y = end->y;
		int step = (*dy > 0) ? 1 : -1;
		while(current.y != end_y)
		{
			current.color = get_gradient_color(&current, begin, end, dx, dy);
			my_mlx_pixel_put(img, current.x, current.y, current.color);
			current.y += step;
		}
		// printf("[2]beginx: %d, beginy: %d\n", begin->x, end_y);
		my_mlx_pixel_put(img, end->x, end_y, end->color);
		return ;
	}
	while (current.x != end->x || current.y != end->y)
	{
		current.color = get_gradient_color(&current, begin, end, dx, dy);
		my_mlx_pixel_put(img, current.x, current.y, current.color);
		if((*dy) > 0)
		current.y += 1;
		else if ((*dy) < 0)
		current.y -= 1;
		// printf("beginy: %d\n", begin->y);
		if (p < 0)
		p = p + 2 * abs(*dx);
		else
		{
			if ((*dx) > 0)
			current.x += 1;
			else if ((*dx) < 0)
			current.x -= 1;
			// printf("beginx: %d\n", begin->x);
			p = p + 2 * abs(*dx) - 2 * abs(*dy);
		}
		//my_mlx_pixel_put(img, current.x, current.y, DEFAULT_COLOR);
		// printf("p: %d\n", p);
		//printf("[2]beginx: %d, beginy: %d\n", begin->x, begin->y);
		// i++;
	}
	my_mlx_pixel_put(img, end->x, end->y, end->color);
}



void	draw_line_bresenham(t_img *img, t_point *begin, t_point *end)
{
	int dx;
	int dy;
	//int distance;

	// printf("beginx: %d, begin.y: %d\n", begin->x, begin->y);
	dx = (end->x - begin->x); // abs (returns positive number) using stdlib.h, forbidden -- need to create a new function
	dy = (end->y - begin->y);
	//distance = get_max_distance(&dx, &dy);
	// printf("[1]dx: %d, dy: %d\n", dx, dy);
	if (abs(dx) > abs(dy))
	{
		slope_less_than_one(begin, end, &dx, &dy, img); //shallow lines
	}
	else
	{
		slope_bigger_than_one(begin, end, &dx, &dy, img); //steep lines
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	if (!img || !img->addr)
		error_and_exit("Error: Invalid image pointer\n");
	if(x < 0 || y < 0|| x >= WIDTH || y >= HEIGHT)
		return ;
		// error_and_exit("Error: image drawing out of bound\n");
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
