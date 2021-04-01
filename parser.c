#include "parser.h"

void ft_strcpy(char *dst, const char *src)
{
    while (*src)
    {
        *dst = *src;
        dst++;
        src++;
    }
}

int check_r(char *map_line, t_map *map_info)
{
    if (map_info->win_h || map_info->win_w)
        return (-1);
    map_line++;
    while (*map_line == ' ')
        map_line++;
    if (!(*map_line >= '0' && *map_line <= '9'))
        return (-1);
    map_info->win_w = ft_atoi(map_line);
    while (*map_line >= '0' && *map_line <= '9')
        map_line++;
    while (*map_line == ' ')
        map_line++;
    if (!(*map_line >= '0' && *map_line <= '9'))
        return (-1);
    map_info->win_h = ft_atoi(map_line);
    while (*map_line >= '0' && *map_line <= '9')
        map_line++;
    if (*map_line)
        return (-1);
    return (0);
}

int set_walls(char *map_line, t_map *map_info, int *i)
{
    if (map_line[0] == 'N')
    {
        if (map_info->no)
            return (-1);
        map_info->no = ft_strdup(&(map_line[*i]));
    }
    else if (map_line[0] == 'W')
    {
        if (map_info->we)
            return (-1);
        map_info->we = ft_strdup(&(map_line[*i]));
    }
    else if (map_line[0] == 'E')
    {
        if (map_info->ea)
            return (-1);
        map_info->ea = ft_strdup(&(map_line[*i]));
    }
    else if (map_line[0] == 'S' && map_line[1] == 'O')
    {
        if (map_info->so)
            return (-1);
        map_info->so = ft_strdup(&(map_line[*i]));
    }
    return (0);
}

int check_sides(char *map_line, t_map *map_info)
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
    if (set_walls(map_line, map_info, &i) < 0)
        return (-1);
    else if (map_line[0] == 'S' && map_line[1] == ' ')
    {
        if (map_info->s)
            return (-1);
        map_info->s = ft_strdup(&(map_line[i]));
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

int check_let(char **map, t_map *map_info)
{
    int i;

    i = -1;
    while (++i < 8 && map[i])
    {
        if (map[i][0] == 'R' && map[i][1] == ' ')
        {
            if (check_r(map[i], map_info) < 0)
                return (-2);
        }
        else if (verify_sides(map, &i))
        {
            if (check_sides(map[i], map_info) < 0)
                return (-3);
        }
        else if (verify_f_c(map, &i))
        {
            if (check_f_c(map[i], map_info) < 0)
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
    if (info->win_h <= 0 || info->win_w <= 0)
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

void set_n(t_map *map_info)
{
    map_info->dirX = 0;
    map_info->dirY = -1;
    map_info->planeX = 0.57;
    map_info->planeY = 0;
}

void set_s(t_map *map_info)
{
    map_info->dirX = 0;
    map_info->dirY = 1;
    map_info->planeX = -0.57;
    map_info->planeY = 0;
}

void set_w(t_map *map_info)
{
    map_info->dirX = -1;
    map_info->dirY = 0;
    map_info->planeX = 0;
    map_info->planeY = -0.57;
}

void set_e(t_map *map_info)
{
    map_info->dirX = 1;
    map_info->dirY = 0;
    map_info->planeX = 0;
    map_info->planeY = 0.57;
}

void set_dir(t_map *map_info, char letter)
{
    if (letter == 'N')
        set_n(map_info);
    else if (letter == 'S')
        set_s(map_info);
    else if (letter == 'W')
        set_w(map_info);
    else if (letter == 'E')
        set_e(map_info);
}

int check_player(char **map_arr, t_map *map_info)
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
                map_info->x_player = j;
                map_info->y_player = i;
                set_dir(map_info, map_arr[i][j]);
                count++;
            }
            j++;
        }
    }
    if (count != 1)
        return (-9);
    return (0);
}

int flood_fill(char ***map_arr, int x, int y, t_map map_info)
{
    if (x < 0 || x > map_info.str_len ||
        y < 8 || y >= map_info.map_len + 8 ||
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
    if (flood_fill(map_arr, x, y + 1, map_info) < 0)
        return (-1);
    if (flood_fill(map_arr, x + 1, y, map_info) < 0)
        return (-1);
    if (flood_fill(map_arr, x - 1, y, map_info) < 0)
        return (-1);
    if (flood_fill(map_arr, x, y - 1, map_info) < 0)
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

int check_map(char ***map, t_map map_info)
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
                if (flood_fill(map, j, i, map_info) < 0)
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
    m->no_text.img = mlx_xpm_file_to_image(m->mlx, m->no, &m->no_text.width, &m->no_text.height);
    if (m->no_text.img == NULL)
        return (-13);
    m->no_text.addr = mlx_get_data_addr(m->no_text.img, &m->no_text.bits_per_pixel, &m->no_text.line_length, &m->no_text.endian);
    m->so_text.img = mlx_xpm_file_to_image(m->mlx, m->so, &m->so_text.width, &m->so_text.height);
    if (m->so_text.img == NULL)
        return (-13);
    m->so_text.addr = mlx_get_data_addr(m->so_text.img, &m->so_text.bits_per_pixel, &m->so_text.line_length, &m->so_text.endian);
    m->ea_text.img = mlx_xpm_file_to_image(m->mlx, m->ea, &m->ea_text.width, &m->ea_text.height);
    if (m->ea_text.img == NULL)
        return (-13);
    m->ea_text.addr = mlx_get_data_addr(m->ea_text.img, &m->ea_text.bits_per_pixel, &m->ea_text.line_length, &m->ea_text.endian);
    m->we_text.img = mlx_xpm_file_to_image(m->mlx, m->we, &m->we_text.width, &m->we_text.height);
    if (m->we_text.img == NULL)
        return (-13);
    m->we_text.addr = mlx_get_data_addr(m->we_text.img, &m->we_text.bits_per_pixel, &m->we_text.line_length, &m->we_text.endian);
    return (0);
}

int load_sprites(t_map *m)
{
    m->spr.img = mlx_xpm_file_to_image(m->mlx, m->s, &m->spr.width, &m->spr.height);
    if (m->spr.img == NULL)
        return (-14);
    m->spr.addr = mlx_get_data_addr(m->spr.img, &m->spr.bits_per_pixel, &m->spr.line_length, &m->spr.endian);
    return (0);
}

int spr_arr(t_map *map_info, t_spr **sprites, int q)
{
    int i;
    int j;
    int k;

    i = 0;
    k = 0;
    if (!(*sprites = (t_spr *)malloc(sizeof(t_spr) * q)))
        return (-1);
    while (i < map_info->map_len)
    {
        j = 0;
        while (j < map_info->str_len)
        {
            if (map_info->map[i][j] == '2')
            {
                (*sprites)[k].x = j + 0.5;
                (*sprites)[k].y = i + 0.5;
                map_info->map[i][j] = '0';
                k++;
            }
            j++;
        }
        i++;
    }
    return (0);
}

int find_sprites(t_map *map_info, t_spr **sprites)
{
    int i;
    int j;
    int k;
    int quantity;

    i = 0;
    j = 0;
    k = 0;
    quantity = 0;
    while (i < map_info->map_len)
    {
        j = 0;
        while (j < map_info->str_len)
        {
            if (map_info->map[i][j] == '2')
                quantity++;
            j++;
        }
        i++;
    }
    if (spr_arr(map_info, sprites, quantity) < 0)
        return (-100);
    return (quantity);
}