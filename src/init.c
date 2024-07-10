/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:56:56 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/10 13:02:21 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_init(t_fractol *fractol)
{
	fractol->zoom = 1.0;
	fractol->x_shift = 0.0;
	fractol->y_shift = 0.0;
	fractol->lcg_a = 1103515245;
	fractol->lcg_c = 12345;
	fractol->lcg_m = 2147483648;
	if (!ft_strcmp(fractol->set, "fern"))
	{
		fractol->definition = 1000000;
		fractol->min_x = -3;
		fractol->max_x = 3;
		fractol->min_y = 0;
		fractol->max_y = 10;
	}
	else
	{
		fractol->definition = 3;
		fractol->min_x = -2;
		fractol->max_x = 2;
		fractol->min_y = -2;
		fractol->max_y = 2;
	}
	fractol->point = (int *)malloc(WIDTH * HEIGHT * sizeof(unsigned int));
}
