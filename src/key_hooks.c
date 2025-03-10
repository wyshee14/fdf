/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:14:58 by wshee             #+#    #+#             */
/*   Updated: 2025/03/05 21:35:19 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int close_window(t_fdf *fdf)
{
	// if (fdf->win)
	// {
	// 	mlx_destroy_window(fdf->mlx, fdf->win);
	// 	mlx_destroy_display(fdf->mlx);
	// 	fdf->win = NULL;
	// }
	if(fdf)
	{
		free_all(fdf);
		fdf = NULL;
	}
	exit(0);
	return(0);
}

int key_press(int key, t_fdf *fdf)
{
	if(key == ESC_KEY)
		close_window(fdf);
	if (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right)
		move(key, fdf);
	if (key == XK_equal || key == XK_minus)
		zoom(key,fdf);
	if (key == XK_1 || key == XK_2 || key == XK_3 || key == XK_7 || key == XK_8 || key == XK_9)
		rotate(key,fdf);
	if (key == XK_p || key == XK_i)
		projection_pressed(key, fdf);
	if (key == XK_space)
		change_colour(key,fdf);
	if (key == XK_z || key == XK_x)
		elevation(key, fdf);
	return(0);
}

// int key_release(int key, t_fdf *fdf)
// {
// 	if (key == XK_Shift_L || key == XK_Shift_R)
// 		fdf->shift_pressed = 0;
// 	return(0);
// }

void	elevation(int key, t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	while(i < fdf->map->row)
	{
		j = 0;
		while(j < fdf->map->column)
		{
			if (key == XK_z)
				fdf->move->z_factor += 0.1;
				//fdf->arr[i][j].z *= 2;
			else if(key == XK_x)
				fdf->arr[i][j].z -= 0.1;
			j++;
		}
		i++;
	}
}

void	change_colour(int key, t_fdf *fdf)
{
	int i;
	int j;

	if (key == XK_space)
	{
		i = 0;
		while (i < fdf->map->row)
		{
			j = 0;
			while(j < fdf->map->column)
			{
				if (!fdf->move->color_switch)
				{
					if (fdf->arr[i][j].z <= 0)
					{
						// printf("[%d][%d] z: %d\n", i, j, fdf->arr[i][j].z);
						fdf->arr[i][j].color = COLOR1;
					}
					else
						fdf->arr[i][j].color = COLOR2;
				}
				else
					fdf->arr[i][j].color = fdf->arr[i][j].ori_color;
				j++;
			}
			i++;
		}
		fdf->move->color_switch = !fdf->move->color_switch;
	}
}

void projection_pressed(int key, t_fdf *fdf)
{
	if (key == XK_i)
	{
		fdf->move->is_iso = 1;
		fdf->move->alpha_x = 0;
		fdf->move->tetha_y = 0;
		fdf->move->gamma_z = 0;
	}
	if (key == XK_p)
	{
		fdf->move->is_iso = 0;
		fdf->move->alpha_x = 0;
		fdf->move->tetha_y = 0;
		fdf->move->gamma_z = 0;
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
	double rad;
	double rad2;

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

// key123 rotate in positive direction
// key789 rotate in opposite direction
void	rotate(int key, t_fdf *fdf)
{
	if (key == XK_1)
		fdf->move->gamma_z += 0.1;
	if (key == XK_2)
		fdf->move->tetha_y += 0.1;
	if (key == XK_3)
		fdf->move->alpha_x += 0.1;
	if (key == XK_7)
		fdf->move->gamma_z -= 0.1;
	if (key == XK_8)
		fdf->move->tetha_y -= 0.1;
	if (key == XK_9)
		fdf->move->alpha_x -= 0.1;
}

void zoom(int key, t_fdf *fdf)
{
	if (key == XK_equal)
		fdf->move->scale += 1;
	if (key == XK_minus)
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
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
}
