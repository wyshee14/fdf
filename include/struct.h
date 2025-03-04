/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:54:29 by wshee             #+#    #+#             */
/*   Updated: 2025/03/04 21:11:19 by wshee            ###   ########.fr       */
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

typedef enum projection
{
	TOP_VIEW,
	FRONT_VIEW,
	RIGHT_SIDE_VIEW
}			t_projection;

typedef struct s_move{
	int mx;
	int my;
	int offset_x;
	int offset_y;
	// int step;
	int scale;
	int z_min;
	int z_max;
	int z_elevation;
	float alpha_x;
	float tetha_y;
	float gamma_z;
	int is_iso;
	t_projection projection;
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
