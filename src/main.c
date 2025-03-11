/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/03/11 15:43:49 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function: mlx_loop
// infinite loop that waits for an event,
int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
		error_and_exit("Usage: ./fdf test_map.fdf\n");
	init_fdf(&fdf, av);
	draw_map(&fdf);
	setup_hook(&fdf);
	mlx_loop(fdf.mlx);
}
