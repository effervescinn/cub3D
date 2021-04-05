#include <stdio.h>
#include "libft/libft.h"
#include <mlx.h>
#include "parser.h"
#include "raycast.h"
#include "main.h"

#define ERROR "Error"
#define FD_ERROR "Wrong file"
#define RES_ERROR "Resolution error"
#define TEXT_ERROR "Textures error"
#define F_C_ERROR "Floor or ceiling error"
#define ODD_ERROR "Odd line"
#define MISS_ERROR "Missed information"
#define RES_SIZE_ERROR "Wrong resolution"
#define COLOR_ERROR "Wrong colors"
#define PLAYER_ERROR "Player is not one"
#define MAP_ERROR "Invalid map"
#define XPM_WALL_ERROR "Invalid texture format"
#define XPM_SPRITE_ERROR "Invalid sprite format"
#define WRONG_TEXTURES "Can't load textures"
#define WRONG_SPRITE "Can't load sprite"
#define MALLOC_ERROR "Malloc error"
#define IMAGE_ERROR "Image error"
#define WINDOW_ERROR "Window error"

void my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->ll + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}

int make_color(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void free_arr(char ***arr)
{
    int i;

    i = 0;
    while ((*arr)[i])
    {
        free((*arr)[i]);
        i++;
    }
    free(*arr);
}

void draw_f_c(t_map *m)
{
    int i;
    int j;
    int c_color;
    int f_color;

    i = 0;
    c_color = make_color(m->ceil.r, m->ceil.g, m->ceil.b);
    f_color = make_color(m->floor.r, m->floor.g, m->floor.b);
    while (i < (m->win_h / 2))
    {
        j = -1;
        while (++j < m->win_w)
            my_mlx_pixel_put(m, j, i, c_color);
        i++;
    }
    while (i < (m->win_h))
    {
        j = -1;
        while (++j < m->win_w)
            my_mlx_pixel_put(m, j, i, f_color);
        i++;
    }
}

void sort_sprites(int *spriteOrder, double *spriteDistance, int len)
{
    int i;
    int j;
    double dist_perm;
    int order_perm;

    i = 0;
    while (i < len - 1)
    {
        j = len - 1;
        while (j > i)
        {
            if (spriteDistance[j - 1] < spriteDistance[j])
            {
                dist_perm = spriteDistance[j - 1];
                order_perm = spriteOrder[j - 1];
                spriteDistance[j - 1] = spriteDistance[j];
                spriteDistance[j] = dist_perm;
                spriteOrder[j - 1] = spriteOrder[j];
                spriteOrder[j] = order_perm;
            }
            j--;
        }
        i++;
    }
}

int esc_close(int keycode)
{
    if (keycode == 53)
        exit(0);
    return (0);
}

int close_all(t_map *m)
{
    free(m->sprites);
    free_arr(&(m->map));
    mlx_destroy_image(m->mlx, m->img);
    if (m->win)
        mlx_destroy_window(m->mlx, m->win);
    exit(0);
    return (0);
}

void l_r_hook(t_map *m)
{
    double oldPlaneX;
    double oldDirX;
    double rotSpeed;
    double moveSpeed;

    rotSpeed = 0.03;
    moveSpeed = 0.08;
    if (m->keys.left == 1)
    {
        oldDirX = m->dirX;
        m->dirX = m->dirX * cos(-rotSpeed) - m->dirY * sin(-rotSpeed);
        m->dirY = (oldDirX * sin(-rotSpeed) + m->dirY * cos(-rotSpeed));
        oldPlaneX = m->planeX;
        m->planeX = (m->planeX * cos(-rotSpeed) - m->planeY * sin(-rotSpeed));
        m->planeY = (oldPlaneX * sin(-rotSpeed) + m->planeY * cos(-rotSpeed));
    }
    if (m->keys.right == 1)
    {
        oldDirX = m->dirX;
        m->dirX = m->dirX * cos(rotSpeed) - m->dirY * sin(rotSpeed);
        m->dirY = (oldDirX * sin(rotSpeed) + m->dirY * cos(rotSpeed));
        oldPlaneX = m->planeX;
        m->planeX = (m->planeX * cos(rotSpeed) - m->planeY * sin(rotSpeed));
        m->planeY = (oldPlaneX * sin(rotSpeed) + m->planeY * cos(rotSpeed));
    }
}

void esc_hook(t_map *m)
{
    if (m->keys.esc == 1)
        close_all(m);
}

void w_s_hook(t_map *m)
{
    double rotSpeed;
    double moveSpeed;

    rotSpeed = 0.03;
    moveSpeed = 0.08;
    if (m->keys.w == 1)
    {
        if (m->map[(int)(m->posY + (m->dirY) * moveSpeed)][(int)(m->posX)] != '1')
            m->posY += (m->dirY) * moveSpeed;
        if (m->map[(int)(m->posY)][(int)(m->posX + (m->dirX) * moveSpeed)] != '1')
            m->posX += (m->dirX) * moveSpeed;
    }
    if (m->keys.s == 1)
    {
        if (m->map[(int)(m->posY - (m->dirY) * moveSpeed)][(int)(m->posX)] != '1')
            m->posY -= (m->dirY) * moveSpeed;
        if (m->map[(int)(m->posY)][(int)(m->posX - (m->dirX) * moveSpeed)] != '1')
            m->posX -= (m->dirX) * moveSpeed;
    }
}

void a_d_hook(t_map *m)
{
    double rotSpeed;
    double moveSpeed;

    rotSpeed = 0.03;
    moveSpeed = 0.08;
    if (m->keys.a == 1)
    {
        if (m->map[(int)(m->posY - (m->dirX) * moveSpeed)][(int)(m->posX)] != '1')
            m->posY -= (m->dirX) * moveSpeed;
        if (m->map[(int)(m->posY)][(int)(m->posX + (m->dirY) * moveSpeed)] != '1')
            m->posX += (m->dirY) * moveSpeed;
    }
    if (m->keys.d == 1)
    {
        if (m->map[(int)(m->posY + (m->dirX) * moveSpeed)][(int)(m->posX)] != '1')
            m->posY += (m->dirX) * moveSpeed;
        if (m->map[(int)(m->posY)][(int)(m->posX - (m->dirY) * moveSpeed)] != '1')
            m->posX -= (m->dirY) * moveSpeed;
    }
}

int key_hook(t_map *m)
{
    esc_hook(m);
    l_r_hook(m);
    w_s_hook(m);
    a_d_hook(m);
    draw_picture(m);
    return (0);
}

int pressed_key(int keycode, t_map *m)
{
    if (keycode == KEY_W)
        m->keys.w = 1;
    if (keycode == KEY_S)
        m->keys.s = 1;
    if (keycode == KEY_A)
        m->keys.a = 1;
    if (keycode == KEY_D)
        m->keys.d = 1;
    if (keycode == KEY_LEFT)
        m->keys.left = 1;
    if (keycode == KEY_RIGHT)
        m->keys.right = 1;
    if (keycode == ESC)
        m->keys.esc = 1;
    return (0);
}

int unpressed_key(int keycode, t_map *m)
{
    if (keycode == KEY_W)
        m->keys.w = 0;
    if (keycode == KEY_S)
        m->keys.s = 0;
    if (keycode == KEY_A)
        m->keys.a = 0;
    if (keycode == KEY_D)
        m->keys.d = 0;
    if (keycode == KEY_LEFT)
        m->keys.left = 0;
    if (keycode == KEY_RIGHT)
        m->keys.right = 0;
    return (0);
}

void track_hooks(t_map *m)
{
    mlx_loop_hook(m->mlx, key_hook, m);
    mlx_hook(m->win, 2, 0, pressed_key, m);
    mlx_hook(m->win, 17, 0, close_all, m);
    mlx_hook(m->win, 3, 0, unpressed_key, m);
    mlx_loop(m->mlx);
}

void set_struct(t_map *m)
{
    m->win = NULL;
    m->win_h = 0;
    m->win_w = 0;
    m->no = NULL;
    m->so = NULL;
    m->we = NULL;
    m->ea = NULL;
    m->s = NULL;
    m->floor.type = NULL;
    m->ceil.type = NULL;
    m->screenshot = 0;
}

void print_err(int err)
{
    if (err == -2)
        printf("%s\n%s\n", ERROR, RES_ERROR);
    else if (err == -3)
        printf("%s\n%s\n", ERROR, TEXT_ERROR);
    else if (err == -4)
        printf("%s\n%s\n", ERROR, F_C_ERROR);
    else if (err == -5)
        printf("%s\n%s\n", ERROR, ODD_ERROR);
    else if (err == -6)
        printf("%s\n%s\n", ERROR, MISS_ERROR);
    else if (err == -7)
        printf("%s\n%s\n", ERROR, RES_SIZE_ERROR);
    else if (err == -8)
        printf("%s\n%s\n", ERROR, COLOR_ERROR);
    else if (err == -9)
        printf("%s\n%s\n", ERROR, PLAYER_ERROR);
    else if (err == -10)
        printf("%s\n%s\n", ERROR, MAP_ERROR);
    else if (err == -11)
        printf("%s\n%s\n", ERROR, XPM_WALL_ERROR);
    else if (err == -12)
        printf("%s\n%s\n", ERROR, XPM_SPRITE_ERROR);
    else if (err == -13)
        printf("%s\n%s\n", ERROR, WRONG_TEXTURES);
    else if (err == -14)
        printf("%s\n%s\n", ERROR, WRONG_SPRITE);
    else if (err == -15)
        printf("%s\n%s\n", ERROR, IMAGE_ERROR);
    else if (err == -16)
        printf("%s\n%s\n", ERROR, WINDOW_ERROR);
    else if (err == -17)
        printf("%s\n%s\n", ERROR, FD_ERROR);
    else if (err == -100)
        printf("%s\n%s\n", ERROR, MALLOC_ERROR);
}

int write_info(char ***map, t_map *m, char **argv)
{
    int fd;
    int ret;
    int err;
    char map_str[BUF_SIZE + 1];

    if (((fd = open(argv[1], O_RDWR)) < 0))
    {
        print_err(-17);
        return (-1);
    }
    while ((ret = read(fd, map_str, BUF_SIZE)))
        map_str[ret] = '\0';
    close(fd);
    if (!(*map = ft_split(map_str, '\n')))
    {
        print_err(-100);
        return (-1);
    }
    if ((err = check_info(*map, m)) < 0)
    {
        print_err(err);
        free_arr(map);
        return (-1);
    }
    return (0);
}

void big_res(t_map *m)
{
    int sizex;
    int sizey;

    mlx_get_screen_size(&sizex, &sizey);
    if (m->win_h > sizey)
        m->win_h = sizey;
    if (m->win_w > (int)((double)sizey * 1.778))
        m->win_w = (int)((double)sizey * 1.778);
}

void calloc_clean(t_map *m, char ***map)
{
    int i;

    i = 0;
    while (m->map[i])
    {
        free(m->map[i]);
        i++;
    }
    free_arr(map);
}

int copy_map(t_map *m, char ***map)
{
    int i;

    i = -1;
    m->str_len = longest_str(*map);
    m->map_len = count_map_len(*map, 8);
    if (!(m->map = (char **)malloc((m->map_len + 1) * sizeof(char *))))
    {
        print_err(-100);
        free_arr(map);
        return (-1);
    }
    while (++i < m->map_len)
    {
        if (!(m->map[i] = ft_calloc(m->str_len + 1, 1)))
        {
            calloc_clean(m, map);
            return (-1);
        }
    }
    m->map[i] = NULL;
    i = -1;
    while (++i < m->map_len)
        ft_strcpy(m->map[i], (*map)[i + 8]);
    return (0);
}

int check_conf(t_map *m, char ***map, int *err)
{
    if ((*err = check_player(m->map, m)) < 0)
    {
        print_err(*err);
        free_arr(&(m->map));
        free_arr(map);
        return (-1);
    }
    if ((*err = check_map(map, *m)) < 0)
    {
        print_err(*err);
        free_arr(&(m->map));
        free_arr(map);
        return (-1);
    }
    if ((*err = find_sprites(m, &(m->sprites))) < 0)
    {
        print_err(*err);
        free_arr(&(m->map));
        free_arr(map);
        return (-1);
    }
    free_arr(map);
    return (0);
}

void destroy_text(t_map *m)
{
    if (m->no_t.img)
        mlx_destroy_image(m->mlx, m->no_t.img);
    if (m->so_t.img)
        mlx_destroy_image(m->mlx, m->so_t.img);
    if (m->we_t.img)
        mlx_destroy_image(m->mlx, m->we_t.img);
    if (m->ea_t.img)
        mlx_destroy_image(m->mlx, m->ea_t.img);
}

void destroy_spr(t_map *m)
{
    if (m->spr.img)
        mlx_destroy_image(m->mlx, m->spr.img);
}

int load_images(t_map *m, int *err)
{
    if ((*err = load_textures(m)) < 0)
    {
        print_err(*err);
        free(m->sprites);
        free_arr(&(m->map));
        destroy_text(m);
        return (-1);
    }
    if ((*err = load_sprites(m)) < 0)
    {
        print_err(*err);
        free(m->sprites);
        free_arr(&(m->map));
        return (-1);
    }
    return (0);
}

int main_image(t_map *m)
{
    m->img = mlx_new_image(m->mlx, m->win_w, m->win_h);
    if (m->img == NULL)
    {
        print_err(-15);
        if (m->win)
            mlx_destroy_window(m->mlx, m->win);
        free(m->sprites);
        free(m->map);
        return (-1);
    }
    m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->ll, &m->end);
    m->posX = (double)m->x_player + 0.5;
    m->posY = (double)m->y_player + 0.5;
    return (0);
}

