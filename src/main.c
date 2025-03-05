/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/03/05 20:44:29 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int find_z_min(t_fdf *fdf)
{
	int min;
	int i;
	int j;

	min = fdf->arr[0][0].z;
	j = 0;
	while(j < fdf->map->row)
	{
		i = 0;
		while(i < fdf->map->column)
		{
			if (min > fdf->arr[j][i].z)
				min = fdf->arr[j][i].z;
			i++;
		}
		j++;
	}
	// printf("zmin: %d\n", min);
	return(min);
}

// Function: mlx_loop
// infinite loop that waits for an event,
int main(int ac, char **av)
{
	t_fdf fdf;

	if (ac != 2)
		error_and_exit("Usage: ./fdf test_map.fdf\n");
	init_fdf(&fdf, av);
	draw_map(&fdf);
	setup_hook(&fdf);
	mlx_loop(fdf.mlx);
}
