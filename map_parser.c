#include <stdio.h>
#include "libft/libft.h"
#include <mlx.h>

// const int BYTES_PER_PIXEL = 3; /// red, green, & blue
// const int FILE_HEADER_SIZE = 14;
// const int INFO_HEADER_SIZE = 40;

// void generateBitmapImage(unsigned char *image, int height, int width, char *imageFileName);
// unsigned char *createBitmapFileHeader(int height, int stride);
// unsigned char *createBitmapInfoHeader(int height, int width);

// void generateBitmapImage(unsigned char *image, int height, int width, char *imageFileName)
// {
//     int widthInBytes = width * BYTES_PER_PIXEL;

//     unsigned char padding[3] = {0, 0, 0};
//     int paddingSize = (4 - (widthInBytes) % 4) % 4;

//     int stride = (widthInBytes) + paddingSize;

//     FILE *imageFile = fopen(imageFileName, "wb");

//     unsigned char *fileHeader = createBitmapFileHeader(height, stride);
//     fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

//     unsigned char *infoHeader = createBitmapInfoHeader(height, width);
//     fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

//     int i;
//     for (i = 0; i < height; i++)
//     {
//         fwrite(image + (i * widthInBytes), BYTES_PER_PIXEL, width, imageFile);
//         fwrite(padding, 1, paddingSize, imageFile);
//     }

//     fclose(imageFile);
// }

// unsigned char *createBitmapFileHeader(int height, int stride)
// {
//     int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

//     static unsigned char fileHeader[] = {
//         0, 0,       /// signature
//         0, 0, 0, 0, /// image file size in bytes
//         0, 0, 0, 0, /// reserved
//         0, 0, 0, 0, /// start of pixel array
//     };

//     fileHeader[0] = (unsigned char)('B');
//     fileHeader[1] = (unsigned char)('M');
//     fileHeader[2] = (unsigned char)(fileSize);
//     fileHeader[3] = (unsigned char)(fileSize >> 8);
//     fileHeader[4] = (unsigned char)(fileSize >> 16);
//     fileHeader[5] = (unsigned char)(fileSize >> 24);
//     fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

//     return fileHeader;
// }

// unsigned char *createBitmapInfoHeader(int height, int width)
// {
//     static unsigned char infoHeader[] = {
//         0, 0, 0, 0, /// header size
//         0, 0, 0, 0, /// image width
//         0, 0, 0, 0, /// image height
//         0, 0,       /// number of color planes
//         0, 0,       /// bits per pixel
//         0, 0, 0, 0, /// compression
//         0, 0, 0, 0, /// image size
//         0, 0, 0, 0, /// horizontal resolution
//         0, 0, 0, 0, /// vertical resolution
//         0, 0, 0, 0, /// colors in color table
//         0, 0, 0, 0, /// important color count
//     };

//     infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
//     infoHeader[4] = (unsigned char)(width);
//     infoHeader[5] = (unsigned char)(width >> 8);
//     infoHeader[6] = (unsigned char)(width >> 16);
//     infoHeader[7] = (unsigned char)(width >> 24);
//     infoHeader[8] = (unsigned char)(height);
//     infoHeader[9] = (unsigned char)(height >> 8);
//     infoHeader[10] = (unsigned char)(height >> 16);
//     infoHeader[11] = (unsigned char)(height >> 24);
//     infoHeader[12] = (unsigned char)(1);
//     infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL * 8);

//     return infoHeader;
// }

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

int load_sprites(t_map *map_info)
{
    map_info->spr.img = mlx_xpm_file_to_image(map_info->mlx, map_info->s, &map_info->spr.width, &map_info->spr.height);
    if (map_info->spr.img == NULL)
        return (-1);
    map_info->spr.addr = mlx_get_data_addr(map_info->spr.img, &map_info->spr.bits_per_pixel, &map_info->spr.line_length, &map_info->spr.endian);
    return (0);
}

void sort_sprites(int *spriteOrder, double *spriteDistance, int len)
{
    int i;
    int j;
    double dist_perm;

    i = 0;
    j = len - 1;
    while (i < len - 1)
    {
        j = len - 1;
        while (j > i)
        {
            if (spriteDistance[j - 1] < spriteDistance[j])
            {
                dist_perm = spriteDistance[j - 1];
                spriteOrder[j - 1] = j;
                spriteDistance[j - 1] = spriteDistance[j];
                spriteDistance[j] = dist_perm;
                spriteOrder[j] = j - 1;
            }
            j--;
        }
        i++;
    }
}

int close_all(void *arg)
{
    exit(0);
    return (0);
}

