/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:28:21 by wshee             #+#    #+#             */
/*   Updated: 2025/03/05 17:53:29 by wshee            ###   ########.fr       */
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
	// free_all(fdf);
	exit(1);
}

void free_all(t_fdf *fdf)
{
	int rows;

	if (!fdf)
		return ;
	 // Free array first (since it depends on map->row)
	if (fdf->arr)
	{
		if (fdf->map)
			rows = fdf->map->row;
		else
			rows = 0;
		for (int i = 0; i < rows; i++)
        {
            if (fdf->arr[i])
                free(fdf->arr[i]);
        }
        free(fdf->arr);
		// Set to NULL to avoid double free
		fdf->arr = NULL;
	}
	if (fdf->img)
	{
		if(fdf->mlx && fdf->img->img)
			mlx_destroy_image(fdf->mlx, fdf->img->img);
		free(fdf->img);
		fdf->img = NULL;
	}
	if(fdf->move)
	{
		free(fdf->move);
		fdf->move = NULL;
	}
	if (fdf->map)
	{
		free(fdf->map);
		fdf->move = NULL;
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
	free(fdf);
}
