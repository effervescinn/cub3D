#include "main.h"

int check_r(char *map_line, t_map *main_info)
{
    if (main_info->winh || main_info->winw)
        return (-1);
    map_line++;
    while (*map_line == ' ')
        map_line++;
    if (!(*map_line >= '0' && *map_line <= '9'))
        return (-1);
    main_info->winw = ft_atoi(map_line);
    while (*map_line >= '0' && *map_line <= '9')
        map_line++;
    while (*map_line == ' ')
        map_line++;
    if (!(*map_line >= '0' && *map_line <= '9'))
        return (-1);
    main_info->winh = ft_atoi(map_line);
    while (*map_line >= '0' && *map_line <= '9')
        map_line++;
    if (*map_line)
        return (-1);
    return (0);
}

int set_walls(char *map_line, t_map *main_info, int *i)
{
    if (map_line[0] == 'N')
    {
        if (main_info->no)
            return (-1);
        main_info->no = ft_strdup(&(map_line[*i]));
    }
    else if (map_line[0] == 'W')
    {
        if (main_info->we)
            return (-1);
        main_info->we = ft_strdup(&(map_line[*i]));
    }
    else if (map_line[0] == 'E')
    {
        if (main_info->ea)
            return (-1);
        main_info->ea = ft_strdup(&(map_line[*i]));
    }
    else if (map_line[0] == 'S' && map_line[1] == 'O')
    {
        if (main_info->so)
            return (-1);
        main_info->so = ft_strdup(&(map_line[*i]));
    }
    return (0);
}

int check_sides(char *map_line, t_map *main_info)
{
    int i;

    i = 0;
    if (map_line[i] == 'S' && map_line[i + 1] == ' ')
        i += 1;
    else
        i += 2;
    if (map_line[i++] != ' ' || !map_line[i])
        return (-1);
    while (map_line[i] == ' ')
        i++;
    if (map_line[i] == '\0')
        return (-1);
    if (set_walls(map_line, main_info, &i) < 0)
        return (-1);
    else if (map_line[0] == 'S' && map_line[1] == ' ')
    {
        if (main_info->s)
            return (-1);
        main_info->s = ft_strdup(&(map_line[i]));
    }
    return (0);
}

int set_f_c(char *map_line, t_color *c_type)
{
    while (*map_line == ' ')
        map_line++;
    if (!(*map_line >= '0' && *map_line <= '9'))
        return (-1);
    c_type->r = ft_atoi(map_line);
    while (*map_line >= '0' && *map_line <= '9')
        map_line++;
    if (*(map_line++) != ',')
        return (-1);
    if (!(*map_line >= '0' && *map_line <= '9'))
        return (-1);
    c_type->g = ft_atoi(map_line);
    while (*map_line >= '0' && *map_line <= '9')
        map_line++;
    if (*(map_line++) != ',')
        return (-1);
    if (!(*map_line >= '0' && *map_line <= '9'))
        return (-1);
    c_type->b = ft_atoi(map_line);
    while (*map_line >= '0' && *map_line <= '9')
        map_line++;
    if (*map_line)
        return (-1);
    return (0);
}

int check_f_c(char *map_line, t_map *m)
{
    if (*map_line == 'F')
    {
        if (m->floor.type)
            return (-1);
        m->floor.type = "F";
        map_line++;
        if (set_f_c(map_line, &(m->floor)) < 0)
            return (-1);
    }
    if (*map_line == 'C')
    {
        if (m->ceil.type)
            return (-1);
        m->ceil.type = "C";
        map_line++;
        if (set_f_c(map_line, &(m->ceil)) < 0)
            return (-1);
    }
    return (0);
}

int verify_sides(char **map, int *i)
{
    if ((map[*i][0] == 'N' && map[*i][1] == 'O') ||
        (map[*i][0] == 'S' && map[*i][1] == 'O') ||
        (map[*i][0] == 'W' && map[*i][1] == 'E') ||
        (map[*i][0] == 'E' && map[*i][1] == 'A') ||
        (map[*i][0] == 'S' && map[*i][1] == ' '))
        return (1);
    else
        return (0);
}

int verify_f_c(char **map, int *i)
{
    if ((map[*i][0] == 'F' && map[*i][1] == ' ') ||
        (map[*i][0] == 'C' && map[*i][1] == ' '))
        return (-1);
    else
        return (0);
}

int check_let(char **map, t_map *main_info)
{
    int i;

    i = -1;
    while (++i < 8 && map[i])
    {
        if (map[i][0] == 'R' && map[i][1] == ' ')
        {
            if (check_r(map[i], main_info) < 0)
                return (-2);
        }
        else if (verify_sides(map, &i))
        {
            if (check_sides(map[i], main_info) < 0)
                return (-3);
        }
        else if (verify_f_c(map, &i))
        {
            if (check_f_c(map[i], main_info) < 0)
                return (-4);
        }
        else
            return (-5);
    }
    return (0);
}

