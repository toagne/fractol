/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:26:15 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/10 16:24:58 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	my_rand(int *lcg_seed, t_fractol *f)
{
	*lcg_seed = (f->lcg_a * (*lcg_seed) + f->lcg_c) % f->lcg_m;
	return (*lcg_seed);
}

int	rev_scale(double n, double new_min, double new_max, double old_max)
{
	int	unscaled_n;

	unscaled_n = (int)((n - new_min) * old_max / (new_max - new_min));
	return (unscaled_n);
}

double	ft_scale(double orig_num, double n_min, double n_max, double o_max)
{
	double	scale;

	scale = (n_max - n_min) * original_num / o_max + n_min;
	return (scale);
}

t_complex_num	mandelbrot_equation(t_complex_num z, t_complex_num c)
{
	t_complex_num	result;

	result.x = ((z.x * z.x) - (z.y * z.y)) + c.x;
	result.y = (2 * z.x * z.y) + c.y;
	return (result);
}

void	fern_equation(double *x, double *y, t_fractol *f, int *lcg_seed)
{
	double	r;

	r = (double)my_rand(lcg_seed, f) / RAND_MAX;
	if (r < 0.01)
	{
		f->fern_new_x = 0;
		f->fern_new_y = 0.16 * (*y);
	}
	else if (r < 0.86)
	{
		f->fern_new_x = 0.85 * (*x) + 0.04 * (*y);
		f->fern_new_y = -0.04 * (*x) + 0.85 * (*y) + 1.6;
	}
	else if (r < 0.93)
	{
		f->fern_new_x = 0.2 * (*x) - 0.26 * (*y);
		f->fern_new_y = 0.23 * (*x) + 0.22 * (*y) + 0.44;
	}
	else
	{
		f->fern_new_x = -0.15 * (*x) + 0.28 * (*y);
		f->fern_new_y = 0.26 * (*x) + 0.24 * (*y) + 0.44;
	}
	*x = f->fern_new_x;
	*y = f->fern_new_y;
}
