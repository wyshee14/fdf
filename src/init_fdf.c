/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:12:26 by wshee             #+#    #+#             */
/*   Updated: 2025/03/05 21:30:42 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Function: mlx_get_data_addr
// t_img *img: A pointer to an image structure.
// int *bits_per_pixel: Pointer to an integer where the function stores the number of bits per pixel.
// int *size_line: Pointer to an integer where the function stores the number of bytes per row of the image.
// int *endian: Pointer to an integer where the function stores the endian format of the image (big-endian or little-endian).
// Bid Endian (endian == 1): most significant byte (MSB) is stored first (lowest memory address)
// Little-Endian (endian == 0): least significant byte (LSB) is stored first.
// Returns: A pointer to the raw pixel data of the image.
t_img *init_img(t_fdf *fdf)
{
	t_img *img;

	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		error_and_exit("Failed to allocate memory for img");
	img->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	//printf("img: %p\n", img->img);
	if (!img->img)
		error_and_exit("Failed to allocate new image\n");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		error_and_exit("Failed to get img address\n");
	return(img);
}

// this struct is to move the image on window (for bonus)
// z_max is used to calculate scale to be right fit in the window
// scale project to the point that we want to draw the line
// offset_x and y move the image to the center or when doing translation
// is_iso is a flag to change from isometric view to parallel view
t_move *init_move(t_fdf *fdf)
{
	t_move *move;
	(void)fdf;

	move = ft_calloc(1, sizeof(t_move));
	if (!move)
	{
		free_tpoint_arr(fdf->arr, fdf->map);
		free_map(fdf->map);
		error_and_exit("Failed to allocate memory for move");
	}
	move->z_max = find_z_max(fdf);
	move->scale = get_scale(fdf, move);
	move->is_iso = 1;
	move->z_factor = 1;
	// printf("gamma: %f\n", move->gamma_z);
	//printf("offset_x: %d, step: %d\n", move->offset_x, move->step);
	return(move);
}

//initialize the

void	init_fdf(t_fdf *fdf, char **av)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	if (!fdf)
		error_and_exit("Failed to allocate memory for fdf");
	fdf->map = parse_maps(av);
	fdf->arr = init_point(av, fdf->map);
	fdf->move = init_move(fdf);
	fdf->mlx = mlx_init();
	fdf->img = init_img(fdf);
	if (!fdf->mlx)
		printf("Failed mlx init\n");
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	if (!fdf->win)
		printf("Failed to create window\n");
}
