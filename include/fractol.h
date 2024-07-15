/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:40:06 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/15 16:50:46 by mpellegr         ###   ########.fr       */
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

# define ERROR_MESSAGE "please enter one of the following:\n\"./fractol mandelbrot\"\n\"./fractol julia <value_1> <value_2>\""

//# define WIDTH 1500
//# define HEIGHT 1500

typedef struct s_cmplx_n
{
	double	x;
	double	y;
}	t_cmplx_n;

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
	uint32_t		color;
	t_cmplx_n		c;
	t_cmplx_n		z;
	double			fern_new_x;
	double			fern_new_y;
	int32_t			x_mouse;
	int32_t			y_mouse;
	int				width;
	int				height;
	int				j_dynamic;
	int				iteration;
	int				color_index;
	int				color_set;
	long			lcg_seed;
}	t_fractol;

void		check_arguments(int argc, char **argv, t_fractol *f);
void		ft_fractol(t_fractol *fractol);
void		ft_init(t_fractol *fractol);

int			my_rand(t_fractol *f);
int			rev_scale(double n, double new_min, double new_max, double old_max);
t_cmplx_n	mandelbrot_equation(t_cmplx_n z, t_cmplx_n c);
double		ft_scale(double orig_num, double n_min, double n_max, double o_max);
void		fern_equation(double *x, double *y, t_fractol *f);

int			ft_strcmp(char *str1, const char *str2);
void		ft_error(void);
void		init_lcg(int *lcg_seed, t_fractol *f, int n);

void		colors(int n, t_fractol *f);
void		scaled_colors(int n, t_fractol *f);

void		ft_mouse(double xdelta, double ydelta, void *param);
void		ft_keyboard(mlx_key_data_t keydata, void *param);

#endif
