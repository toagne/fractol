/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_and_keyboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:35:48 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/12 17:12:58 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_cursor(double xpos, double ypos, void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	if (!ft_strcmp(f->set, "julia") && f->j_dynamic == 1)
	{
		f->x_julia = ft_scale(xpos, f->min_x, f->max_x, f->width) + f->x_shift;
		f->y_julia = ft_scale(ypos, f->max_y, f->min_y, f->height) + f->y_shift;
	}
}

void	ft_mouse(double xdelta, double ydelta, void *param)
{
	t_fractol	*f;
	double		scaled_x;
	double		scaled_y;
	double		new_x_range;
	double		new_y_range;

	(void)xdelta;
	f = (t_fractol *)param;
	mlx_get_mouse_pos(f->mlx_start, &f->x_mouse, &f->y_mouse);
	if (ydelta < 0)
		f->zoom = 1.2;
	else if (ydelta > 0)
		f->zoom = 0.8;
	scaled_x = ft_scale(f->x_mouse, f->min_x, f->max_x, f->width);
	scaled_y = ft_scale(f->y_mouse, f->max_y, f->min_y, f->height);
	new_x_range = (f->max_x - f->min_x) * f->zoom;
	new_y_range = (f->max_y - f->min_y) * f->zoom;
	f->min_x = scaled_x - ((double)f->x_mouse / f->width) * new_x_range;
	f->max_x = f->min_x + new_x_range;
	f->min_y = scaled_y - (1 - (double)f->y_mouse / f->height) * new_y_range;
	f->max_y = f->min_y + new_y_range;
	ft_fractol(f);
}

void	arrows(mlx_key_data_t *keydata, t_fractol *f)
{
	if (f->j_dynamic)
	{
		if (keydata->key == MLX_KEY_UP && keydata->action == MLX_PRESS)
			f->y_julia -= 0.01 * f->zoom;
		if (keydata->key == MLX_KEY_DOWN && keydata->action == MLX_PRESS)
			f->y_julia += 0.01 * f->zoom;
		if (keydata->key == MLX_KEY_RIGHT && keydata->action == MLX_PRESS)
			f->x_julia -= 0.01 * f->zoom;
		if (keydata->key == MLX_KEY_LEFT && keydata->action == MLX_PRESS)
			f->x_julia += 0.01 * f->zoom;
	}
	else
	{
		if (keydata->key == MLX_KEY_UP && keydata->action == MLX_PRESS)
			f->y_shift -= (f->max_y - f->min_y) * 0.1;
		if (keydata->key == MLX_KEY_DOWN && keydata->action == MLX_PRESS)
			f->y_shift += (f->max_y - f->min_y) * 0.1;
		if (keydata->key == MLX_KEY_RIGHT && keydata->action == MLX_PRESS)
			f->x_shift -= (f->max_x - f->min_x) * 0.1;
		if (keydata->key == MLX_KEY_LEFT && keydata->action == MLX_PRESS)
			f->x_shift += (f->max_x - f->min_x) * 0.1;
	}
}

void	ft_keyboard(mlx_key_data_t keydata, void *param)
{
	t_fractol	*f;
	int			def;

	f = (t_fractol *)param;
	def = 1;
	if (!ft_strcmp(f->set, "fern"))
		def = 1000000;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(f->mlx_start);
		exit (EXIT_SUCCESS);
	}
	if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
		f->definition += def;
	if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS)
		f->definition -= def;
//	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
//		colors(f);
	if (keydata.key == MLX_KEY_J)
	{
		if (keydata.action == MLX_REPEAT)
		{
			f->j_dynamic = 1;
			mlx_cursor_hook(f->mlx_start, &ft_cursor, f);
		}
		else if (keydata.action == MLX_RELEASE)
			f->j_dynamic = 0;
	}
	arrows(&keydata, f);
	ft_fractol(f);
}
