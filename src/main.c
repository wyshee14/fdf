/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/02/20 17:07:31 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// void init_data(t_map *map)
// {
// 	// map = (t_map *)malloc(sizeof(t_map));
// 	// if(!map)
// 	// 	error_and_exit("Failed to allocate memory for map");
// }

int main(int ac, char **av)
{
	t_map map;

	(void)av;
	if (ac != 2)
		error_and_exit("Usage: ./fdf test_map.fdf\n");
	parse_maps(av, &map);
	//free(map);
}
