/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:31:20 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/12 17:13:45 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/*
static unsigned int	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | (a));
}

uint32_t	get_random_color(int *lcg_seed, t_fractol *fractol)
{
	int	r;
	int	g;
	int	b;

	r = my_rand(lcg_seed, fractol) % 256;
	g = my_rand(lcg_seed, fractol) % 256;
	b = my_rand(lcg_seed, fractol) % 256;
	return (get_rgba(r, g, b, 255));
}

static int	get_r_g_b(int color, char c)
{
	if (c == 'r')
		return ((color >> 24) & 0xFF);
	else if (c == 'g')
		return ((color >> 16) & 0xFF);
	else if (c == 'b')
		return ((color >> 8) & 0xFF);
	else
		return (0);
}

static uint32_t	get_scaled_color(uint32_t color, int new_color, double ratio)
{
	int		rgb_start[3];
	int		rgb_end[3];

	rgb_start[0] = get_r_g_b(color, 'r');
	rgb_start[1] = get_r_g_b(color, 'g');
	rgb_start[2] = get_r_g_b(color, 'b');
	rgb_end[0] = get_r_g_b(new_color, 'r');
	rgb_end[1] = get_r_g_b(new_color, 'g');
	rgb_end[2] = get_r_g_b(new_color, 'b');
	rgb_start[0] = rgb_start[0] + ratio * (rgb_end[0] - rgb_start[0]);
	rgb_start[1] = rgb_start[1] + ratio * (rgb_end[1] - rgb_start[1]);
	rgb_start[2] = rgb_start[2] + ratio * (rgb_end[2] - rgb_start[2]);
	return (get_rgba(rgb_start[0], rgb_start[1], rgb_start[2], 255));
}

void	m_or_j_color(uint32_t *color, int n, t_fractol *f, int *lcg_seed)
{
	int		iteration;
	double	ratio;

	if (n < 7)
	{
		ratio = (double)n / f->definition;
		*color = get_scaled_color(0x000000FF, 0xFFFFFFFF, ratio);
		f->first_color = *color;
	}
	else
	{
		iteration = n % 3;
		if (iteration == 0 && n > 0)
		{
			f->first_color = f->second_color;
			f->second_color = get_random_color(lcg_seed, f);
		}
		ratio = (double)iteration / 3;
		*color = get_scaled_color(f->first_color, f->second_color, ratio);
	}
}
*/

void	colors(mlx_key_data_t keydata, void *param)
{
	t_fractol	*f;
	uint32_t	color[5];
	int			index;

	f = (t_fractol *)param;
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		color[0] = 0xFF00FFAA;
		color[1] = 0x39FF14AA;
		color[2] = 0x1E90FFAA;
		color[3] = 0xFF69B4AA;
		color[4] = 0xFFFF00AA;
		index = f->definition % 4;
		f->color = color[index];
	}
}
