/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:34:05 by wshee             #+#    #+#             */
/*   Updated: 2025/03/10 21:39:32 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// to calculate the distance travelled between two points
// x - x1 is the current position travelled
// x2 - x1 is the total distance travelled
float	fraction(float x1, float x2, float x)
{
	if (x1 != x2)
		return ((x - x1) / (x2 - x1));
	return (0);
}

// 0xRRGGBB (24 bit color) is a base 16 notation(hexadecimal)
// RR (bits 16-23), GG(bits 8-15), BB(bits 0-7)
// using binary to extract a portion of the integer
// return using OR operation to combine them back to one integer
int	color_gradient(t_point *begin, t_point *end, float *distance)
{
	int	r;
	int	g;
	int	b;

	r = ((begin->color >> 16) & 0xFF) + (*distance) * ((end->color >> 16 & 0xFF)
			- ((begin->color >> 16) & 0xFF));
	g = ((begin->color >> 8) & 0xFF) + (*distance) * ((end->color >> 8 & 0xFF)
			- ((begin->color >> 8) & 0xFF));
	b = (begin->color & 0xFF) + (*distance) * ((end->color & 0xFF)
			- (begin->color & 0xFF));
	return ((r << 16) | (g << 8) | b);
}

int	get_gradient_color(t_point *current, t_draw *draw)
{
	float	position;
	int		color;

	if (draw->begin.color == draw->end.color)
		return (draw->begin.color);
	if (abs(draw->dx) > abs(draw->dy))
		position = fraction(draw->begin.x, draw->end.x, current->x);
	else
		position = fraction(draw->begin.y, draw->end.y, current->y);
	color = color_gradient(&draw->begin, &draw->end, &position);
	return (color);
}
