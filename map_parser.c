#include <stdio.h>
#include "libft.h"

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

int flood_fill(char ***map_arr, int x, int y)
{
    // if (!(map_arr[y][x] == 'N' || map_arr[y][x] == 'W' || map_arr[y][x] == 'E' || map_arr[y][x] == 'S' || map_arr[y][x] == '0' || map_arr[y][x] == '2'))
    //     return (-1);
    if ((*map_arr)[y][x] == ' ' || (*map_arr)[y][x] == '\0')
        return (-1);
    if ((*map_arr)[y][x] == 'c' || (*map_arr)[y][x] == '1')
        return(1);
    // printf("x= %d, y= %d\n, %c", x, y, (*map_arr)[y][x]);

    if ((*map_arr)[y][x] == 'N' || (*map_arr)[y][x] == 'W' || (*map_arr)[y][x] == 'E' || (*map_arr)[y][x] == 'S' || (*map_arr)[y][x] == '0' || (*map_arr)[y][x] == '2')
        (*map_arr)[y][x] = 'c';
    if (flood_fill(map_arr, x, y + 1) < 0)
        return (-1);
    if (flood_fill(map_arr, x + 1, y) < 0)
        return (-1);
    if (flood_fill(map_arr, x - 1, y) < 0)
        return (-1);
    if (flood_fill(map_arr, x, y - 1) < 0)
        return (-1);
    // return (flood_fill(map_arr, x - 1, y) || flood_fill(map_arr, x + 1, y) || flood_fill(map_arr, x, y - 1) || flood_fill(map_arr, x, y + 1));
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
        if (ft_strlen(map[i]) > max_len)
            max_len = ft_strlen(map[i]);
        i++;
    }
    return (max_len);
}

int main()
{
    //считываем весь файл конфигурации в одну строку, дальше читаем с помощью сплита и записываем в двумерный массив
    int i = 0;
    int j = 0;
    char **map;
    char **map_arr;
    int map_len;
    t_map map_info;
    t_player player;
    int map_str_len;

    map_info.win_h = 0;
    map_info.win_w = 0;
    map_info.no = NULL;
    map_info.so = NULL;
    map_info.we = NULL;
    map_info.ea = NULL;
    map_info.s = NULL;

    char *map_str = "R    1600     800\nNO     cub3d_tester/textures/wall_1.xpm\n\n\nWE cub3d_tester/textures/wall_3.xpm\nEA cub3d_tester/textures/wall_4.xpm\nS cub3d_tester/textures/sprite_1.xpm\nSO cub3d_tester/textures/sprite_1.xpm\n 1111111111111111111111\n 100000000011000000000111\n 1011000001110000002000001\n 100100000000000N000000001\n 1111111111111111111111111";
    map = ft_split(map_str, '\n');
    if (check_info(map, &map_info) < 0)
    {
        printf("%s", "Invalid .cub file");
        return (-1);
    }
    //Выделяем новый массив под карту онли
    map_str_len = longest_str(map);
    map_len = count_map_len(map, 6) + 3;

    map_arr = (char**)malloc((map_len) * sizeof(char*));
    while (i < map_len)
    {
        map_arr[i] = ft_calloc(map_str_len + 2, 1);
        map_arr[i][0] = ' ';
        i++;
    }
    free(map_arr[--i]);
    map_arr[i] = NULL;
    i = 1;
    map_len -= 3;

    while (map_len--)
    {
        j = 0;
        while (map[i + 5][j])
        {
            map_arr[i][j + 1] = map[i + 5][j];
            j++;
        }
        i++;
    }
    free(map);
    int k = 0;
    while(map_arr[k])
    {
        printf("%s\n", map_arr[k]);
        k++;
    }
    
    if (check_player(map_arr, &player) < 0)
    {
        printf("%s", "Invalid .cub file");
        return (-1);
    }
    if (flood_fill(&map_arr, player.x_player, player.y_player) < 0)
    {
        printf("%s", "Invalid .cub file");
        return (-1);
    }
    // printf("%d\n", player.x_player);
    // printf("%d\n", player.y_player);

    // printf("%d\n", map_info.win_w);
    // printf("%d\n", map_info.win_h);
    // printf("%s\n", map_info.no);
    // printf("%s\n", map_info.so);
    // printf("%s\n", map_info.we);
    // printf("%s\n", map_info.ea);
    // printf("%s\n", map_info.s);

    
    return 0;
}
