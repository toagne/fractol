/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:40:06 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/03 15:27:15 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define ERROR_MESSAGE "please enter one of the following:\n\"./fractol mandelbrot\"\n\"./fractol julia <value_1> <value_2>\""

# define WIDTH 1500
# define HEIGHT 1500
//# define MAX_ITERATIONS 100

#define COLOR_BLACK      0xFF000000
#define COLOR_WHITE      0xFFFFFFFF
#define COLOR_RED        0xFFFF0000
#define COLOR_GREEN      0xFF00FF00
#define COLOR_BLUE       0xFF0000FF
#define COLOR_YELLOW     0xFFFFFF00
#define COLOR_CYAN       0xFF00FFFF
#define COLOR_MAGENTA    0xFFFF00FF
#define COLOR_TRANSPARENT 0x00000000

typedef struct s_fractol
{
    mlx_t           *mlx_start;
    mlx_image_t     *mlx_image;
    double          zoom;
    double          x_shift;
    double          y_shift;
    int             definition;
    double          min_x;
    double          max_x;
    double          min_y;
    double          max_y;
    double          old_min_x;
    double          old_max_x;
    double          old_min_y;
    double          old_max_y;
}   t_fractol;

typedef struct s_complex_num
{
    double  x;
    double  y;
//    double  escape_value;
}   t_complex_num;

#endif