int check_n_s_xpm(t_map *info)
{
    int i;

    i = ft_strlen(info->no);
    if (i < 5)
        return (-11);
    i--;
    if (info->no[i] != 'm' || info->no[i - 1] != 'p' ||
        info->no[i - 2] != 'x' || info->no[i - 3] != '.')
        return (-11);
    i = ft_strlen(info->so);
    if (i < 5)
        return (-11);
    i--;
    if (info->so[i] != 'm' || info->so[i - 1] != 'p' ||
        info->so[i - 2] != 'x' || info->so[i - 3] != '.')
        return (-11);
    return (0);
}

int check_w_e_xpm(t_map *info)
{
    int i;

    i = ft_strlen(info->we);
    if (i < 5)
        return (-11);
    i--;
    if (info->we[i] != 'm' || info->we[i - 1] != 'p' ||
        info->we[i - 2] != 'x' || info->we[i - 3] != '.')
        return (-11);
    i = ft_strlen(info->ea);
    if (i < 5)
        return (-11);
    i--;
    if (info->ea[i] != 'm' || info->ea[i - 1] != 'p' ||
        info->ea[i - 2] != 'x' || info->ea[i - 3] != '.')
        return (-11);
    return (0);
}

int check_spr_xpm(t_map *info)
{
    int i;

    i = ft_strlen(info->s);
    if (i < 5)
        return (-12);
    i--;
    if (info->s[i] != 'm' || info->s[i - 1] != 'p' ||
        info->s[i - 2] != 'x' || info->s[i - 3] != '.')
        return (-12);
    return (0);
}

int check_info(char **map, t_map *info)
{
    int ret;

    if ((ret = check_let(map, info)) < 0)
        return (ret);
    if ((ret = check_n_s_xpm(info)) < 0)
        return (ret);
    if ((ret = check_w_e_xpm(info)) < 0)
        return (ret);
    if ((ret = check_spr_xpm(info)) < 0)
        return (ret);
    if (!(info->no) || !(info->so) || !(info->we) || !(info->ea) || 
    !(info->ea) || !(info->floor.type) || !(info->ceil.type))
        return (-6);
    if (info->winh <= 0 || info->winw <= 0)
        return (-7);
    if (!(info->floor.b >= 0 && info->floor.b <= 255) ||
        !(info->floor.r >= 0 && info->floor.r <= 255) ||
        !(info->floor.g >= 0 && info->floor.g <= 255) ||
        !(info->ceil.g >= 0 && info->ceil.g <= 255) ||
        !(info->ceil.r >= 0 && info->ceil.r <= 255) ||
        !(info->ceil.b >= 0 && info->ceil.b <= 255))
        return (-8);
    return (0);
}

int count_map_len(char **map, int i)
{
    int map_len;

    map_len = 0;
    while (map[i])
    {
        map_len++;
        i++;
    }
    return (map_len);
}

void set_n(t_map *main_info)
{
    main_info->dx = 0;
    main_info->dy = -1;
    main_info->px = 0.57;
    main_info->py = 0;
}

void set_s(t_map *main_info)
{
    main_info->dx = 0;
    main_info->dy = 1;
    main_info->px = -0.57;
    main_info->py = 0;
}

void set_w(t_map *main_info)
{
    main_info->dx = -1;
    main_info->dy = 0;
    main_info->px = 0;
    main_info->py = -0.57;
}

void set_e(t_map *main_info)
{
    main_info->dx = 1;
    main_info->dy = 0;
    main_info->px = 0;
    main_info->py = 0.57;
}

void set_dir(t_map *main_info, char letter)
{
    if (letter == 'N')
        set_n(main_info);
    else if (letter == 'S')
        set_s(main_info);
    else if (letter == 'W')
        set_w(main_info);
    else if (letter == 'E')
        set_e(main_info);
}

int check_player(char **map_arr, t_map *main_info)
{
    int i;
    int j;
    int count;

    i = -1;
    count = 0;
    while (map_arr[++i])
    {
        j = 0;
        while (map_arr[i][j])
        {
            if (map_arr[i][j] == 'N' || map_arr[i][j] == 'E' ||
                map_arr[i][j] == 'W' || map_arr[i][j] == 'S')
            {
                main_info->x_player = j;
                main_info->y_player = i;
                set_dir(main_info, map_arr[i][j]);
                count++;
            }
            j++;
        }
    }
    if (count != 1)
        return (-9);
    return (0);
}

