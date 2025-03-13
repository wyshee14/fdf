/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:29:41 by wshee             #+#    #+#             */
/*   Updated: 2025/03/13 14:55:45 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	rotate_x(t_point *a, t_move *move)
{
	int	prev_y;

	prev_y = a->y;
	a->y = prev_y * cos(move->alpha_x) + a->z * sin(move->alpha_x);
	a->z = prev_y * -sin(move->alpha_x) + a->z * cos(move->alpha_x);
}

void	rotate_y(t_point *a, t_move *move)
{
	int	prev_x;

	prev_x = a->x;
	a->x = prev_x * cos(move->tetha_y) + a->z * sin(move->tetha_y);
	a->z = prev_x * -sin(move->tetha_y) + a->z * cos(move->tetha_y);
}

void	rotate_z(t_point *a, t_move *move)
{
	int	prev_x;

	prev_x = a->x;
	a->x = prev_x * cos(move->gamma_z) - a->y * sin(move->gamma_z);
	a->y = prev_x * sin(move->gamma_z) + a->y * cos(move->gamma_z);
}
