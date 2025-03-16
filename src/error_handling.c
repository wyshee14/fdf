/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:28:21 by wshee             #+#    #+#             */
/*   Updated: 2025/03/16 20:54:09 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	error_and_exit(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

void	free_tpoint_arr(t_point **arr, t_map *map)
{
	int	i;
	int	rows;

	i = 0;
	if (arr)
	{
		if (map)
			rows = map->row;
		else
			rows = 0;
		while (i < rows)
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_map(t_map *map)
{
	if (map)
	{
		free(map);
		map = NULL;
	}
}

void	free_img(t_fdf *fdf)
{
	if (fdf->img)
	{
		if (fdf->mlx && fdf->img->img)
			mlx_destroy_image(fdf->mlx, fdf->img->img);
		free(fdf->img);
		fdf->img = NULL;
	}
}

// Free array first (since it depends on map->row)
// Set to NULL to avoid double free
// mlx_do_sync ensures that all pending drawing operations are processed
// before we destroy the MLX instance.
// It forces the MiniLibX display buffer to sync with what has been rendered.
// mlx_destroy_display cleans display resources allocated by MiniLibX
// but does not free the MLX instance
// at last need to free fdf->mlx manual
void	free_all(t_fdf *fdf)
{
	if (!fdf)
		return ;
	free_tpoint_arr(fdf->arr, fdf->map);
	if (fdf->move)
	{
		free(fdf->move);
		fdf->move = NULL;
	}
	free_map(fdf->map);
	free_img(fdf);
	if (fdf->mlx && fdf->win)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		fdf->win = NULL;
	}
	if (fdf->mlx)
	{
		mlx_do_sync(fdf->mlx);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
		fdf->mlx = NULL;
	}
}
