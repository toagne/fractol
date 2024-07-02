/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:04:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/02 16:16:13 by mpellegr         ###   ########.fr       */
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

void    ft_error(void)
{
    const char    *error_message;
    
    error_message = mlx_strerror(mlx_errno);
    write(STDERR_FILENO, error_message, ft_strlen(error_message));
    exit(EXIT_FAILURE);
}

double  ft_scale(double original_num, double new_min, double new_max, double old_max)
{
    double  scale;

    scale = (new_max - new_min) * original_num / old_max + new_min;
    return (scale);
}

t_complex_num   mandelbrot_equation(t_complex_num z, t_complex_num c)
{
    t_complex_num   result;

    result.x = ((z.x * z.x) - (z.y * z.y)) + c.x;
    result.y = (2 * z.x * z.y) + c.y;
    return (result);
}

unsigned int get_rgba(int r, int g, int b, int a)
{
    return ((a) | (r << 24) | (g << 16) | (b << 8));
}
/*
uint32_t    get_color(int n)
{
    int  rgb_start[3];
    int  rgb_end[3];

    rgb_start[0] = 0;
    rgb_start[1] = 0;
    rgb_start[2] = 0;
    rgb_end[0] = 255;
    rgb_end[1] = 255;
    rgb_end[2] = 255;
    rgb_start[0] = rgb_start[0] + (n * ((rgb_end[0] - rgb_start[0]) / (MAX_ITERATIONS - 1)));
    rgb_start[1] = rgb_start[1] + (n * ((rgb_end[1] - rgb_start[1]) / (MAX_ITERATIONS - 1)));
    rgb_start[2] = rgb_start[2] + (n * ((rgb_end[2] - rgb_start[2]) / (MAX_ITERATIONS - 1)));
    return (get_rgba(rgb_start[0], rgb_start[1], rgb_start[2], 255));
}
*/

int    random_n(int n, t_fractol *fractol)
{
    long LCG_A = 16645525;
    long LCG_C = 1013904223;
    long LCG_M = 4294967296;
    int lcg_seed = n + fractol->definition;

    lcg_seed = (((LCG_A * lcg_seed + LCG_C) % LCG_M) % 256);
    return (lcg_seed);
}

uint32_t get_colour(int n, t_fractol *fractol)
{
    int r;
    int g;
    int b;

    r = random_n(n, fractol);
    g = random_n(r, fractol);
    b = random_n(g, fractol);
    return (get_rgba(r, g, b, 255));
}

void    create_fractal(int x, int y, t_fractol *fractol)
{
    t_complex_num       z;
    t_complex_num       c;
    int                 n;
    uint32_t            color;

    n = 0;
    z.x = 0.0;
    z.y = 0.0;
    c.x = (ft_scale(x, -2, 2, WIDTH) * fractol->zoom) + fractol->x_shift;
    c.y = (ft_scale(y, 2, -2, HEIGHT) * fractol->zoom) + fractol->y_shift;
    while(n < fractol->definition)
    {
        z = mandelbrot_equation(z, c);
        if ((z.x * z.x) + (z.y * z.y) > 4)
        {
            color = get_colour(n, fractol);
            //printf("iteration %d, colour 0x%08X\n", n, color);
            mlx_put_pixel(fractol->mlx_image, x, y, color);
            return;
        }
        n++;
    }
    mlx_put_pixel(fractol->mlx_image, x, y, COLOR_WHITE);
}

void    ft_fractol(t_fractol *fractol)
{
    int x;
    int y;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
            create_fractal(x, y, fractol);
    }
    mlx_image_to_window(fractol->mlx_start, fractol->mlx_image, 0, 0);
}

void    ft_mouse(double xdelta, double ydelta, void* param)
{
    t_fractol   *fractol;
    int32_t     x_mouse;
    int32_t     y_mouse;
    
    (void)xdelta;
    fractol = (t_fractol *)param;
    mlx_get_mouse_pos(fractol->mlx_start, &x_mouse, &y_mouse);
    //fractol->x_shift += x_mouse;
    //fractol->y_shift += y_mouse;
    //printf("%d   %d\n", x_mouse, y_mouse);
    if (ydelta < 0)
        fractol->zoom *= 0.95;
    else if (ydelta > 0)
        fractol->zoom *= 1.05;
    ft_fractol(fractol);
}

void    ft_keyboard(mlx_key_data_t keydata, void* param)
{
    t_fractol   *fractol;

    fractol = (t_fractol *)param;
//    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
//
    if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
        fractol->definition += 10;
    if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS)
        fractol->definition -= 10;
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
        fractol->y_shift += (0.5 * fractol->zoom);
    if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
        fractol->y_shift -= (0.5 * fractol->zoom);
    if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
        fractol->x_shift += (0.5 * fractol->zoom);
    if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
        fractol->x_shift -= (0.5 * fractol->zoom);
    ft_fractol(fractol);
}

int main(int argc, char **argv)
{
    t_fractol   fractol;

    if (2 == argc && !ft_strcmp(argv[1], "mandelbrot"))
    {
        fractol.mlx_start = mlx_init(WIDTH, HEIGHT, "mandelbrot", true);
        if (!fractol.mlx_start)
            ft_error();
        fractol.mlx_image = mlx_new_image(fractol.mlx_start, WIDTH, HEIGHT);
        if (!fractol.mlx_image)
            ft_error();
        fractol.x_shift = 0.0;
        fractol.y_shift = 0.0;
        fractol.zoom = 1.0;
        fractol.definition = 20;
        ft_fractol(&fractol);
        mlx_key_hook(fractol.mlx_start, &ft_keyboard, &fractol);
        mlx_scroll_hook(fractol.mlx_start, &ft_mouse, &fractol);
        mlx_loop(fractol.mlx_start);
        mlx_terminate(fractol.mlx_start);
    }
    else if (4 == argc && ft_strcmp(argv[1], "julia"))
    {

    }
    else
    {
        ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
        exit (EXIT_FAILURE);
    }
}
