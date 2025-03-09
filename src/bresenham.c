#include "../include/fdf.h"

//assign another pointer current to prevent moving begin when we get the color
//and to track the distance in between the two points
void draw_horizontal_line(t_point *current, t_point *begin, t_point *end, t_draw *draw, t_img *img)
{
	int step;

	step = 1;
	if (draw->dx < 0) 
		step = -1;
	while(current->x != end->x)
	{
		current->color = get_gradient_color(current, begin, end, draw);
		my_mlx_pixel_put(img, current->x, begin->y, current->color);
		current->x += step;
	}
	my_mlx_pixel_put(img, end->x, end->y, end->color);
	return ;
}

void slope_less_than_one(t_point *begin, t_point *end, t_draw *draw, t_img *img)
{
	t_point current;
	
	current = *begin;
	if (draw->dy == 0)
		draw_horizontal_line(&current, begin, end, draw, img);
	while (current.x != end->x || current.y != end->y)
	{
		current.color = get_gradient_color(&current, begin, end, draw);
		my_mlx_pixel_put(img, current.x, current.y, current.color);
		if((draw->dx) > 0)
			current.x += 1;
		else
			current.x -= 1;
		if (draw->p < 0)
			draw->p = draw->p + 2 * abs(draw->dy);
	  	else
	  	{
			if ((draw->dy) > 0)
				current.y += 1;
			else
				current.y -= 1;
			draw->p = draw->p + 2 * abs(draw->dy) - 2 * abs(draw->dx);
		}
	 }
	my_mlx_pixel_put(img, end->x, end->y, end->color);
}

void	draw_vertical_line(t_point *current, t_point *begin, t_point *end, t_draw *draw, t_img *img)
{
		int step;
		
		step = 1;
		if (draw->dy < 0) 
			step = -1;
		while(current->y != end->y)
		{
			current->color = get_gradient_color(current, begin, end, draw);
			my_mlx_pixel_put(img, current->x, current->y, current->color);
			current->y += step;
		}
		my_mlx_pixel_put(img, end->x, end->y, end->color);
		return ;
}

void	slope_bigger_than_one(t_point *begin, t_point *end, t_draw *draw, t_img *img)
{
	t_point current;
	
	current = *begin;
	if (draw->dx == 0)
		draw_vertical_line(&current, begin, end, draw, img);
	while (current.x != end->x || current.y != end->y)
	{
		current.color = get_gradient_color(&current, begin, end, draw);
		my_mlx_pixel_put(img, current.x, current.y, current.color);
		if(draw->dy > 0)
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
	my_mlx_pixel_put(img, end->x, end->y, end->color);
}

// abs (returns positive number) using stdlib.h, forbidden -- need to create a new function
void	draw_line_bresenham(t_img *img, t_point *begin, t_point *end)
{
	t_draw draw;
	
	ft_memset(&draw, 0, sizeof(t_draw));
	draw.dx = (end->x - begin->x); 
	draw.dy = (end->y - begin->y);
	if (abs(draw.dx) > abs(draw.dy))
	{
		draw.p = 2 * abs(draw.dy) - abs(draw.dx);
		slope_less_than_one(begin, end, &draw, img); //shallow lines
	}
	else
	{
		draw.p = 2 * abs(draw.dx) - abs(draw.dy);
		slope_bigger_than_one(begin, end, &draw, img); //steep lines
	}
}
