/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:14:58 by wshee             #+#    #+#             */
/*   Updated: 2025/03/01 18:14:45 by wshee            ###   ########.fr       */
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
	// if (key == XK_Pointer_Button4 || key == XK_Pointer_Button5)
	// 	zoom(key,fdf);
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

void zoom(int button, t_fdf *fdf)
{
	// if (key == XK_Shift_L || key == XK_Shift_R)
	// 	fdf->shift_pressed = 1;
	if (button == Button4)
	{
		printf("Button: %d\n", button);
		fdf->move->scale += 1;
	}
	if (button == Button5)
	{
		printf("Button: %d\n", button);
		fdf->move->scale -= 1;
	}
	draw_map(fdf);
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
