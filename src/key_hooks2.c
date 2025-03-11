/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:38:47 by wshee             #+#    #+#             */
/*   Updated: 2025/03/11 21:47:44 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

void	zoom(int key, t_fdf *fdf)
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
}

void	change_colour(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map->row)
	{
		j = 0;
		while (j < fdf->map->column)
		{
			if (!fdf->move->color_switch)
			{
				if (fdf->arr[i][j].z <= 0)
					fdf->arr[i][j].color = COLOR1;
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

void	elevation(int key, t_fdf *fdf)
{
	if (key == XK_z)
		fdf->move->z_factor += 0.1;
	if (key == XK_x)
		fdf->move->z_factor -= 0.1;
}
