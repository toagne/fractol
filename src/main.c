/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:04:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/04 17:44:53 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp_1(char *str1, const char *str2)
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

uint32_t    get_scaled_color(int n, t_fractol *f)
{
    int  rgb_start[3];
    int  rgb_end[3];

    rgb_start[0] = 0;
    rgb_start[1] = 0;
    rgb_start[2] = 0;
    rgb_end[0] = 255;
    rgb_end[1] = 255;
    rgb_end[2] = 255;
    rgb_start[0] = rgb_start[0] + (n * ((rgb_end[0] - rgb_start[0]) / (f->definition - 1)));
    rgb_start[1] = rgb_start[1] + (n * ((rgb_end[1] - rgb_start[1]) / (f->definition - 1)));
    rgb_start[2] = rgb_start[2] + (n * ((rgb_end[2] - rgb_start[2]) / (f->definition - 1)));
    return (get_rgba(rgb_start[0], rgb_start[1], rgb_start[2], 255));
}
/*
uint32_t    get_scaled_color_1(int n, t_fractol *f)
{
    int  rgb_start[3];
    int  rgb_end[3];

    rgb_start[0] = 255;
    rgb_start[1] = 255;
    rgb_start[2] = 0;
    rgb_end[0] = 255;
    rgb_end[1] = 0;
    rgb_end[2] = 0;
    rgb_start[0] = rgb_start[0] + (n * ((rgb_end[0] - rgb_start[0]) / (f->definition - 1)));
    rgb_start[1] = rgb_start[1] + (n * ((rgb_end[1] - rgb_start[1]) / (f->definition - 1)));
    rgb_start[2] = rgb_start[2] + (n * ((rgb_end[2] - rgb_start[2]) / (f->definition - 1)));
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

uint32_t get_random_color(int n, t_fractol *fractol)
{
    int r;
    int g;
    int b;

    r = random_n(n, fractol);
    g = random_n(r, fractol);
    b = random_n(g, fractol);
    return (get_rgba(r, g, b, 255));
}

void    create_fractal(int x, int y, t_fractol *f)
{
    t_complex_num       z;
    t_complex_num       c;
    int                 n;
    uint32_t            color;
    uint32_t            new_color;

    n = 0;
    new_color = 0;
    //z.x = 0.0;
    //z.y = 0.0;
    z.x = ft_scale(x, f->min_x, f->max_x, WIDTH) + f->x_shift;
    z.y = ft_scale(y, f->max_y, f->min_y, HEIGHT) + f->y_shift;
    if (!ft_strcmp_1(f->set, "mandelbrot"))
    {
        c.x = z.x;
        c.y = z.y;
    }
    else
    {
        c.x = f->x_julia;
        c.y = f->y_julia;
    }
    while(n < f->definition)
    {
        z = mandelbrot_equation(z, c);
        if ((z.x * z.x) + (z.y * z.y) > 4)
        {
            if (n < 10)
                color = get_scaled_color(n, f);
            //else if (n == f->definition - 1)
            //{
            //    color = new_color;
            //}
            else
            {/*
                color = get_scaled_color_1(n, f);*/
                //color = get_random_color(n, f);
                color  = get_random_color(n, f);
                //new_color = color;
            }
            mlx_put_pixel(f->mlx_image, x, y, color);
            return;
        }
        n++;
    }
    mlx_put_pixel(f->mlx_image, x, y, 0x000000FF);
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
    t_fractol   *f;
    int32_t     x_mouse;
    int32_t     y_mouse;
    double  scaled_x;
    double  scaled_y;
    double  new_x_range;
    double  new_y_range;

    
    (void)xdelta;
    f = (t_fractol *)param;
    mlx_get_mouse_pos(f->mlx_start, &x_mouse, &y_mouse);
    if (ydelta < 0)
        f->zoom = 0.95;
    else if (ydelta > 0)
        f->zoom = 1.05;
    scaled_x = ft_scale(x_mouse, f->min_x, f->max_x, WIDTH);
    scaled_y = ft_scale(y_mouse, f->max_y, f->min_y, HEIGHT);
    new_x_range = (f->max_x - f->min_x) * f->zoom;
    new_y_range = (f->max_y - f->min_y) * f->zoom;
    f->min_x = scaled_x - ((double)x_mouse / WIDTH) * new_x_range;
    f->max_x = f->min_x + new_x_range;
    f->min_y = scaled_y - (1 - (double)y_mouse / HEIGHT) * new_y_range;
    f->max_y = f->min_y + new_y_range;
    ft_fractol(f);
}

void    ft_keyboard(mlx_key_data_t keydata, void* param)
{
    t_fractol   *fractol;

    fractol = (t_fractol *)param;
//    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
        fractol->definition += 1;
    if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS)
        fractol->definition -= 1;
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
        fractol->y_shift += (fractol->max_y - fractol->min_y) * 0.1;
        //fractol->y_shift += (0.5 * fractol->zoom);
    if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
        fractol->y_shift -= (fractol->max_y - fractol->min_y) * 0.1;
        //fractol->y_shift -= (0.5 * fractol->zoom);
    if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
        fractol->x_shift += (fractol->max_x - fractol->min_x) * 0.1;
        //fractol->x_shift += (0.5 * fractol->zoom);
    if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
        fractol->x_shift -= (fractol->max_x - fractol->min_x) * 0.1;
        //fractol->x_shift -= (0.5 * fractol->zoom);
    ft_fractol(fractol);
}

void    ft_init(t_fractol *fractol)
{
    fractol->zoom = 1.0;
    fractol->x_shift = 0.0;
    fractol->y_shift = 0.0;
    fractol->definition = 15;
    fractol->min_x = -2;
    fractol->max_x = 2;
    fractol->min_y = -2;
    fractol->max_y = 2;
}

int main(int argc, char **argv)
{
    t_fractol   fractol;

    fractol.mlx_start = mlx_init(WIDTH, HEIGHT, "mandelbrot", true);
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
}