int check_args(t_map *m, int argc, char **argv)
{
    if (!(argc == 3 && !ft_strncmp(argv[2], "--save", 6)))
    {
        if (!(m->win = mlx_new_window(m->mlx, m->win_w, m->win_h, "cub3D")))
        {
            print_err(-16);
            free(m->sprites);
            free_arr(&(m->map));
            destroy_text(m);
            destroy_spr(m);
            return (-1);
        }
    }
    else if (argc == 3 && !ft_strncmp(argv[2], "--save", 6))
        m->screenshot = 1;
    return (0);
}

int main(int argc, char **argv)
{
    char **map;
    t_map map_info;
    int err;

    set_struct(&map_info);
    if ((write_info(&map, &map_info, argv) < 0))
        return (-1);
    if ((copy_map(&map_info, &map) < 0))
        return (-1);
    if ((check_conf(&map_info, &map, &err) < 0))
        return (-1);
    map_info.mlx = mlx_init();
    if ((load_images(&map_info, &err) < 0))
        return (-1);
    big_res(&map_info);
    if ((check_args(&map_info, argc, argv) < 0))
        return (-1);
    mlx_do_key_autorepeatoff(map_info.mlx);
    if ((main_image(&map_info) < 0))
        return (-1);
    draw_picture(&map_info);
    track_hooks(&map_info);
    return (0);
}
