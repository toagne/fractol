/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:40:06 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/10 16:24:52 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <string.h>

# define ERROR_MESSAGE "please enter one of the following:\n\"./fractol mandelbrot\"\n\"./fractol julia <value_1> <value_2>\""

# define WIDTH 1500
# define HEIGHT 1500

typedef struct s_complex_num
{
	double	x;
	double	y;
}	t_complex_num;

typedef struct s_fractol
{
	mlx_t			*mlx_start;
	mlx_image_t		*mlx_image;
	double			zoom;
	double			x_shift;
	double			y_shift;
	int				definition;
	double			min_x;
	double			max_x;
	double			min_y;
	double			max_y;
	char			*set;
	double			x_julia;
	double			y_julia;
	int				*point;
	uint32_t		first_color;
	uint32_t		second_color;
	long			lcg_a;
	long			lcg_c;
	long			lcg_m;
	t_complex_num	c;
	t_complex_num	z;
	double			fern_new_x;
	double			fern_new_y;
	int32_t			x_mouse;
	int32_t			y_mouse;
}	t_fractol;

void		check_arguments(int argc, char **argv, t_fractol *f);
void		ft_fractol(t_fractol *fractol);
void		ft_init(t_fractol *fractol);

int			my_rand(int *lcg_seed, t_fractol *f);
int			rev_scale(double n, double new_min, double new_max, double old_max);
int			random_n(int n, t_fractol *fractol);
t_c_num		mandelbrot_equation(t_complex_num z, t_complex_num c);
double		ft_scale(double orig_num, double n_min, double n_max, double o_max);
void		fern_equation(double *x, double *y, t_fractol *f, int *lcg_seed);

int			ft_strcmp(char *str1, const char *str2);
void		ft_error(void);
void		init_lcg(int *lcg_seed, t_fractol *f, int n);

uint32_t	get_random_color(int *lcg_seed, t_fractol *fractol);
void		m_or_j_color(uint32_t *color, int n, t_fractol *f, int *lcg_seed);

void		ft_mouse(double xdelta, double ydelta, void *param);
void		ft_keyboard(mlx_key_data_t keydata, void *param);

#endif
