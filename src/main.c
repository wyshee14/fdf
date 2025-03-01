/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:02:09 by wshee             #+#    #+#             */
/*   Updated: 2025/03/01 21:53:16 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_img *init_img(t_fdf *fdf)
{
	t_img *img;

	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		error_and_exit("Failed to allocate memory for img");
	img->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	//printf("img: %p\n", img->img);
	if (!img->img)
		printf("Failed to allocate new image\n");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		printf("Failed to get img address\n");
	return(img);
}

t_move *init_move(void)
{
	t_move *move;

	move = (t_move *)malloc(sizeof(t_move));
	if (!move)
		error_and_exit("Failed to allocate memory for move");
	// move->step = 10;
	move->offset_x = WIDTH / 2;
	move->offset_y = HEIGHT / 2;
	move->scale = 5;
	//printf("offset_x: %d, step: %d\n", move->offset_x, move->step);
	return(move);
}

t_fdf	*init_fdf(t_fdf *fdf, char **av)
{
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		error_and_exit("Failed to allocate memory for fdf");
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		printf("Failed mlx init\n");
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	if (!fdf->win)
		printf("Failed to create window\n");
	fdf->img = init_img(fdf);
	fdf->move = init_move();
	fdf->map = parse_maps(av);
	fdf->arr = init_point(av, fdf->map);
	return(fdf);
}

int main(int ac, char **av)
{
	//t_map map;
	t_fdf *fdf;
	// t_point **arr;

	fdf = NULL;
	// arr = NULL;
	if (ac != 2)
		error_and_exit("Usage: ./fdf test_map.fdf\n");
	fdf = init_fdf(fdf, av);
	// draw_square(fdf->img, 5, 5, 50, 0xe0c887);
	draw_map(fdf);
	// mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	setup_hook(fdf);
	//free(map);
	mlx_loop(fdf->mlx);
}