int flood_fill(char ***map_arr, int x, int y, t_map main_info)
{
    if (x < 0 || x > main_info.str_len ||
        y < 8 || y >= main_info.map_len + 8 ||
        !((*map_arr)[y][x] == 'N' || (*map_arr)[y][x] == 'W' ||
          (*map_arr)[y][x] == 'E' || (*map_arr)[y][x] == 'S' ||
          (*map_arr)[y][x] == '0' || (*map_arr)[y][x] == '2' ||
          (*map_arr)[y][x] == '1'))
        return (-1);
    if ((*map_arr)[y][x] == '1')
        return (1);
    if ((*map_arr)[y][x] == 'N' || (*map_arr)[y][x] == 'W' ||
        (*map_arr)[y][x] == 'E' || (*map_arr)[y][x] == 'S' ||
        (*map_arr)[y][x] == '0' || (*map_arr)[y][x] == '2')
        (*map_arr)[y][x] = '1';
    if (flood_fill(map_arr, x, y + 1, main_info) < 0)
        return (-1);
    if (flood_fill(map_arr, x + 1, y, main_info) < 0)
        return (-1);
    if (flood_fill(map_arr, x - 1, y, main_info) < 0)
        return (-1);
    if (flood_fill(map_arr, x, y - 1, main_info) < 0)
        return (-1);
    return (0);
}

int longest_str(char **map)
{
    int i;
    int max_len;

    i = 8;
    max_len = 0;
    while (map[i])
    {
        if ((int)ft_strlen(map[i]) > max_len)
            max_len = ft_strlen(map[i]);
        i++;
    }
    return (max_len);
}

int check_map(char ***map, t_map main_info)
{
    int i;
    int j;

    i = 8;
    j = 0;
    while ((*map)[i])
    {
        j = 0;
        while ((*map)[i][j])
        {
            if ((*map)[i][j] == '0' || (*map)[i][j] == '2' ||
                (*map)[i][j] == 'N' || (*map)[i][j] == 'E' ||
                (*map)[i][j] == 'S' || (*map)[i][j] == 'W')
            {
                if (flood_fill(map, j, i, main_info) < 0)
                    return (-10);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int load_textures(t_map *m)
{
    m->no_t.img = mlx_xpm_file_to_image(m->mlx, m->no, &m->no_t.w, &m->no_t.h);
    if (m->no_t.img == NULL)
        return (-13);
    m->no_t.ad = get_ad(m->no_t.img, &m->no_t.bpp, &m->no_t.ll, &m->no_t.end);
    m->so_t.img = mlx_xpm_file_to_image(m->mlx, m->so, &m->so_t.w, &m->so_t.h);
    if (m->so_t.img == NULL)
        return (-13);
    m->so_t.ad = get_ad(m->so_t.img, &m->so_t.bpp, &m->so_t.ll, &m->so_t.end);
    m->ea_t.img = mlx_xpm_file_to_image(m->mlx, m->ea, &m->ea_t.w, &m->ea_t.h);
    if (m->ea_t.img == NULL)
        return (-13);
    m->ea_t.ad = get_ad(m->ea_t.img, &m->ea_t.bpp, &m->ea_t.ll, &m->ea_t.end);
    m->we_t.img = mlx_xpm_file_to_image(m->mlx, m->we, &m->we_t.w, &m->we_t.h);
    if (m->we_t.img == NULL)
        return (-13);
    m->we_t.ad = get_ad(m->we_t.img, &m->we_t.bpp, &m->we_t.ll, &m->we_t.end);
    return (0);
}

int load_sprites(t_map *m)
{
    m->spr.img = mlx_xpm_file_to_image(m->mlx, m->s, &m->spr.w, &m->spr.h);
    if (m->spr.img == NULL)
        return (-14);
    m->spr.ad = get_ad(m->spr.img, &m->spr.bpp, &m->spr.ll, &m->spr.end);
    return (0);
}

int spr_arr(t_map *main_info, t_spr **sprites, int q)
{
    int i;
    int j;
    int k;

    i = 0;
    k = 0;
    if (!(*sprites = (t_spr *)malloc(sizeof(t_spr) * q)))
        return (-1);
    while (i < main_info->map_len)
    {
        j = 0;
        while (j < main_info->str_len)
        {
            if (main_info->map[i][j] == '2')
            {
                (*sprites)[k].x = j + 0.5;
                (*sprites)[k].y = i + 0.5;
                k++;
            }
            j++;
        }
        i++;
    }
    return (0);
}

int find_sprites(t_map *main_info, t_spr **sprites)
{
    int i;
    int j;
    int k;
    int quantity;

    i = 0;
    j = 0;
    k = 0;
    quantity = 0;
    while (i < main_info->map_len)
    {
        j = 0;
        while (j < main_info->str_len)
        {
            if (main_info->map[i][j] == '2')
                quantity++;
            j++;
        }
        i++;
    }
    if (spr_arr(main_info, sprites, quantity) < 0)
        return (-100);
    main_info->spr_l = quantity;
    return (0);
}