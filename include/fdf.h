/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:41:48 by wshee             #+#    #+#             */
/*   Updated: 2025/02/23 17:32:44 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
//# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include "struct.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>

// Color component extraction macros
#define R(color) ((color >> 16) & 0xFF)
#define G(color) ((color >> 8) & 0xFF)
#define B(color) (color & 0xFF)

// Color combination macro
#define RGB(r, g, b) ((r << 16) | (g << 8) | b)

// Color
#define DEFAULT_COLOR 0xFFFFFF

// Define STD ERROR
#define SPLIT_ERROR "Failed to split"

#define HEIGHT 720
#define WIDTH 720
#define SCALE 20

#define ESC_KEY 65307

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//error_handling.c
void	free_2d_array(char **arr);
void	error_and_exit(char *message);

//parse_map.c
int		check_file_extension(char *filename);
void	find_column(char *line, int *fd, t_map *map);
void	set_map_row_and_column(char **av, t_map *map);
t_point	**parse_maps(char **av, t_map *map);

//init_point.c
void	allocate_map(t_map *map, t_point ***arr);
int		get_color(char *column_line);
void	init_point(char **av, t_map *map, t_point ***arr);

//key_hooks.c
int	close_window(t_fdf *fdf);
int press_esc(int key, t_fdf *fdf);

//draw_line.c
void	my_mlx_pixel_put(t_img *s_img, int x, int y, int color);
void	draw_line_bresenham(t_img *s_img, t_point *begin, t_point *end);
void    slope_bigger_than_one(t_point *begin, t_point *end, int *dx, int *dy, t_img *s_img);
void    slope_less_than_one(t_point *begin, t_point *end, int *dx, int *dy, t_img *s_img);
void	draw_map(t_map *map, t_fdf *fdf, t_point **arr);
//t_point *project_point(t_point *point, t_fdf *fdf);

void draw_square(t_img *img, int x, int y, int size, int color);

#endif
