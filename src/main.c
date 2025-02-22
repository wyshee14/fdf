/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/02/21 21:27:15 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_fdf	*init_fdf(t_fdf *fdf)
{
	t_img *img = NULL;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		error_and_exit("Failed to allocate memory for fdf");
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		error_and_exit("Failed to allocate memory for img");
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		printf("Failed mlx init\n");
	fdf->win = mlx_new_window(fdf->mlx, HEIGHT, WIDTH, "FDF");
	if (!fdf->win)
		printf("Failed to create window\n");
	img->img = mlx_new_image(fdf->mlx, HEIGHT, WIDTH);
	//printf("img: %p\n", img->img);
	if (!img->img)
		printf("Failed to allocate new image\n");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		printf("Failed to get img address\n");
	fdf->img = img;
	// draw_square(fdf->img, 5, 5, 50, 0xe0c887);
	// mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	mlx_hook(fdf->win, 2, 1L<<0, press_esc, fdf);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
	// mlx_loop(fdf->mlx);
	return(fdf);
}

int main(int ac, char **av)
{
	t_map map;
	t_fdf *fdf;
	t_point **arr;
	
	fdf = NULL;
	arr = NULL;
	if (ac != 2)
		error_and_exit("Usage: ./fdf test_map.fdf\n");
	arr = parse_maps(av, &map);
	fdf = init_fdf(fdf);
	//printf("img2: %p\n", fdf->img->img);
	// draw_square(fdf->img, 5, 5, 50, 0xe0c887);
	draw_map(&map, fdf, arr);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	// scaling(arr, &map);
	// isometric
	//free(map);
	mlx_loop(fdf->mlx);
}
