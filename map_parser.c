#include <stdio.h>
#include "libft/libft.h"
#include <mlx.h>

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

void set_dir(t_map *map_info, char letter)
{
    if (letter == 'N')
    {
        map_info->dirX = 0;
        map_info->dirY = -1;
        map_info->planeX = 0.57;
        map_info->planeY = 0;
    }
    else if (letter == 'S')
    {
        map_info->dirX = 0;
        map_info->dirY = 1;
        map_info->planeX = -0.57;
        map_info->planeY = 0;
    }
    else if (letter == 'W')
    {
        map_info->dirX = -1;
        map_info->dirY = 0;
        map_info->planeX = 0;
        map_info->planeY = -0.57;
    }
    else if (letter == 'E')
    {
        map_info->dirX = 1;
        map_info->dirY = 0;
        map_info->planeX = 0;
        map_info->planeY = 0.57;
    }
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

void my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
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

void drawline(t_map *map_info, int p, int drawStart, int drawEnd, int color)
{
    while (drawStart <= drawEnd)
    {
        my_mlx_pixel_put(map_info, p, drawStart, color);
        drawStart++;
    }
}

void draw_f_c(t_map *map_info)
{
    int i;
    int j;
    int c_color = 0xC0E9F5;
    int f_color = 0xF5DEC0;

    i = 0; //height
    j = 0; //width
    while (i < (map_info->win_h / 2))
    {
        j = 0;
        while (j < map_info->win_w)
        {
            my_mlx_pixel_put(map_info, j, i, c_color);
            j++;
        }
        i++;
    }
    while (i < (map_info->win_h))
    {
        j = 0;
        while (j < map_info->win_w)
        {
            my_mlx_pixel_put(map_info, j, i, f_color);
            j++;
        }
        i++;
    }
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

void draw_wall(t_map *map_info)
{

    unsigned int color;
    int p = 0;
    // zBuffer[map_info->win_w];

    draw_f_c(map_info);

    while (p < map_info->win_w)
    {
        //calculate ray position and direction
        double cameraX = 2 * p / (double)map_info->win_w - 1; //x-coordinate in camera space
        double rayDirX = map_info->dirX + map_info->planeX * cameraX;
        double rayDirY = map_info->dirY + map_info->planeY * cameraX;
        //which box of the map we're in
        int mapX = (int)(map_info->posX);
        int mapY = (int)(map_info->posY);

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side;    //was a NS or a EW wall hit?
        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (map_info->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - map_info->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (map_info->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - map_info->posY) * deltaDistY;
        }
        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (map_info->map[mapY][mapX] != '0' && map_info->map[mapY][mapX] != 'N' &&  map_info->map[mapY][mapX] != 'W' &&  map_info->map[mapY][mapX] != 'E' && map_info->map[mapY][mapX] != 'S')
                hit = 1;
        }
        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0)
            perpWallDist = (mapX - map_info->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - map_info->posY + (1 - stepY) / 2) / rayDirY;

        //Calculate height of line to draw on screen
        int lineHeight = (int)(map_info->win_h / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + map_info->win_h / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + map_info->win_h / 2;
        if (drawEnd >= map_info->win_h)
            drawEnd = map_info->win_h - 1;

        //texturing calculations
        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if (side == 0)
            wallX = map_info->posY + perpWallDist * rayDirY;
        else
            wallX = map_info->posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        //x coordinate on the texture
        int texX = (int)(wallX * (double)(map_info->no_text.width));
        // if (side == 0 && rayDirX > 0)
        //     texX = texX;
        if (side == 0 && rayDirX <= 0)
            texX = map_info->ea_text.width - 1 - texX;
        if (side == 1 && rayDirY >= 0)
            texX = map_info->so_text.width - 1 - texX;
            

        // How much to increase the texture coordinate per screen pixel
        double step = 1.0 * map_info->no_text.height / lineHeight;
        // Starting texture coordinate
        double texPos = (drawStart - map_info->win_h / 2 + lineHeight / 2) * step;

        char *dst;
        for (int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (map_info->we_text.height - 1);
            texPos += step;
            if (side == 0 && rayDirX >= 0)
                dst = map_info->we_text.addr + (texY * map_info->we_text.line_length + texX * (map_info->we_text.bits_per_pixel / 8));

            else if (side == 0 && rayDirX <= 0)
                dst = map_info->ea_text.addr + (texY * map_info->ea_text.line_length + texX * (map_info->ea_text.bits_per_pixel / 8));

            else if (side  == 1 && rayDirY <= 0)
                dst = map_info->no_text.addr + (texY * map_info->no_text.line_length + texX * (map_info->no_text.bits_per_pixel / 8));

            else if (side  == 1 && rayDirY >= 0)
                dst = map_info->so_text.addr + (texY * map_info->so_text.line_length + texX * (map_info->so_text.bits_per_pixel / 8));

            color = *(unsigned int *)dst;
            my_mlx_pixel_put(map_info, p, y, color);
        }
        p++;
    }
    mlx_put_image_to_window(map_info->mlx, map_info->win, map_info->img, 0, 0);
}

int key_hook(int keycode, t_map *map_info)
{
    double rotSpeed = 0.2;
    double moveSpeed = 0.6;

    if (keycode == 123)
    {
        double oldDirX = map_info->dirX;
        map_info->dirX = map_info->dirX * cos(-rotSpeed) - map_info->dirY * sin(-rotSpeed);
        map_info->dirY = (oldDirX * sin(-rotSpeed) + map_info->dirY * cos(-rotSpeed));
        double oldPlaneX = map_info->planeX;
        map_info->planeX = (map_info->planeX * cos(-rotSpeed) - map_info->planeY * sin(-rotSpeed));
        map_info->planeY = (oldPlaneX * sin(-rotSpeed) + map_info->planeY * cos(-rotSpeed));
    }
    else if (keycode == 124)
    {
        double oldDirX = map_info->dirX;
        map_info->dirX = map_info->dirX * cos(rotSpeed) - map_info->dirY * sin(rotSpeed);
        map_info->dirY = (oldDirX * sin(rotSpeed) + map_info->dirY * cos(rotSpeed));
        double oldPlaneX = map_info->planeX;
        map_info->planeX = (map_info->planeX * cos(rotSpeed) - map_info->planeY * sin(rotSpeed));
        map_info->planeY = (oldPlaneX * sin(rotSpeed) + map_info->planeY * cos(rotSpeed));
    }
    else if (keycode == 126)
    {
        if (map_info->map[(int)(map_info->posY + (map_info->dirY) * moveSpeed)][(int)(map_info->posX)] != '1')
            map_info->posY += (map_info->dirY) * moveSpeed;
        if (map_info->map[(int)(map_info->posY)][(int)(map_info->posX + (map_info->dirX) * moveSpeed)] != '1')
            map_info->posX += (map_info->dirX) * moveSpeed;
    }

    else if (keycode == 125)
    {
        if (map_info->map[(int)(map_info->posY - (map_info->dirY) * moveSpeed)][(int)(map_info->posX)] != '1')
            map_info->posY -= (map_info->dirY) * moveSpeed;
        if (map_info->map[(int)(map_info->posY)][(int)(map_info->posX - (map_info->dirX) * moveSpeed)] != '1')
            map_info->posX -= (map_info->dirX) * moveSpeed;
    }
    draw_wall(map_info);
    return (0);
}

void find_sprites(t_map *map_info, t_spr **sprites)
{
    int i;
    int j;
    int k;
    int quantity;

    i = 0;
    j = 0;
    k = 0;
    quantity = 0;
    while (i < map_info->map_len) //считаем количество спрайтов
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

    *sprites = (t_spr*)malloc(sizeof(t_spr) * quantity);
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
    t_spr *sprites;

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

    if (check_player(map_info.map, &map_info) < 0)
    {
        printf("%s\n", "Error");
        return (-1);
    }

    if (check_map(&map, map_info) < 0)
    {
        printf("%s\n", "Error");
        return (-1);
    }
    find_sprites(&map_info, &sprites); //потом почистить массив спрайтов

    //текстуры

    free(map);
    printf("%f\n%f\n", sprites[1].x, sprites[1].y);
    // Рисуем карту
    map_info.mlx = mlx_init();
    map_info.win = mlx_new_window(map_info.mlx, map_info.win_w, map_info.win_h, "Test");
    map_info.img = mlx_new_image(map_info.mlx, map_info.win_w, map_info.win_h);
    map_info.addr = mlx_get_data_addr(map_info.img, &map_info.bits_per_pixel, &map_info.line_length, &map_info.endian);

    map_info.posX = (double)map_info.x_player + 0.5; //координата игрока по x //26
    map_info.posY = (double)map_info.y_player + 0.5;

    if (load_textures(&map_info) < 0)
    {
        printf("%s\n", "No texture file");
        return (-1);
    }
    draw_wall(&map_info);
    mlx_hook(map_info.win, 2, 1L << 0, key_hook, &map_info);
    mlx_loop(map_info.mlx);
    return (0);
}
