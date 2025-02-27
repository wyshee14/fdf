/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:14:58 by wshee             #+#    #+#             */
/*   Updated: 2025/02/27 17:44:52 by wshee            ###   ########.fr       */
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
	if (key == XK_plus || key == XK_minus)
		zoom(key,fdf);
	return(0);
}

int key_release(int key, t_fdf *fdf)
{
	if (key == XK_Shift_L || key == XK_Shift_R)
		fdf->shift_pressed = 0;
	return(0);
}

void zoom(int key, t_fdf *fdf)
{
	if (key == XK_Shift_L || key == XK_Shift_R)
		fdf->shift_pressed = 1;
	if (key == XK_equal && fdf->shift_pressed == 1)
		fdf->move->scale += 1;
	if (key == XK_minus && fdf->shift_pressed == 1)
		fdf->move->scale -= 1;
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
	mlx_hook(fdf->win, 3, 1L<<1, key_release, fdf);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
}
