#include "main.h"

void set_struct(t_map *m)
{
    m->win = NULL;
    m->winh = 0;
    m->winw = 0;
    m->no = NULL;
    m->so = NULL;
    m->we = NULL;
    m->ea = NULL;
    m->s = NULL;
    m->floor.type = NULL;
    m->ceil.type = NULL;
    m->screenshot = 0;
}

void err_first(int err)
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
}

void err_second(int err)
{
    if (err == -11)
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

void big_res(t_map *m)
{
    int sizex;
    int sizey;

    mlx_get_screen_size(&sizex, &sizey);
    if (m->winh > sizey)
        m->winh = sizey;
    if (m->winw > (int)((double)sizey * 1.778))
        m->winw = (int)((double)sizey * 1.778);
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
    m->img = mlx_new_image(m->mlx, m->winw, m->winh);
    if (m->img == NULL)
    {
        print_err(-15);
        if (m->win)
            mlx_destroy_window(m->mlx, m->win);
        free(m->sprites);
        free(m->map);
        return (-1);
    }
    m->ad = mlx_get_data_addr(m->img, &m->bpp, &m->ll, &m->end);
    m->x = (double)m->x_player + 0.5;
    m->y = (double)m->y_player + 0.5;
    return (0);
}

int check_args(t_map *m, int argc, char **argv)
{
    if (!(argc == 3 && !ft_strncmp(argv[2], "--save", 6)))
    {
        if (!(m->win = mlx_new_window(m->mlx, m->winw, m->winh, "cub3D")))
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

int main(int argc, char **argv)
{
    char **map;
    t_map main_info;
    int err;

    set_struct(&main_info);
    if ((write_info(&map, &main_info, argv) < 0))
        return (-1);
    if ((copy_map(&main_info, &map) < 0))
        return (-1);
    if ((check_conf(&main_info, &map, &err) < 0))
        return (-1);
    main_info.mlx = mlx_init();
    if ((load_images(&main_info, &err) < 0))
        return (-1);
    big_res(&main_info);
    if ((check_args(&main_info, argc, argv) < 0))
        return (-1);
    mlx_do_key_autorepeatoff(main_info.mlx);
    if ((main_image(&main_info) < 0))
        return (-1);
    draw_picture(&main_info);
    track_hooks(&main_info);
    return (0);
}
