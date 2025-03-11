/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:48:18 by wshee             #+#    #+#             */
/*   Updated: 2025/03/11 22:41:42 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	clear_image(fdf);
	y = 0;
	while (y < fdf->map->row)
	{
		x = 0;
		while (x < fdf->map->column)
		{
			draw_array_grid(fdf, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	return (0);
}

// p1 is the begin point and scale before draw
// x draw to the right until the last column
// y draw to downwards until the last row
void	draw_array_grid(t_fdf *fdf, int x, int y)
{
	t_draw	draw;

	ft_memset(&draw, 0, sizeof(t_draw));
	draw.begin = ft_scale(fdf->arr[y][x], fdf);
	if (x != fdf->map->column - 1)
	{
		draw.end = ft_scale(fdf->arr[y][x + 1], fdf);
		draw_line_bresenham(fdf->img, &draw);
	}
	if (y != fdf->map->row - 1)
	{
		draw.end = ft_scale(fdf->arr[y + 1][x], fdf);
		draw_line_bresenham(fdf->img, &draw);
	}
}

void	isometric_projection(t_point *point)
{
	double	iso_radian;
	int		previous_x;

	previous_x = point->x;
	iso_radian = 30 * M_PI / 180;
	point->x = (previous_x - point->y) * cos(iso_radian);
	point->y = ((previous_x + point->y) * sin(iso_radian)) - (point->z);
}

// 1. zoom the point to according to its scale
// 2. centre of the map become the new origin (0,0)
// 3. convert to isometric
// 4. move to centre of window
t_point	ft_scale(t_point point, t_fdf *fdf)
{
	point.x *= fdf->move->scale;
	point.y *= fdf->move->scale;
	point.z *= fdf->move->scale * fdf->move->z_factor;
	// printf("z[%f]\n", point.z);
	point.x -= (fdf->map->column * fdf->move->scale) / 2;
	point.y -= (fdf->map->row * fdf->move->scale) / 2;
	if (fdf->move->is_iso == 1)
		isometric_projection(&point);
	rotate_x(&point, fdf->move);
	rotate_y(&point, fdf->move);
	rotate_z(&point, fdf->move);
	point.x += WIDTH / 2 + fdf->move->offset_x;
	point.y += HEIGHT / 2 + fdf->move->offset_y;
	return (point);
}
