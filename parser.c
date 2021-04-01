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

int check_let(char **map, t_map *map_info)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 8 && map[i])
    {
        if (map[i][j] == 'R' && map[i][j + 1] == ' ')
        {
            if (check_r(map[i], map_info) < 0)
                return (-2);
        }
        else if ((map[i][j] == 'N' && map[i][j + 1] == 'O') ||
                 (map[i][j] == 'S' && map[i][j + 1] == 'O') ||
                 (map[i][j] == 'W' && map[i][j + 1] == 'E') ||
                 (map[i][j] == 'E' && map[i][j + 1] == 'A') ||
                 (map[i][j] == 'S' && map[i][j + 1] == ' '))
        {
            if (check_sides(map[i], map_info) < 0)
                return (-3);
        }
        else if ((map[i][j] == 'F' && map[i][j + 1] == ' ') ||
                 (map[i][j] == 'C' && map[i][j + 1] == ' '))
        {
            if (check_f_c(map[i], map_info) < 0)
                return (-4);
        }
        else
            return (-5);
        i++;
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
    if (info->no[i] != 'm' || info->no[i - 1] != 'p' || info->no[i - 2] != 'x' || info->no[i - 3] != '.')
        return (-11);
    i = ft_strlen(info->so);
    if (i < 5)
        return (-11);
    i--;
    if (info->so[i] != 'm' || info->so[i - 1] != 'p' || info->so[i - 2] != 'x' || info->so[i - 3] != '.')
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
    if (info->we[i] != 'm' || info->we[i - 1] != 'p' || info->we[i - 2] != 'x' || info->we[i - 3] != '.')
        return (-11);
    i = ft_strlen(info->ea);
    if (i < 5)
        return (-11);
    i--;
    if (info->ea[i] != 'm' || info->ea[i - 1] != 'p' || info->ea[i - 2] != 'x' || info->ea[i - 3] != '.')
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
    if (info->s[i] != 'm' || info->s[i - 1] != 'p' || info->s[i - 2] != 'x' || info->s[i - 3] != '.')
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
    if (!(info->no) || !(info->so) || !(info->we) || !(info->ea) || !(info->ea) 
    || !(info->floor.type) || !(info->ceil.type))
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

void set_N(t_map *map_info)
{
    map_info->dirX = 0;
    map_info->dirY = -1;
    map_info->planeX = 0.57;
    map_info->planeY = 0;
}

void set_S(t_map *map_info)
{
    map_info->dirX = 0;
    map_info->dirY = 1;
    map_info->planeX = -0.57;
    map_info->planeY = 0;
}

void set_W(t_map *map_info)
{
    map_info->dirX = -1;
    map_info->dirY = 0;
    map_info->planeX = 0;
    map_info->planeY = -0.57;
}

void set_E(t_map *map_info)
{
    map_info->dirX = 1;
    map_info->dirY = 0;
    map_info->planeX = 0;
    map_info->planeY = 0.57;
}

void set_dir(t_map *map_info, char letter)
{
    if (letter == 'N')
        set_N(map_info);
    else if (letter == 'S')
        set_S(map_info);
    else if (letter == 'W')
        set_W(map_info);
    else if (letter == 'E')
        set_E(map_info);
}

int check_player(char **map_arr, t_map *map_info)
{
    int i;
    int j;
    int count;

    i = 0;
    count = 0;
    while (map_arr[i])
    {
        j = 0;
        while (map_arr[i][j])
        {
            if (map_arr[i][j] == 'N' || map_arr[i][j] == 'E' || map_arr[i][j] == 'W' || map_arr[i][j] == 'S')
            {
                map_info->x_player = j;
                map_info->y_player = i;
                set_dir(map_info, map_arr[i][j]);
                count++;
            }
            j++;
        }
        i++;
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

int load_textures(t_map *map_info)
{
    map_info->no_text.img = mlx_xpm_file_to_image(map_info->mlx, map_info->no, &map_info->no_text.width, &map_info->no_text.height);
    if (map_info->no_text.img == NULL)
        return (-1);
    map_info->no_text.addr = mlx_get_data_addr(map_info->no_text.img, &map_info->no_text.bits_per_pixel, &map_info->no_text.line_length, &map_info->no_text.endian);

    map_info->so_text.img = mlx_xpm_file_to_image(map_info->mlx, map_info->so, &map_info->so_text.width, &map_info->so_text.height);
    if (map_info->so_text.img == NULL)
        return (-1);
    map_info->so_text.addr = mlx_get_data_addr(map_info->so_text.img, &map_info->so_text.bits_per_pixel, &map_info->so_text.line_length, &map_info->so_text.endian);

    map_info->ea_text.img = mlx_xpm_file_to_image(map_info->mlx, map_info->ea, &map_info->ea_text.width, &map_info->ea_text.height);
    if (map_info->ea_text.img == NULL)
        return (-1);
    map_info->ea_text.addr = mlx_get_data_addr(map_info->ea_text.img, &map_info->ea_text.bits_per_pixel, &map_info->ea_text.line_length, &map_info->ea_text.endian);

    map_info->we_text.img = mlx_xpm_file_to_image(map_info->mlx, map_info->we, &map_info->we_text.width, &map_info->we_text.height);
    if (map_info->we_text.img == NULL)
        return (-1);
    map_info->we_text.addr = mlx_get_data_addr(map_info->we_text.img, &map_info->we_text.bits_per_pixel, &map_info->we_text.line_length, &map_info->we_text.endian);
    return (0);
}

int load_sprites(t_map *map_info)
{
    map_info->spr.img = mlx_xpm_file_to_image(map_info->mlx, map_info->s, &map_info->spr.width, &map_info->spr.height);
    if (map_info->spr.img == NULL)
        return (-1);
    map_info->spr.addr = mlx_get_data_addr(map_info->spr.img, &map_info->spr.bits_per_pixel, &map_info->spr.line_length, &map_info->spr.endian);
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

    *sprites = (t_spr *)malloc(sizeof(t_spr) * quantity);
    i = 0;
    j = 0;
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
    return (quantity);
}