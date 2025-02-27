/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:54:29 by wshee             #+#    #+#             */
/*   Updated: 2025/02/27 17:37:19 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_map {
	int row;
	int column;
}				t_map;

typedef struct s_move{
	int mx;
	int my;
	int offset_x;
	int offset_y;
	// int step;
	int scale;
}				t_move;

typedef struct s_point{
	int x;
	int y;
	int z;
	int color;
}				t_point;

typedef struct s_fdf {
	void	*mlx;
	void	*win;
	t_img	*img;
	t_move	*move;
	t_map	*map;
	t_point **arr;
	int shift_pressed;
}				t_fdf;

#endif
