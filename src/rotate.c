/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:29:41 by wshee             #+#    #+#             */
/*   Updated: 2025/03/03 21:01:43 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	rotate_x(t_point *a, t_move *move)
{
	int prev_y;

	prev_y = a->y;
	a->y = prev_y * cos(move->gamma_z) - a->z * sin(move->gamma_z);
	a->z = prev_y * sin(move->gamma_z) + cos(move->gamma_z);
}

void	rotate_y(t_point *a, t_move *move)
{
	int prev_x;

	prev_x = a->x;
	a->x = prev_x * cos(move->tetha_y) + a->z * sin(move->tetha_y);
	a->z = a->z * cos(move->tetha_y) - prev_x * sin(move->tetha_y);
}

void	rotate_z(t_point *a, t_move *move)
{
	int prev_x;

	prev_x = a->x;
	a->x = prev_x * cos(move->alpha_x) - a->y * sin(move->alpha_x);
	a->y = prev_x * sin(move->alpha_x) + a->y * cos(move->alpha_x);
}
