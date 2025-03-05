/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:28:21 by wshee             #+#    #+#             */
/*   Updated: 2025/03/05 18:47:34 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/fdf.h"

void	free_2d_array(void **arr)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
	{
		if(arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void error_and_exit(char *message)
{
	perror(message);
	// if (fdf)
	// 	free_all(fdf);
	exit(1);
}

void	free_tpoint_arr(t_point **arr, t_map *map)
{
	if (arr)
	{
		int rows;

		if (map)
			rows = map->row;
		else
			rows = 0;
		for (int i = 0; i < rows; i++)
        {
            if (arr[i])
                free(arr[i]);
        }
        free(arr);
		// Set to NULL to avoid double free
		arr = NULL;
	}
}

void free_map(t_map *map)
{
	if (map)
	{
		free(map);
		map = NULL;
	}
}

void free_all(t_fdf *fdf)
{
	if (!fdf)
		return ;
	 // Free array first (since it depends on map->row)
	free_tpoint_arr(fdf->arr, fdf->map);
	if(fdf->move)
	{
		free(fdf->move);
		fdf->move = NULL;
	}
	free_map(fdf->map);
	if (fdf->img)
	{
		if(fdf->mlx && fdf->img->img)
			mlx_destroy_image(fdf->mlx, fdf->img->img);
		free(fdf->img);
		fdf->img = NULL;
	}
	if (fdf->mlx && fdf->win)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		fdf->win = NULL;
	}
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
		fdf->mlx = NULL;
	}
}