void draw_wall(t_map *map_info)
{
    unsigned int color;
    int p = 0;
    double zBuffer[map_info->win_w];
    double spriteDistance[map_info->sprites_len];
    int spriteOrder[map_info->sprites_len];

    draw_f_c(map_info);

    while (p < map_info->win_w)
    {
        double cameraX = 2 * p / (double)map_info->win_w - 1; //x-coordinate in camera space
        double rayDirX = map_info->dirX + map_info->planeX * cameraX;
        double rayDirY = map_info->dirY + map_info->planeY * cameraX;
        int mapX = (int)(map_info->posX);
        int mapY = (int)(map_info->posY);

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side;    //was a NS or a EW wall hit?
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
        while (hit == 0)
        {
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
            if (map_info->map[mapY][mapX] != '0' && map_info->map[mapY][mapX] != 'N' && map_info->map[mapY][mapX] != 'W' && map_info->map[mapY][mapX] != 'E' && map_info->map[mapY][mapX] != 'S')
                hit = 1;
        }
        if (side == 0)
            perpWallDist = (mapX - map_info->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - map_info->posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(map_info->win_h / perpWallDist);

        int drawStart = -lineHeight / 2 + map_info->win_h / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + map_info->win_h / 2;
        if (drawEnd >= map_info->win_h)
            drawEnd = map_info->win_h - 1;

        double wallX; //where exactly the wall was hit
        if (side == 0)
            wallX = map_info->posY + perpWallDist * rayDirY;
        else
            wallX = map_info->posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        int texX = (int)(wallX * (double)(map_info->no_text.width));
        if (side == 0 && rayDirX <= 0)
            texX = map_info->ea_text.width - 1 - texX;
        if (side == 1 && rayDirY >= 0)
            texX = map_info->so_text.width - 1 - texX;

        double step = 1.0 * map_info->no_text.height / lineHeight;
        double texPos = (drawStart - map_info->win_h / 2 + lineHeight / 2) * step;

        for (int y = drawStart; y < drawEnd; y++)
        {
            int texY = (int)texPos & (map_info->we_text.height - 1);
            texPos += step;
            if (side == 0 && rayDirX >= 0)
                color = ((unsigned int *)(map_info->we_text.addr))[map_info->we_text.width * texY + texX];
            else if (side == 0 && rayDirX <= 0)
                color = ((unsigned int *)(map_info->ea_text.addr))[map_info->ea_text.width * texY + texX];
            else if (side == 1 && rayDirY <= 0)
                color = ((unsigned int *)(map_info->no_text.addr))[map_info->no_text.width * texY + texX];
            else if (side == 1 && rayDirY >= 0)
                color = ((unsigned int *)(map_info->so_text.addr))[map_info->so_text.width * texY + texX];
            my_mlx_pixel_put(map_info, p, y, color);
        }
        zBuffer[p] = perpWallDist;
        p++;
    }

    for (int r = 0; r < map_info->sprites_len; r++) //считаем расстояние до спрайтов
    {
        spriteOrder[r] = r;
        spriteDistance[r] = ((map_info->posX - map_info->sprites[r].x) * (map_info->posX - map_info->sprites[r].x) + (map_info->posY - map_info->sprites[r].y) * (map_info->posY - map_info->sprites[r].y)); //sqrt not taken, unneeded
    }
    sort_sprites(spriteOrder, spriteDistance, map_info->sprites_len); // вроде как сортируется в порядке возрастания расстояния
    for (int i = 0; i < map_info->sprites_len; i++)
    {
        double spriteX = map_info->sprites[spriteOrder[i]].x - map_info->posX;
        double spriteY = map_info->sprites[spriteOrder[i]].y - map_info->posY;
        double invDet = 1.0 / (map_info->planeX * map_info->dirY - map_info->dirX * map_info->planeY); //required for correct matrix multiplication

        double transformX = invDet * (map_info->dirY * spriteX - map_info->dirX * spriteY);
        double transformY = invDet * ((map_info->planeY) * -1 * spriteX + map_info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
        int spriteScreenX = (int)((map_info->win_w / 2) * (1 + transformX / transformY));
        int spriteHeight = abs((int)(map_info->win_h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
        int drawStartY = -spriteHeight / 2 + map_info->win_h / 2;
        if (drawStartY < 0)
            drawStartY = 0;
        int drawEndY = spriteHeight / 2 + map_info->win_h / 2;
        if (drawEndY >= map_info->win_h)
            drawEndY = map_info->win_h - 1;
        int spriteWidth = abs((int)(map_info->win_h / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0)
            drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= map_info->win_w)
            drawEndX = map_info->win_w - 1;
        for (int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;

            if (transformY > 0 && stripe > 0 && stripe < map_info->win_w && transformY < zBuffer[stripe])
            {
                for (int y = drawStartY; y < drawEndY; y++)
                {
                    int d = (y)*256 - map_info->win_h * 128 + spriteHeight * 128;
                    int texY = ((d * map_info->no_text.height) / spriteHeight) / 256;
                    color = ((unsigned int *)(map_info->spr.addr))[map_info->no_text.width * texY + texX];
                    if ((color & 0xFFFFFF) != 0)
                        my_mlx_pixel_put(map_info, stripe, y, color);
                }
            }
        }
    }

    if (map_info->screenshot == 1)
    {
        int fd;
        unsigned char bitmap[54];
        int i = 0;
        int filesize;
        unsigned int *tmp;

        filesize = map_info->win_w * map_info->win_h * 4 + 54;
        fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        while (i < 54)
        {
            bitmap[i] = (unsigned char)0;
            i++;
        }
        bitmap[0] = 'B';
        bitmap[1] = 'M';
        bitmap[2] = filesize;
        bitmap[10] = 54;
        bitmap[14] = 40;
        *((int *)(bitmap + 2)) = filesize;
        *(int *)(bitmap + 10) = 54;
        *(int *)(bitmap + 14) = 40;
        *(int *)(bitmap + 18) = map_info->win_w;
        *(int *)(bitmap + 22) = map_info->win_h;
        *(bitmap + 26) = 1;
        *(bitmap + 28) = 32;

        write(fd, bitmap, 54);
        printf("%u\n", bitmap[18]);
        int l;
        int s;
        l = (map_info->win_h - 1) * map_info->win_w;
        tmp = (unsigned int *)map_info->addr;

        while (l >= 0)
        {
            s = 0;
            while (s < map_info->win_w)
            {
                write(fd, &tmp[l], 4);
                s++;
                l++;
            }
            l -= 2 * map_info->win_w;
        }
        close(fd);
        close_all(map_info);
    }

    mlx_put_image_to_window(map_info->mlx, map_info->win, map_info->img, 0, 0);
}

int key_hook(t_map *map_info)
{
    double rotSpeed = 0.03;
    double moveSpeed = 0.08;

    if (map_info->keys.left == 1)
    {
        double oldDirX = map_info->dirX;
        map_info->dirX = map_info->dirX * cos(-rotSpeed) - map_info->dirY * sin(-rotSpeed);
        map_info->dirY = (oldDirX * sin(-rotSpeed) + map_info->dirY * cos(-rotSpeed));
        double oldPlaneX = map_info->planeX;
        map_info->planeX = (map_info->planeX * cos(-rotSpeed) - map_info->planeY * sin(-rotSpeed));
        map_info->planeY = (oldPlaneX * sin(-rotSpeed) + map_info->planeY * cos(-rotSpeed));
    }
    if (map_info->keys.right == 1)
    {
        double oldDirX = map_info->dirX;
        map_info->dirX = map_info->dirX * cos(rotSpeed) - map_info->dirY * sin(rotSpeed);
        map_info->dirY = (oldDirX * sin(rotSpeed) + map_info->dirY * cos(rotSpeed));
        double oldPlaneX = map_info->planeX;
        map_info->planeX = (map_info->planeX * cos(rotSpeed) - map_info->planeY * sin(rotSpeed));
        map_info->planeY = (oldPlaneX * sin(rotSpeed) + map_info->planeY * cos(rotSpeed));
    }
    if (map_info->keys.w == 1)
    {
        if (map_info->map[(int)(map_info->posY + (map_info->dirY) * moveSpeed)][(int)(map_info->posX)] != '1')
            map_info->posY += (map_info->dirY) * moveSpeed;
        if (map_info->map[(int)(map_info->posY)][(int)(map_info->posX + (map_info->dirX) * moveSpeed)] != '1')
            map_info->posX += (map_info->dirX) * moveSpeed;
    }
    if (map_info->keys.s == 1)
    {
        if (map_info->map[(int)(map_info->posY - (map_info->dirY) * moveSpeed)][(int)(map_info->posX)] != '1')
            map_info->posY -= (map_info->dirY) * moveSpeed;
        if (map_info->map[(int)(map_info->posY)][(int)(map_info->posX - (map_info->dirX) * moveSpeed)] != '1')
            map_info->posX -= (map_info->dirX) * moveSpeed;
    }
    if (map_info->keys.a == 1)
    {
        if (map_info->map[(int)(map_info->posY - (map_info->dirX) * moveSpeed)][(int)(map_info->posX)] != '1')
            map_info->posY -= (map_info->dirX) * moveSpeed;
        if (map_info->map[(int)(map_info->posY)][(int)(map_info->posX + (map_info->dirY) * moveSpeed)] != '1')
            map_info->posX += (map_info->dirY) * moveSpeed;
    }
    if (map_info->keys.d == 1)
    {
        if (map_info->map[(int)(map_info->posY + (map_info->dirX) * moveSpeed)][(int)(map_info->posX)] != '1')
            map_info->posY += (map_info->dirX) * moveSpeed;
        if (map_info->map[(int)(map_info->posY)][(int)(map_info->posX - (map_info->dirY) * moveSpeed)] != '1')
            map_info->posX -= (map_info->dirY) * moveSpeed;
    }
    draw_wall(map_info);
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

void free_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int handle_pressed_key(int keycode, t_map *map_info)
{
    if (keycode == KEY_W)
        map_info->keys.w = 1;
    if (keycode == KEY_S)
        map_info->keys.s = 1;
    if (keycode == KEY_A)
        map_info->keys.a = 1;
    if (keycode == KEY_D)
        map_info->keys.d = 1;
    if (keycode == KEY_LEFT)
        map_info->keys.left = 1;
    if (keycode == KEY_RIGHT)
        map_info->keys.right = 1;
    return (0);
}

int handle_unpressed_key(int keycode, t_map *map_info)
{
    if (keycode == KEY_W)
        map_info->keys.w = 0;
    if (keycode == KEY_S)
        map_info->keys.s = 0;
    if (keycode == KEY_A)
        map_info->keys.a = 0;
    if (keycode == KEY_D)
        map_info->keys.d = 0;
    if (keycode == KEY_LEFT)
        map_info->keys.left = 0;
    if (keycode == KEY_RIGHT)
        map_info->keys.right = 0;
    return (0);
}

int main(int argc, char **argv)
{
    int fd;
    int ret;
    char map_str[BUF_SIZE + 1];
    int i = 0;
    char **map;
    t_map map_info;

    map_info.win_h = 0;
    map_info.win_w = 0;
    map_info.no = NULL;
    map_info.so = NULL;
    map_info.we = NULL;
    map_info.ea = NULL;
    map_info.s = NULL;
    map_info.screenshot = 0;

    fd = open("map.cub", O_RDWR);
    if (fd == -1)
    {
        printf("%s\n", "Wrong file");
        return (-1);
    }
    while ((ret = read(fd, map_str, BUF_SIZE)))
        map_str[ret] = '\0';
    close(fd);
    map = ft_split(map_str, '\n');
    if (check_info(map, &map_info) < 0)
    {
        printf("%s\n", "Info eror");
        free_arr(map);
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
        printf("%s\n", "Player error");
        free_arr(map_info.map);
        free_arr(map);
        getc(stdin);
        return (-1);
    }

    if (check_map(&map, map_info) < 0)
    {
        printf("%s\n", "Map error");
        free_arr(map_info.map);
        free_arr(map);
        return (-1);
    }
    map_info.sprites_len = find_sprites(&map_info, &(map_info.sprites)); //потом почистить массив спрайтов

    //текстуры
    free_arr(map);
    map_info.mlx = mlx_init();
    mlx_do_key_autorepeatoff(map_info.mlx);

    if (load_textures(&map_info) < 0)
    {
        printf("%s\n", "No texture file");
        int e = 0;
        while (e < map_info.map_len)
        {
            free(map_info.map[e]);
            e++;
        }
        free(map_info.map);
        free(map);
        return (-1);
    }

    if (load_sprites(&map_info) < 0)
    {
        printf("%s\n", "No sprites file");
        int e = 0;
        while (e < map_info.map_len)
        {
            free(map_info.map[e]);
            e++;
        }
        free(map_info.map);
        free(map);
        return (-1);
    }

    if (argc == 1)
        map_info.win = mlx_new_window(map_info.mlx, map_info.win_w, map_info.win_h, "cub3D");
    else if (argc == 2 && !ft_strncmp(argv[1], "--save", 6))
        map_info.screenshot = 1;

    map_info.img = mlx_new_image(map_info.mlx, map_info.win_w, map_info.win_h);
    map_info.addr = mlx_get_data_addr(map_info.img, &map_info.bits_per_pixel, &map_info.line_length, &map_info.endian);
    map_info.posX = (double)map_info.x_player + 0.5;
    map_info.posY = (double)map_info.y_player + 0.5;
    draw_wall(&map_info);

    mlx_loop_hook(map_info.mlx, key_hook, &map_info);

    mlx_hook(map_info.win, 2, 0, handle_pressed_key, &map_info);

    mlx_hook(map_info.win, 17, 0, close_all, &map_info); // крестик

    mlx_hook(map_info.win, 3, 0, handle_unpressed_key, &map_info);

    mlx_loop(map_info.mlx);
    return (0);
}
