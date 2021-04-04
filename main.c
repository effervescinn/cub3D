#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

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


int key_hook(int keycode, t_vars *vars)
{
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->win);
    }
    exit(0);
    return (0);
}

void my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int     main(void)
{
    t_vars vars;
    // t_img image;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "test");
    // mlx_key_hook(vars.win, key_hook, &vars);
    // mlx_hook(vars.win, 17, 1L<<15, key_hook, &vars);
    vars.img = mlx_new_image(vars.mlx, 640, 480);
    vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
    my_mlx_pixel_put(&vars, 0, 0, 0xE9C0B6);
    my_mlx_pixel_put(&vars, 1, 0, 0xE9C0B6);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
    for (int i = 0; i < 8; i++)
    {
        printf("%u\n", vars.addr[i] & 0x0000FF);
    }
    // printf("%x\n%x\n%x\n%x\n", vars.addr[0], vars.addr[1], vars.addr[2], vars.addr[3]);
    mlx_loop(vars.mlx);
}