#include <stdio.h>
#include "libft/libft.h"
#include <mlx.h>
#define SCALE 30
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
    if (map_line[0] == 'N')
    {
        if (map_info->no)
            return (-1);
        map_info->no = ft_strdup(&(map_line[i]));
    }
    else if (map_line[0] == 'W')
    {
        if (map_info->we)
            return (-1);
        map_info->we = ft_strdup(&(map_line[i]));
    }
    else if (map_line[0] == 'E')
    {
        if (map_info->ea)
            return (-1);
        map_info->ea = ft_strdup(&(map_line[i]));
    }
    else if (map_line[0] == 'S' && map_line[1] == 'O')
    {
        if (map_info->so)
            return (-1);
        map_info->so = ft_strdup(&(map_line[i]));
    }
    else if (map_line[0] == 'S')
    {
        if (map_info->s)
            return (-1);
        map_info->s = ft_strdup(&(map_line[i]));
    }
    return (0);
}

int check_info(char **map, t_map *map_info)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 6)
    {
        j = 0;
        if (map[i] == NULL)
            return (-1);
        if (map[i][j] == 'R' && map[i][j + 1] == ' ')
        {
            if ((check_r(map[i], map_info)) < 0)
                return (-1);
        }
        else if ((map[i][j] == 'N' && map[i][j + 1] == 'O') || (map[i][j] == 'S' && map[i][j + 1] == 'O') || (map[i][j] == 'W' && map[i][j + 1] == 'E') || (map[i][j] == 'E' && map[i][j + 1] == 'A') || (map[i][j] == 'S' && map[i][j + 1] == ' '))
        {
            if ((check_sides(map[i], map_info)) < 0)
                return (-1);
        }
        else
            return (-1);
        i++;
    }
    if (!(map_info->no) || !(map_info->so) || !(map_info->we) || !(map_info->ea) || !(map_info->ea))
        return (-1);
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

void set_dir(char sym, t_player *player)
{
    if (sym == 'N')
        player->dir = 3 * M_PI_2;
    else if (sym == 'S')
        player->dir = M_PI_2;
    else if (sym == 'W')
        player->dir = M_PI;
    else if (sym == 'E')
        player->dir = 0;
}

int check_player(char **map_arr, t_player *player)
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
                player->x_player = j;
                player->y_player = i;
                set_dir(map_arr[i][j], player);
                count++;
            }
            j++;
        }
        i++;
    }
    if (count != 1)
        return (-1);
    return (0);
}

int flood_fill(char ***map_arr, int x, int y, t_map map_info)
{
    if (x < 0 || x > map_info.str_len || y < 6 || y >= map_info.map_len + 6 || !((*map_arr)[y][x] == 'N' || (*map_arr)[y][x] == 'W' || (*map_arr)[y][x] == 'E' || (*map_arr)[y][x] == 'S' || (*map_arr)[y][x] == '0' || (*map_arr)[y][x] == '2' || (*map_arr)[y][x] == '1'))
        return (-1);
    if ((*map_arr)[y][x] == '1')
        return (1);

    if ((*map_arr)[y][x] == 'N' || (*map_arr)[y][x] == 'W' || (*map_arr)[y][x] == 'E' || (*map_arr)[y][x] == 'S' || (*map_arr)[y][x] == '0' || (*map_arr)[y][x] == '2')
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

    i = 6;
    max_len = 0;
    while (map[i])
    {
        if ((int)ft_strlen(map[i]) > max_len)
            max_len = ft_strlen(map[i]);
        i++;
    }
    return (max_len);
}

void draw_square(t_win window, int x, int y, int color)
{
    int width;
    int height;
    int x_start;

    width = SCALE;
    height = SCALE;
    x_start = x;
    while (height)
    {
        width = SCALE;
        x = x_start;
        while (width)
        {
            mlx_pixel_put(window.mlx, window.win, x, y, color);
            x++;
            width--;
        }
        y++;
        height--;
    }
}

