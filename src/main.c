/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:04:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/07/09 12:18:33 by mpellegr         ###   ########.fr       */
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

int    random_n(int n, t_fractol *fractol)
{
    long LCG__A = 1103515245;
    long LCG__C = 12345;
    long LCG__M = 2147483648;
    int lcg__seed = n + fractol->definition;

    lcg__seed = ((LCG__A * lcg__seed + LCG__C) % LCG__M);
    return (lcg__seed);
}

uint32_t get_random_color(int n, t_fractol *fractol)
{
    int r;
    int g;
    int b;

    r = random_n(n, fractol) % 256;
    g = random_n(r, fractol) % 256;
    b = random_n(g, fractol) % 256;
    return (get_rgba(r, g, b, 255));
}

int get_r(int rgba)
{
    // Move 3 bytes to the right and mask out the first byte.
    return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int get_g(int rgba)
{
    // Move 2 bytes to the right and mask out the first byte.
    return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int get_b(int rgba)
{
    // Move 1 byte to the right and mask out the first byte.
    return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int get_a(int rgba)
{
    // Move 0 bytes to the right and mask out the first byte.
    return (rgba & 0xFF);
}

uint32_t    get_scaled_color_1(int color, int new_color, t_fractol *f, int n)
{
    int  rgb_start[3];
    int  rgb_end[3];
    //float ratio;

    rgb_start[0] = get_r(color);
    rgb_start[1] = get_g(color);
    rgb_start[2] = get_b(color);
    rgb_end[0] = get_r(new_color);
    rgb_end[1] = get_g(new_color);
    rgb_end[2] = get_b(new_color);
    //ratio = n / 9.0;
    rgb_start[0] = rgb_start[0] + n * (rgb_end[0] - rgb_start[0])/9;
    rgb_start[1] = rgb_start[1] + n * (rgb_end[1] - rgb_start[1])/9;
    rgb_start[2] = rgb_start[2] + n * (rgb_end[2] - rgb_start[2])/9;
    return (get_rgba(rgb_start[0], rgb_start[1], rgb_start[2], 255));
}

void    create_fractal(int x, int y, t_fractol *f)
{
    t_complex_num       z;
    t_complex_num       c;
    int                 n;
    uint32_t            color;
    int                 iteration;
    int first_color;
    int second_color;

    n = 0;
    //new_color = 0;
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
    first_color = f->start_color;
    second_color = f->random_color;
    while(n < f->definition)
    {
        iteration = n % 10;
        if (iteration == 0 && n > 0)
        {
            first_color = second_color;
            second_color = get_random_color(n, f);
        }
        //printf("iterarion %d, start color = 0x%08X, seond color = 0x%08X\n", n, f->start_color, f->random_color);
        color = get_scaled_color_1(first_color, second_color, f, iteration);
        //printf("color = 0x%08X\n\n", color);
        z = mandelbrot_equation(z, c);
        if ((z.x * z.x) + (z.y * z.y) > 4)
        {
            /*if (n < 10)
                color = get_scaled_color(n, f);
            else
                color  = get_random_color(n, f);
            if (iteration == 0 && n > 0)
            {
                f->start_color = f->random_color;
                f->random_color = get_random_color(n, f);
            }
            color = get_scaled_color_1(f->start_color, f->random_color, f, iteration);*/
            mlx_put_pixel(f->mlx_image, x, y, color);
            return;
        }
        n++;
    }
    mlx_put_pixel(f->mlx_image, x, y, 0x000000FF);
}

int    reverse_scale(double n, double new_min, double new_max, double old_max)
{
    int unscaled_n;

    unscaled_n = (int)((n - new_min) * old_max / (new_max - new_min));
    return (unscaled_n);
}

void init_lcg(int *lcg_seed)
{
    *lcg_seed = 1103527590;
}

int my_rand(int *lcg_seed)
{
    long LCG_A = 1103515245;
    long LCG_C = 12345;
    long LCG_M = 2147483648;
    *lcg_seed = (LCG_A * (*lcg_seed) + LCG_C) % LCG_M;
    return (*lcg_seed);
}

void    create_felce(double x, double y, t_fractol *f)
{
    double  new_x;
    double  new_y;
    int     n;
    int lcg_seed;

    /*f->point = (int **)malloc(WIDTH * sizeof(int *));
    if (f->point == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < WIDTH; i++)
    {
        f->point[i] = (int *)malloc(HEIGHT * sizeof(int));
        if (f->point[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        // Use memset to initialize to 0
        //memset(f->point[i], 0, HEIGHT * sizeof(int));
    }*/
    n = 0;
    /*int a = -1;
    while (++a < WIDTH)
    {
        memset(f->point[a], 0, HEIGHT * sizeof(int));
    }*/
    memset(f->point, 0, WIDTH * HEIGHT * sizeof(unsigned int));
    /*int i = -1;
    while (++i < HEIGHT)
    {
        int j = -1;
        while (++j < WIDTH)
            mlx_put_pixel(f->mlx_image, i, j, 0x000000FF);
    }*/
    int case1 = 0, case2 = 0, case3 = 0, case4 = 0;
    init_lcg(&lcg_seed);
    while (n < f->definition)
    {
        //double rr = (double)rand() / RAND_MAX;
        double r = (double)my_rand(&lcg_seed) / RAND_MAX;
        //printf("my_r = %f\n", r);
        //printf("real_r = %f\n\n", rr);
        if (r < 0.01)
        {
            new_x = 0;
            new_y = 0.16 * y;
            case1++;
        }
        else if (r < 0.86)
        {
            new_x = 0.85 * x + 0.04 * y;
            new_y = -0.04 * x + 0.85 * y + 1.6;
            case2++;
        }
        else if (r < 0.93)
        {
            new_x = 0.2 * x - 0.26 * y;
            new_y = 0.23 * x + 0.22 * y + 0.44;
            case3++;
        }
        else
        {
            new_x = -0.15 * x + 0.28 * y;
            new_y = 0.26 * x + 0.24 * y + 0.44;
            case4++;
        }
        /*
        int a = n % 100;
        printf("a = %d\n", a);
        if (a < 1)
        {
            new_x = 0;
            new_y = 0.16 * y;
            case1++;
        }
        else if (a < 86)
        {
            new_x = 0.85 * x + 0.04 * y;
            new_y = -0.04 * x + 0.85 * y + 1.6;
            case2++;
        }
        else if (a < 93)
        {
            new_x = 0.2 * x - 0.26 * y;
            new_y = 0.23 * x + 0.22 * y + 0.44;
            case3++;
        }
        else
        {
            new_x = -0.15 * x + 0.28 * y;
            new_y = 0.26 * x + 0.24 * y + 0.44;
            case4++;
        }*/
        x = new_x;
        y = new_y;
        //int plotX = (int)((x + 3) * WIDTH / 6);
        //int plotY = HEIGHT - (int)(y * HEIGHT / 10);
        int plotX = reverse_scale(x, f->min_x, f->max_x, WIDTH) + f->x_shift * 10;
        int plotY = reverse_scale(y, f->max_y, f->min_y, HEIGHT) + f->y_shift * 10;
        //printf("x = %f   y = %f\n", x, y);
        //printf("%f + 2.1820) x %d / 4.8378 = %f\n", x, WIDTH)
        //printf("iteration = %d    random = %f   x = %d   y = %d\n", n, r, plotX, plotY);
        //printf("my_x = %d   my_y = %d\n\n", plot_X, plot_Y);   
        if (plotX >= 0 && plotX < WIDTH && plotY >= 0 && plotY < HEIGHT)
            //f->point[plotX][plotY] = 1;
            f->point[plotY * HEIGHT + plotX] = 0x00FF00FF;
        //    mlx_put_pixel(f->mlx_image, plotX, plotY, 0x00FF00FF);
        //printf("x = %d   y = %d   point = %d\n", plotX, plotY, f->point[plotX][plotY]);
        n++;
    }
    //r = 0;
    //printf("\n");
    int i = -1;
    while (++i < HEIGHT)
    {
        int j = -1;
        while (++j < WIDTH)
        {
            int index = j * HEIGHT + i;
            //if (f->point[i][j] == 1)
            if (f->point[index] != 0)
                mlx_put_pixel(f->mlx_image, i, j, f->point[index]);
            else /*if (f->point[i][j] == 0)*/
                mlx_put_pixel(f->mlx_image, i, j, 0x000000FF);
        }
    }
    //printf("definition = %d   case1 = %d   case2 = %d   case3 = %d   case4 = %d\n", f->definition, case1, case2, case3, case4);
}

void    ft_fractol(t_fractol *fractol)
{
    int x;
    int y;

    if (!ft_strcmp_1(fractol->set, "felce"))
        create_felce(0, 0, fractol);
    else
    {
        y = -1;
        while (++y < HEIGHT)
        {
            x = -1;
            while (++x < WIDTH)
                create_fractal(x, y, fractol);
        }
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
    {
        if (!ft_strcmp_1(fractol->set, "felce"))
            fractol->definition += 1000000;
        else
            fractol->definition += 1;
    }
    if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS)
    {
        if (!ft_strcmp_1(fractol->set, "felce"))
            fractol->definition -= 1000000;
        else
            fractol->definition -= 1;
    }
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		fractol->y_shift += (fractol->max_y - fractol->min_y) * 0.1;
    if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		fractol->y_shift -= (fractol->max_y - fractol->min_y) * 0.1;
    if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		fractol->x_shift += (fractol->max_x - fractol->min_x) * 0.1;
    if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		fractol->x_shift -= (fractol->max_x - fractol->min_x) * 0.1;
	ft_fractol(fractol);
}

void    ft_init(t_fractol *fractol)
{
    fractol->zoom = 1.0;
    fractol->x_shift = 0.0;
    fractol->y_shift = 0.0;
    if (!ft_strcmp_1(fractol->set, "felce"))
    {
        fractol->definition = 1000000;
        fractol->min_x = -3;
        fractol->max_x = 3;
        fractol->min_y = 0;
        fractol->max_y = 10;
    }
    else
    {
        fractol->definition = 3;
        fractol->min_x = -2;
        fractol->max_x = 2;
        fractol->min_y = -2;
        fractol->max_y = 2;
        fractol->start_color = 0x000000FF;
        fractol->random_color = get_random_color(0, fractol);
        printf("0x%08X   0x%08X", fractol->start_color, fractol->random_color);
    }
    /*fractol->point = (int **)malloc(WIDTH * sizeof(int *));
    if (fractol->point == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < WIDTH; i++)
    {
        fractol->point[i] = (int *)malloc(HEIGHT * sizeof(int));
        if (fractol->point[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        // Use memset to initialize to 0
        //memset(f->point[i], 0, HEIGHT * sizeof(int));
    }*/
    fractol->point = (int *)malloc(WIDTH * HEIGHT * sizeof(unsigned int));
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
