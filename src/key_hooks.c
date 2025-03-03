/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:14:58 by wshee             #+#    #+#             */
/*   Updated: 2025/03/03 22:21:33 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int close_window(t_fdf *fdf)
{
	if (fdf->win)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		fdf->win = NULL;
	}
	exit(0);
	return(0);
}

int key_press(int key, t_fdf *fdf)
{
	if(key == ESC_KEY)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		fdf->win = NULL;
		exit(0);
	}
	if (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right)
		move(key, fdf);
	if (key == XK_equal || key == XK_minus)
		zoom(key,fdf);
	if (key == XK_1 || key == XK_2 || key == XK_3)
		rotate(key,fdf);
	if (key == XK_p)
		projection_pressed(key, fdf);
	return(0);
}

int key_release(int key, t_fdf *fdf)
{
	if (key == XK_Shift_L || key == XK_Shift_R)
		fdf->shift_pressed = 0;
	return(0);
}

int mouse_scroll(int button, t_fdf *fdf)
{
	if (button == Button4 || button == Button5)
		zoom(button,fdf);
	return (0);
}

void projection_pressed(int key, t_fdf *fdf)
{
	if (key == XK_p)
	{
		if (fdf->move->projection == 0)
			fdf->move->projection = 1;
		else if (fdf->move->projection == 1)
			fdf->move->projection = 2;
		else if (fdf->move->projection == 2)
			fdf->move->projection = 0;
		projection_type(key, fdf);
	}
}

void	projection_type(int key, t_fdf *fdf)
{
	(void)key;
	double rad;
	double rad2;

	rad = 90 * M_PI / 180;
	rad2 = 270 * M_PI / 180;
	printf("Projection value: %d\n", fdf->move->projection);
	if (fdf->move->projection == TOP_VIEW)
	{
		fdf->move->alpha_x = 0;
		fdf->move->tetha_y = 0;
		fdf->move->gamma_z = 0;
	}
	if (fdf->move->projection == FRONT_VIEW)
	{
		fdf->move->alpha_x = rad;
		fdf->move->tetha_y = 0;
		fdf->move->gamma_z = 0;
	}
	if (fdf->move->projection == RIGHT_SIDE_VIEW)
	{
		fdf->move->alpha_x = 0;
		fdf->move->tetha_y = rad;
		fdf->move->gamma_z = rad2;
	}
}

void	rotate(int key, t_fdf *fdf)
{
	if (key == XK_1)
	{
		fdf->move->gamma_z += 0.1;
		//printf("gamma: %f\n", fdf->move->gamma_z);
	}
	if (key == XK_2)
		fdf->move->tetha_y += 0.1;
	if (key == XK_3)
		fdf->move->alpha_x += 0.1;
}

void zoom(int key, t_fdf *fdf)
{
	if (key == XK_equal)
	{
		// printf("Button: %d\n", button);
		fdf->move->scale += 1;
	}
	if (key == XK_minus)
	{
		// printf("Button: %d\n", button);
		fdf->move->scale -= 1;
	}
	// draw_map(fdf);
}

void	move(int key, t_fdf *fdf)
{
	if (key == XK_Up)
		fdf->move->offset_y -= MOVE_STEP;
	if (key == XK_Down)
		fdf->move->offset_y += MOVE_STEP;
	if (key == XK_Left)
		fdf->move->offset_x -= MOVE_STEP;
	if (key == XK_Right)
		fdf->move->offset_x += MOVE_STEP;
	//draw_map(fdf);
}

void	setup_hook(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, draw_map,fdf);
	mlx_hook(fdf->win, 2, 1L<<0, key_press, fdf);
	mlx_hook(fdf->win, 4, 1L<<2, mouse_scroll, fdf);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
}
