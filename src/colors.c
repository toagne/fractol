/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:31:20 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/15 14:22:00 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static unsigned int	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | (a));
}

void	scaled_colors(int n, t_fractol *f)
{
	double		ratio;
	int			rgb_start[3];
	int			rgb_end[3];

	ratio = (double)(n % 5) / 5;
	rgb_start[0] = 0;
	rgb_start[1] = 255;
	rgb_start[2] = 255;
	rgb_end[0] = 0;
	rgb_end[1] = 0;
	rgb_end[2] = 255;
	rgb_start[0] = rgb_start[0] + ratio * (rgb_end[0] - rgb_start[0]);
	rgb_start[1] = rgb_start[1] + ratio * (rgb_end[1] - rgb_start[1]);
	rgb_start[2] = rgb_start[2] + ratio * (rgb_end[2] - rgb_start[2]);
	f->color = get_rgba(rgb_start[0], rgb_start[1], rgb_start[2], 255);
}

void	colors(int n, t_fractol *f)
{
	uint32_t	color[5];
	int			index;

	index = 0;
	color[0] = 0xFF1493FF;
	color[1] = 0x39FF14FF;
	color[2] = 0x00FFFFFF;
	color[3] = 0xFFA500FF;
	color[4] = 0x9400D3FF;
	index = n % 5;
	f->color = color[index];
}
