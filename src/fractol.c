/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:14:44 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/12 17:15:16 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	convert_m_or_j_points(int x, int y, t_fractol **f)
{
	(*f)->z.x = ft_scale(x, (*f)->min_x, (*f)->max_x, (*f)->width) + (*f)->x_shift;
	(*f)->z.y = ft_scale(y, (*f)->max_y, (*f)->min_y, (*f)->height) + (*f)->y_shift;
	if (!ft_strcmp((*f)->set, "mandelbrot"))
	{
		(*f)->c.x = (*f)->z.x;
		(*f)->c.y = (*f)->z.y;
	}
	else
	{
		(*f)->c.x = (*f)->x_julia;
		(*f)->c.y = (*f)->y_julia;
	}
}

static void	create_m_or_j(int x, int y, t_fractol *f)
{
	//uint32_t		color;
	//int				lcg_seed;

	f->iteration = 0;
	//init_lcg(&lcg_seed, f, n);
	convert_m_or_j_points(x, y, &f);
	//f->first_color = 0x000000FF;
	//f->second_color = get_random_color(&lcg_seed, f);
	while (f->iteration < f->definition)
	{
		//m_or_j_color(&color, n, f, &lcg_seed);
		//mlx_key_hook(f->mlx_start, &colors, f);
		f->z = mandelbrot_equation(f->z, f->c);
		if ((f->z.x * f->z.x) + (f->z.y * f->z.y) > 4)
		{
			mlx_put_pixel(f->mlx_image, x, y, f->color);
			return ;
		}
		f->iteration++;
	}
	mlx_put_pixel(f->mlx_image, x, y, 0x000000FF);
}

static void	def_fern_points(double x, double y, t_fractol *f)
{
	int		n;
	int		lcg_seed;
	int		plot_x;
	int		plot_y;

	n = 0;
	ft_bzero(f->point, f->width * f->height * sizeof(unsigned int));
	init_lcg(&lcg_seed, f, n);
	while (n < f->definition)
	{
		fern_equation(&x, &y, f, &lcg_seed);
		plot_x = rev_scale(x - f->x_shift, f->min_x, f->max_x, f->width);
		plot_y = rev_scale(y - f->y_shift, f->max_y, f->min_y, f->height);
		if (plot_x >= 0 && plot_x < f->width && plot_y >= 0 && plot_y < f->height)
			f->point[plot_y * f->width + plot_x] = 0x00FF00FF;
		n++;
	}
}

static void	create_fern(int x, int y, t_fractol *f)
{
	int	index;

	index = y * f->width + x;
	if (f->point[index] != 0)
		mlx_put_pixel(f->mlx_image, x, y, f->point[index]);
	else
		mlx_put_pixel(f->mlx_image, x, y, 0x000000FF);
}

void	ft_fractol(t_fractol *f)
{
	int	x;
	int	y;

	if (!ft_strcmp(f->set, "fern"))
		def_fern_points(0, 0, f);
	y = -1;
	while (++y < f->height)
	{
		x = -1;
		while (++x < f->width)
		{
			if (!ft_strcmp(f->set, "fern"))
			{
				create_fern(x, y, f);
			}
			else
				create_m_or_j(x, y, f);
		}
	}
	mlx_image_to_window(f->mlx_start, f->mlx_image, 0, 0);
}
