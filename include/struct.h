/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:54:29 by wshee             #+#    #+#             */
/*   Updated: 2025/02/20 16:56:49 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
