/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:08:49 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/10 13:44:19 by mpellegr         ###   ########.fr       */
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

void	ft_error(void)
{
	const char	*error_message;

	error_message = mlx_strerror(mlx_errno);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	exit(EXIT_FAILURE);
}

void	init_lcg(int *lcg_seed, t_fractol *f, int n)
{
	if (!ft_strcmp(f->set, "fern"))
		*lcg_seed = 1103527590;
	else
		*lcg_seed = n + f->definition;
}
