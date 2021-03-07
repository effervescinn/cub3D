// #include <mlx.h>

// typedef struct  s_vars {
//         void    *mlx;
//         void    *win;
// }               t_vars;

// int             close(int keycode, t_vars *vars)
// {
//     if (keycode == 53)
//         mlx_destroy_window(vars->mlx, vars->win);
//     // printf("%d\n", keycode);
//     return 0;
// }

// int             main(void)
// {
//     t_vars    vars;

//     vars.mlx = mlx_init();
//     vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
//     mlx_hook(vars.win, 2, 1L<<0, close, &vars);
//     mlx_loop(vars.mlx);
// } 

#include <mlx.h>

typedef struct  s_vars {
        void    *mlx;
        void    *win;
}               t_vars;


int     render_next_frame(void *YourStruct)
{
    YourStruct->win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
}
int     main(void)
{
    t_vars      vars;
    // void    *mlx;
    // void    *mlx_win;

    vars.mlx = mlx_init();
    
    mlx_loop_hook(vars.mlx, render_next_frame, &vars);
    mlx_loop(vars.mlx);
}