/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:46:33 by wshee             #+#    #+#             */
/*   Updated: 2025/02/21 18:02:24 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// Color component extraction macros
#define R(color) ((color >> 16) & 0xFF)
#define G(color) ((color >> 8) & 0xFF)
#define B(color) (color & 0xFF)

// Color combination macro
#define RGB(r, g, b) ((r << 16) | (g << 8) | b)

void draw_line(t_img *img, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	//  pixels = sqrt((10 * 10) + (0 * 0)) = sqrt(100) = 10
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		my_mlx_pixel_put(img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

void draw_circle(t_img *data, int x, int y, int radius, int color) {
    int i, j;
    double distance;

    for (i = -radius; i <= radius; i++)
	{
        for (j = -radius; j <= radius; j++)
		{
            distance = sqrt(i * i + j * j);
            if (distance <= radius)
			{
                int pixel_x = x + j;
                int pixel_y = y + i;

                // Check for out-of-bounds access
                if (pixel_x >= 0 && pixel_x < 1920 && pixel_y >= 0 && pixel_y < 1080)
				{
                    my_mlx_pixel_put(data, pixel_x, pixel_y, color);
                }
            }
        }
    }
}


void draw_square(t_img *img, int x, int y, int size, int color)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            my_mlx_pixel_put(img, x + j, y + i, color);
        }
    }
}

void draw_square_gradient(t_img *data, int x, int y, int size, int start_color, int end_color) {
    int i, j;
    double r_increment = (double)(R(end_color) - R(start_color)) / (double)size;
    double g_increment = (double)(G(end_color) - G(start_color)) / (double)size;
    double b_increment = (double)(B(end_color) - B(start_color)) / (double)size;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            int r = R(start_color) + (int)(i * r_increment);
            int g = G(start_color) + (int)(i * g_increment);
            int b = B(start_color) + (int)(i * b_increment);

            //Clamp the values between 0 and 255
            r = (r > 255) ? 255 : (r < 0) ? 0 : r;
            g = (g > 255) ? 255 : (g < 0) ? 0 : g;
            b = (b > 255) ? 255 : (b < 0) ? 0 : b;

            int color = (r << 16) | (g << 8) | b;
            my_mlx_pixel_put(data, x + j, y + i, color);
        }
    }
}

// int close_window(t_fdf *vars)
// {
// 	// (void)keycode;
// 	// (void)vars;
// 	// if(!vars || !vars->mlx || !vars->win)
// 	// {
// 	// 	printf("Error: Invalid data structure\n");
// 	// 	exit(1);
// 	// }
// 	if (vars->win)
// 	{
// 		// printf("Closing window...\n");
// 		mlx_destroy_window(vars->mlx, vars->win);
// 		vars->win = NULL;
// 	}
// 	// if (vars->mlx)
// 	// {
// 	// 	mlx_destroy_display(vars->mlx);
// 	// 	free(vars->mlx);
// 	// 	vars->mlx = NULL;
// 	// }
// 	exit(0);
// 	return(0);
// }

int key_hook(int keycode, t_fdf *vars)
{
	(void)keycode;
	(void)vars;
	printf("Hello from key hook!\n");
	return (0);
}

int mouse_hook(int keycode, t_fdf *vars)
{
	(void)keycode;
	(void)vars;
	printf("Hello from mouse hook!\n");
	return (0);
}

// int main(void)
// {
// 	// void	*mlx;
// 	// void *mlx_win;
// 	t_img	img;
// 	t_fdf	vars;

// 	vars.mlx = mlx_init();
// 	if (!vars.mlx)
// 	{
// 		printf("Failed to initialize Minilibx\n");
// 		return (1);
// 	}
// 	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Welcome to FDF");
// 	if (!vars.win)
// 	{
// 		printf("Failed to create\n");
// 		return (1);
// 	}
// 	img.img = mlx_new_image(vars.mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	// draw_square(&img, 50, 50, 100, 0xe0c887);
// 	// draw_circle(&img, 100, 100, 50, 0x00FF00);
// 	// draw_square_gradient(&img, 50, 50, 1000, 0x0000FF, 0xFF0000);
// 	draw_line(&img, 10, 0, 200, 100, 0xFFFFFF); // This should create a white horizontal line about 10 pixels long.
// 	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
// 	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
// 	mlx_key_hook(vars.win, key_hook, &vars);
// 	mlx_mouse_hook(vars.win, close_window, &vars);
// 	mlx_hook(vars.win, 17, 0, close_window, &vars);
// 	mlx_loop(vars.mlx);
// 	return(0);
// }

// Function: mlx_get_data_addr
// t_img *img: A pointer to an image structure.
// int *bits_per_pixel: Pointer to an integer where the function stores the number of bits per pixel.
// int *size_line: Pointer to an integer where the function stores the number of bytes per row of the image.
// int *endian: Pointer to an integer where the function stores the endian format of the image (big-endian or little-endian).
// Bid Endian (endian == 1): most significant byte (MSB) is stored first (lowest memory address)
// Little-Endian (endian == 0): least significant byte (LSB) is stored first.
// Returns: A pointer to the raw pixel data of the image.

// Function: mlx_loop
// infinite loop that waits for an event,
