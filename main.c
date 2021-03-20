// #include <mlx.h>
// #include <stdio.h>

// typedef struct  s_vars
// {
//     void *mlx;
//     void *win;
//     int i;
//     int x;
//     int y;

//     void *img;
//     char *addr;
//     int bits_per_pixel;
//     int line_length;
//     int endian;

//     void *img2;
//     char *addr2;
//     int bits_per_pixel2;
//     int line_length2;
//     int endian2;
// }               t_vars;

// void my_mlx_pixel_put(t_vars *data, int x, int y, int color)
// {
//     char *dst;

//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//     *(unsigned int *)dst = color;
// }

// int key_hook(int keycode, t_vars *vars)
// {
    
//     if (keycode == 123)
//     {
//         mlx_clear_window(vars->mlx, vars->win);
//         my_mlx_pixel_put(vars, vars->x, vars->y, 0xFF0000);
//         mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
//         (vars->x)++;
//         (vars->y)++;
//     }

//     return (0);
// }

// int main(void)
// {
//     t_vars vars;
//     vars.x = 5;
//     vars.y = 5;

//     vars.mlx = mlx_init();
//     vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
//     vars.img = mlx_new_image(vars.mlx, 640, 480);
//     vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);

//     my_mlx_pixel_put(&vars, vars.x, vars.y, 0xFF0000);
    
//     mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
//     mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
//     mlx_loop(vars.mlx);
// }

#include <mlx.h>
#include <stdio.h>

typedef struct  s_vars
{
    void *mlx;
    void *win;
    int i;
    int x;
    int y;

    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
}               t_vars;

typedef struct  s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
}               t_img;

void my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int     main(void)
{
    t_vars vars;
    t_img image;
    char    *relative_path = "redbrick.xpm";
    int     img_width;
    int     img_height;
    char *dst;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "test");

    vars.img = mlx_new_image(vars.mlx, 640, 480);
    vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);

    image.img = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_width, &img_height);
    image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);

    // // printf("%d\n", (int)(*(vars.img)));
    // dst = image.addr + (1 * image.line_length + 1 * (image.bits_per_pixel / 8));
    // unsigned int color = *(unsigned int *)dst;
    // my_mlx_pixel_put(&vars, 300, 300, color);
    // mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
    printf("%d-%d", img_height, img_width);

    // mlx_pixel_put(vars.mlx, vars.win, 300, 300, *(unsigned int *)dst);
    // printf("%u", *(unsigned int *)dst);
    // mlx_loop(vars.mlx);
}