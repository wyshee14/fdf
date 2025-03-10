/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:12:17 by wshee             #+#    #+#             */
/*   Updated: 2025/03/10 21:32:00 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

//assign another pointer current to prevent moving begin when we get the color
//and to track the distance in between the two points
void	draw_horizontal_line(t_point *current, t_draw *draw, t_img *img)
{
	int	step;

	step = 1;
	if (draw->dx < 0)
		step = -1;
	while (current->x != draw->end.x)
	{
		current->color = get_gradient_color(current, draw);
		my_mlx_pixel_put(img, current->x, draw->begin.y, current->color);
		current->x += step;
	}
	my_mlx_pixel_put(img, draw->end.x, draw->end.y, draw->end.color);
	return ;
}

// for shallow line where dx > dy
// plot the pixel by incrementing x
void	slope_less_than_one(t_draw *draw, t_img *img)
{
	t_point	current;

	current = draw->begin;
	if (draw->dy == 0)
		draw_horizontal_line(&current, draw, img);
	while (current.x != draw->end.x || current.y != draw->end.y)
	{
		current.color = get_gradient_color(&current, draw);
		my_mlx_pixel_put(img, current.x, current.y, current.color);
		if (draw->dx > 0)
			current.x += 1;
		else
			current.x -= 1;
		if (draw->p < 0)
			draw->p = draw->p + 2 * abs(draw->dy);
		else
		{
			if (draw->dy > 0)
				current.y += 1;
			else
				current.y -= 1;
			draw->p = draw->p + 2 * abs(draw->dy) - 2 * abs(draw->dx);
		}
	}
	my_mlx_pixel_put(img, draw->end.x, draw->end.y, draw->end.color);
}

void	draw_vertical_line(t_point *current, t_draw *draw, t_img *img)
{
	int	step;

	step = 1;
	if (draw->dy < 0)
		step = -1;
	while (current->y != draw->end.y)
	{
		current->color = get_gradient_color(current, draw);
		my_mlx_pixel_put(img, current->x, current->y, current->color);
		current->y += step;
	}
	my_mlx_pixel_put(img, draw->end.x, draw->end.y, draw->end.color);
	return ;
}

// for steep line where dy > dx
// plot the pixel by incrementing y
void	slope_bigger_than_one(t_draw *draw, t_img *img)
{
	t_point	current;

	current = draw->begin;
	if (draw->dx == 0)
		draw_vertical_line(&current, draw, img);
	while (current.x != draw->end.x || current.y != draw->end.y)
	{
		current.color = get_gradient_color(&current, draw);
		my_mlx_pixel_put(img, current.x, current.y, current.color);
		if (draw->dy > 0)
			current.y += 1;
		else if (draw->dy < 0)
			current.y -= 1;
		if (draw->p < 0)
			draw->p = draw->p + 2 * abs(draw->dx);
		else
		{
			if (draw->dx > 0)
				current.x += 1;
			else if (draw->dx < 0)
				current.x -= 1;
			draw->p = draw->p + 2 * abs(draw->dx) - 2 * abs(draw->dy);
		}
	}
	my_mlx_pixel_put(img, draw->end.x, draw->end.y, draw->end.color);
}

// abs (returns positive number) using stdlib.h, forbidden
// -- need to create a new function
void	draw_line_bresenham(t_img *img, t_draw *draw)
{
	draw->dx = (draw->end.x - draw->begin.x);
	draw->dy = (draw->end.y - draw->begin.y);
	if (abs(draw->dx) > abs(draw->dy))
	{
		draw->p = 2 * abs(draw->dy) - abs(draw->dx);
		slope_less_than_one(draw, img);
	}
	else
	{
		draw->p = 2 * abs(draw->dx) - abs(draw->dy);
		slope_bigger_than_one(draw, img);
	}
}
