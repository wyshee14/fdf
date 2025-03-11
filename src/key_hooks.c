/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:14:58 by wshee             #+#    #+#             */
/*   Updated: 2025/03/11 21:27:55 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	close_window(t_fdf *fdf)
{
	if (fdf)
	{
		free_all(fdf);
		fdf = NULL;
	}
	exit (0);
	return (0);
}

void	projection_pressed(int key, t_fdf *fdf)
{
	fdf->move->alpha_x = 0;
	fdf->move->tetha_y = 0;
	fdf->move->gamma_z = 0;
	if (key == XK_i)
		fdf->move->is_iso = 1;
	if (key == XK_p)
	{
		fdf->move->is_iso = 0;
		if (fdf->move->projection == 0)
			fdf->move->projection = 1;
		else if (fdf->move->projection == 1)
			fdf->move->projection = 2;
		else if (fdf->move->projection == 2)
			fdf->move->projection = 0;
		projection_type(fdf);
	}
}

void	projection_type(t_fdf *fdf)
{
	double	rad;
	double	rad2;

	rad = 90 * M_PI / 180;
	rad2 = 270 * M_PI / 180;
	if (fdf->move->projection == TOP_VIEW)
	{
		fdf->move->alpha_x = 0;
		fdf->move->tetha_y = 0;
		fdf->move->gamma_z = 0;
	}
	if (fdf->move->projection == FRONT_VIEW)
	{
		fdf->move->alpha_x = 0;
		fdf->move->tetha_y = 0;
		fdf->move->gamma_z = rad;
	}
	if (fdf->move->projection == RIGHT_SIDE_VIEW)
	{
		fdf->move->alpha_x = rad2;
		fdf->move->tetha_y = rad;
		fdf->move->gamma_z = 0;
	}
}

int	key_press(int key, t_fdf *fdf)
{
	if (key == XK_Escape)
		close_window(fdf);
	if (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right)
		move(key, fdf);
	if (key == XK_equal || key == XK_minus)
		zoom(key, fdf);
	if (key == XK_1 || key == XK_2 || key == XK_3
		|| key == XK_7 || key == XK_8 || key == XK_9)
		rotate(key, fdf);
	if (key == XK_p || key == XK_i)
		projection_pressed(key, fdf);
	if (key == XK_space)
		change_colour(fdf);
	if (key == XK_z || key == XK_x)
		elevation(key, fdf);
	return (0);
}

void	setup_hook(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, draw_map, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, key_press, fdf);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
}
