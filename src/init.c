/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:56:56 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/16 09:31:06 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_malloc(t_fractol *f)
{
	f->point = (int *)malloc(f->width * f->height * sizeof(unsigned int));
	if (!f->point)
		exit(EXIT_FAILURE);
}

void	ft_init(t_fractol *f)
{
	f->zoom = 1.0;
	f->x_shift = 0.0;
	f->y_shift = 0.0;
	f->width = 1000;
	f->height = 1000;
	f->j_dynamic = 0;
	f->color = 0xFFFFFFFF;
	f->color_set = 0;
	if (!ft_strcmp(f->set, "fern"))
	{
		f->definition = 1000000;
		f->min_x = -3;
		f->max_x = 3;
		f->min_y = 0;
		f->max_y = 10;
	}
	else
	{
		f->definition = 50;
		f->min_x = -2;
		f->max_x = 2;
		f->min_y = -2;
		f->max_y = 2;
	}
	ft_malloc(f);
}