int check_map(char ***map, t_map map_info)
{
    int i;
    int j;

    i = 6;
    j = 0;
    while ((*map)[i])
    {
        j = 0;
        while ((*map)[i][j])
        {
            if ((*map)[i][j] == '0' || (*map)[i][j] == '2' || (*map)[i][j] == 'N' || (*map)[i][j] == 'E' || (*map)[i][j] == 'S' || (*map)[i][j] == 'W')
            {
                if (flood_fill(map, j, i, map_info) < 0)
                    return (-1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int main()
{
    //считываем весь файл конфигурации в одну строку, дальше читаем с помощью сплита и записываем в двумерный массив
    int fd;
    int ret;
    char map_str[BUF_SIZE + 1];
    int i = 0;
    char **map;
    t_map map_info;
    t_player player;
    t_win window;

    map_info.win_h = 0;
    map_info.win_w = 0;
    map_info.no = NULL;
    map_info.so = NULL;
    map_info.we = NULL;
    map_info.ea = NULL;
    map_info.s = NULL;

    fd = open("map.cub", O_RDWR);
    if (fd == -1)
    {
        printf("%s\n", "Error");
        return (-1);
    }
    while ((ret = read(fd, map_str, BUF_SIZE)))
        map_str[ret] = '\0';
    close(fd);
    map = ft_split(map_str, '\n');
    if (check_info(map, &map_info) < 0)
    {
        printf("%s\n", "Error");
        return (-1);
    }
    //Выделяем новый массив под карту онли
    map_info.str_len = longest_str(map);
    map_info.map_len = count_map_len(map, 6);

    map_info.map = (char **)malloc((map_info.map_len + 1) * sizeof(char *));
    while (i < map_info.map_len)
    {
        map_info.map[i] = ft_calloc(map_info.str_len + 1, 1);
        i++;
    }
    map_info.map[i] = NULL;
    i = 0;
    while (i < map_info.map_len)
    {
        ft_strcpy(map_info.map[i], map[i + 6]);
        i++;
    }

    if (check_player(map_info.map, &player) < 0)
    {
        printf("%s\n", "Error");
        return (-1);
    }

    if (check_map(&map, map_info) < 0)
    {
        printf("%s\n", "Error");
        return (-1);
    }

    free(map);
    //Рисуем карту
    window.mlx = mlx_init();
    window.win = mlx_new_window(window.mlx, map_info.win_w, map_info.win_h, "Test");

    int k = 0;
    int l = 0;
    int x = 0;
    int y = 0;
    while (map_info.map[k])
    {
        l = 0;
        x = 0;
        while (map_info.map[k][l])
        {
            if (map_info.map[k][l] == '1')
                draw_square(window, x, y, 0xFFFFFF);
            else if (map_info.map[k][l] == '2')
                draw_square(window, x, y, 0xFF0000);
            // else if (map_info.map[k][l] == 'N' || map_info.map[k][l] == 'W' || map_info.map[k][l] == 'E' || map_info.map[k][l] == 'S')
            //     draw_square(window, x, y, 0x00FF00);
            x += SCALE;
            l++;
        }
        y += SCALE;
        k++;
    }
    player.x_player = player.x_player * SCALE;
    player.y_player = player.y_player * SCALE;

    mlx_pixel_put(window.mlx, window.win, player.x_player, player.y_player, 0x00FF00); // Игрок

    t_player ray;
    ray = player;
    // Луч
    // while (map_info.map[(int)(ray.y_player / SCALE)][(int)(ray.x_player / SCALE)] != '1')
    // {
    //     ray.x_player += cos(ray.dir);
    //     ray.y_player += sin(ray.dir);
    //     mlx_pixel_put(window.mlx, window.win, ray.x_player, ray.y_player, 0x990099);
    // }

    // Много лучей
    // ray.start = ray.dir - M_PI_4;
    // ray.end = ray.dir + M_PI_4;
    // while (ray.start <= ray.end)
    // {
    //     ray.x_player = player.x_player; // каждый раз возвращаемся в точку начала
    //     ray.y_player = player.y_player;
    //     while (map_info.map[(int)(ray.y_player / SCALE)][(int)(ray.x_player / SCALE)] != '1')
    //     {
    //         ray.x_player += cos(ray.start);
    //         ray.y_player += sin(ray.end);
    //         mlx_pixel_put(window.mlx, window.win, ray.x_player, ray.y_player, 0x990099);
    //     }
    //     ray.start += M_PI_2 / 1000;
    // }

    

    // Потуги с лучами
    double posX = player.x_player; //координата игрока по x
    double poxY = player.y_player; //координата игрока по y
    double dirX = -1; //initial diection vector
    double dirY = 0;
    double planeX = 0; //the 2d raycaster version of camera plane, FOV is 2 * atan(0.66/1.0)=66°
    double planeY = 0.66;
    double time = 0;
    double oldTime = 0;
    double cameraX;
    double rayDirX;
    double rayDirY;

    int p = 0;
    double w = 12; //предположительно количество лучей
    while (p < w)
    {
      //calculate ray position and direction
      cameraX = 2 * p / w - 1; //x-coordinate in camera space
      rayDirX = dirX + planeX * cameraX;
      rayDirY = dirY + planeY * cameraX;
      printf("%f and %f and %f\n", cameraX, rayDirX, rayDirY);
      p++;
    }
    mlx_loop(window.mlx);
    // double angle = 0; //угол взгляда игрока
    return 0;
}
