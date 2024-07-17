/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:04:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/16 10:12:51 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	f;

	check_arguments(argc, argv, &f);
	ft_init(&f);
	f.mlx_start = mlx_init(f.width, f.height, "fractol", false);
	if (!f.mlx_start)
		ft_error(&f);
	f.mlx_image = mlx_new_image(f.mlx_start, f.width, f.height);
	if (!f.mlx_image)
		ft_error(&f);
	mlx_key_hook(f.mlx_start, &ft_keyboard, &f);
	mlx_scroll_hook(f.mlx_start, &ft_mouse, &f);
	ft_fractol(&f);
	mlx_loop(f.mlx_start);
	mlx_terminate(f.mlx_start);
	free(f.point);
	exit(EXIT_SUCCESS);
}
