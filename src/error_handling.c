/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:28:21 by wshee             #+#    #+#             */
/*   Updated: 2025/02/19 16:34:46 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/fdf.h"

void	free_2d_array(char **arr)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void error_and_exit(char *message)
{
	perror(message);
	exit(1);
}
