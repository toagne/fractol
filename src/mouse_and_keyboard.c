/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_and_keyboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:35:48 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/10 15:40:59 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		f->zoom = 0.9;
	else if (ydelta > 0)
		f->zoom = 1.1;
	scaled_x = ft_scale(f->x_mouse, f->min_x, f->max_x, WIDTH);
	scaled_y = ft_scale(f->y_mouse, f->max_y, f->min_y, HEIGHT);
	new_x_range = (f->max_x - f->min_x) * f->zoom;
	new_y_range = (f->max_y - f->min_y) * f->zoom;
	f->min_x = scaled_x - ((double)f->x_mouse / WIDTH) * new_x_range;
	f->max_x = f->min_x + new_x_range;
	f->min_y = scaled_y - (1 - (double)f->y_mouse / HEIGHT) * new_y_range;
	f->max_y = f->min_y + new_y_range;
	ft_fractol(f);
}

void	ft_keyboard(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;
	int			boh;

	fractol = (t_fractol *)param;
	boh = 1;
	if (!ft_strcmp(fractol->set, "fern"))
		boh = 1000000;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(fractol->mlx_start);
		exit (EXIT_SUCCESS);
	}
	if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
		fractol->definition += boh;
	if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS)
		fractol->definition -= boh;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		fractol->y_shift += (fractol->max_y - fractol->min_y) * 0.1;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		fractol->y_shift -= (fractol->max_y - fractol->min_y) * 0.1;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		fractol->x_shift += (fractol->max_x - fractol->min_x) * 0.1;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		fractol->x_shift -= (fractol->max_x - fractol->min_x) * 0.1;
	ft_fractol(fractol);
}
