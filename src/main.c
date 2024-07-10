/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:04:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/10 15:13:45 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	fractol.mlx_start = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!fractol.mlx_start)
		ft_error();
	fractol.mlx_image = mlx_new_image(fractol.mlx_start, WIDTH, HEIGHT);
	if (!fractol.mlx_image)
		ft_error();
	check_arguments(argc, argv, &fractol);
	ft_init(&fractol);
	ft_fractol(&fractol);
	mlx_key_hook(fractol.mlx_start, &ft_keyboard, &fractol);
	mlx_scroll_hook(fractol.mlx_start, &ft_mouse, &fractol);
	mlx_loop(fractol.mlx_start);
	mlx_terminate(fractol.mlx_start);
}
