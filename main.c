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

int     main(void)
{
    t_vars vars;
    t_img image;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "test");
    mlx_key_hook(vars.win, key_hook, &vars);
    // mlx_hook(vars.win, 17, 1L<<15, key_hook, &vars);
    mlx_loop(vars.mlx);
}