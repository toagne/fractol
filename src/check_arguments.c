/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:23:37 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/05 10:18:17 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int ft_strcmp(char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

int	ft_isspace_plus_or_minus(char *str, int *negative)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 43)
		i++;
	if (str[i] == 45)
	{
		*negative *= -1;
		i++;
	}
	return (i);
}

double	ft_atofl(char *str)
{
	int		i;
	int		negative;
	double	n;
	double	convert_to_decimal;

	negative = 1;
	n = 0.0;
	convert_to_decimal = 0.1;
	i = ft_isspace_plus_or_minus(str, &negative);
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		n = n + (str[i] - '0') * convert_to_decimal;
		convert_to_decimal *= 0.1;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (100);
	return (n * negative);
}

void	check_julia_params(char **argv, t_fractol *f)
{
	f->x_julia = ft_atofl(argv[2]);
	if (f->x_julia > 2.0 || f->x_julia < -2.0)
	{
		ft_putstr_fd(ERROR_MESSAGE, EXIT_FAILURE);
		exit (EXIT_FAILURE);
	}
	f->y_julia = ft_atofl(argv[3]);
	if (f->y_julia > 2.0 || f->y_julia < -2.0)
	{
		ft_putstr_fd(ERROR_MESSAGE, EXIT_FAILURE);
		exit (EXIT_FAILURE);
	}
}

void	check_arguments(int argc, char **argv, t_fractol *f)
{
	if (argc == 2 && !ft_strcmp(argv[1], "mandelbrot"))
		f->set = "mandelbrot";
	else if (argc == 2 && !ft_strcmp(argv[1], "felce"))
		f->set = "felce";
	else if (argc == 4 && !ft_strcmp(argv[1], "julia"))
	{
		f->set = "julia";
		if (argc == 4)
			check_julia_params(argv, f);
	}
	else
	{
		ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
}
