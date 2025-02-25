#include "../include/fdf.h"

float	fraction(float x1, float x2, float x)
{
	if (x1 != x2)
		return((x - x1) / (x2 - x1));
	return(0);
}

int color_gradient(t_point *begin, t_point *end, float *distance)
{
	int r = ((begin->color >> 16) & 0xFF) + (*distance) * (((end->color >> 16) & 0xFF) - ((begin->color >> 16) & 0xFF));
	int g = ((begin->color >> 8) & 0xFF) + (*distance) * (((end->color >> 8) & 0xFF) - ((begin->color >> 8) & 0xFF));
	int b = (begin->color & 0xFF) + (*distance) * ((end->color & 0xFF) - (begin->color & 0xFF));
	return (r << 16 | (g << 8) | b);
}

int get_gradient_color(t_point *current, t_point *begin, t_point *end, int *dx, int *dy)
{
	float position;
	int color;

	if (begin->color == end->color)
		return(begin->color);
	if (abs(*dx) > abs(*dy))
		position = fraction(begin->x, end->x, current->x);
	else
		position = fraction(begin->y, end->y, current->y);
	color = color_gradient(begin, end, &position);
	return(color);
}