/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:08:49 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/16 11:04:15 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

void	ft_message(void)
{
	ft_putstr_fd("please enter one of the following\n", STDERR_FILENO);
	ft_putstr_fd("	./fractol mandelbrot\n", STDERR_FILENO);
	ft_putstr_fd("	./fractol julia <value_1> <value_2>", STDERR_FILENO);
	ft_putstr_fd(" || values must be between -2 and 2\n", STDERR_FILENO);
	ft_putstr_fd("	./fractol fern", STDERR_FILENO);
}

void	ft_error(t_fractol *f)
{
	if (f->mlx_start)
		mlx_terminate(f->mlx_start);
	if (f->point)
		free(f->point);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}
