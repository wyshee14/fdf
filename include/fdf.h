/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:41:48 by wshee             #+#    #+#             */
/*   Updated: 2025/02/18 21:02:01 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
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

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map {
	int row;
	int column;
	// int **arr_2d;
}				t_map;

typedef struct s_point{
	int x;
	int y;
	int z;
	int color;
}				t_point;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

#endif
