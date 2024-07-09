/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:40:06 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/09 11:56:51 by mpellegr         ###   ########.fr       */
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
#include <string.h>

# define ERROR_MESSAGE "please enter one of the following:\n\"./fractol mandelbrot\"\n\"./fractol julia <value_1> <value_2>\""

# define WIDTH 1500
# define HEIGHT 1500
//# define MAX_ITERATIONS 100
# define BPP sizeof(int32_t)

/*# define LCG_A 1103515245
# define LCG_C 12345
# define LCG_M 2147483648  // 2^31*/

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
    char            *set;
    double          x_julia;
    double          y_julia;
    int             *point;
    int             start_color;
    int             random_color;
}   t_fractol;

typedef struct s_complex_num
{
    double  x;
    double  y;
//    double  escape_value;
}   t_complex_num;

void check_arguments(int argc, char **argv, t_fractol *f);
void ft_init(t_fractol *fractol);

#endif
