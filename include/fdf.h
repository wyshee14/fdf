/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:41:48 by wshee             #+#    #+#             */
/*   Updated: 2025/03/05 17:56:13 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
#include "X11/keysym.h"
#include "X11/X.h"
//# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include "struct.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>

// Color
#define DEFAULT_COLOR 0xFFFFFF
#define COLOR1 0x87CEFA
#define COLOR2 0x7CFC00

// Define STD ERROR
#define SPLIT_ERROR "Failed to split"

#define HEIGHT 2000
#define WIDTH 3000
#define SCALE 5
#define MOVE_STEP 100

// define key
#define ESC_KEY 65307
// #define KEY_UP 126
// #define KEY_DOWN 125
// #define KEY_LEFT 123
// #define KEY_RIGHT 124

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//error_handling.c
void	free_2d_array(void **arr);
void	error_and_exit(char *message);
void	free_all(t_fdf *fdf);

//parse_map.c
int		check_file_extension(char *filename);
void	find_column(char *line, int *fd, t_map *map);
void	set_map_row_and_column(char **av, t_map *map);
t_map	*parse_maps(char **av);

//init_point.c
void	allocate_map(t_map *map, t_point ***arr);
int		get_color(char *column_line);
t_point	**init_point(char **av, t_map *map);

//key_hooks.c
int		close_window(t_fdf *fdf);
int		key_press(int key, t_fdf *fdf);
void	elevation(int key, t_fdf *fdf);
void	change_colour(int key, t_fdf *fdf);
void	projection_pressed(int key, t_fdf *fdf);
void	projection_type(int key, t_fdf *fdf);
void	rotate(int key, t_fdf *fdf);
void	zoom(int key, t_fdf *fdf);
void	move(int key, t_fdf *fdf);
void	setup_hook(t_fdf *fdf);

//draw.c
void	my_mlx_pixel_put(t_img *s_img, int x, int y, int color);
void	draw_line_bresenham(t_img *s_img, t_point *begin, t_point *end);
void	slope_bigger_than_one(t_point *begin, t_point *end, int *dx, int *dy, t_img *s_img);
void	slope_less_than_one(t_point *begin, t_point *end, int *dx, int *dy, t_img *s_img);
int	draw_map(t_fdf *fdf);
t_point	ft_scale(t_point point, t_fdf *fdf);

//color.c
float	fraction(float x1, float x2, float x);
int		color_gradient(t_point *begin, t_point *end, float *distance);
int		get_gradient_color(t_point *current, t_point *begin, t_point *end, int *dx, int *dy);

//utils.c
void    clear_image(t_fdf *fdf);

//rotate.c
void	rotate_x(t_point *a, t_move *move);
void	rotate_y(t_point *a, t_move *move);
void	rotate_z(t_point *a, t_move *move);

#endif
