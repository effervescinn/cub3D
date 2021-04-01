#include <stdio.h>
#include "libft/libft.h"
#include <mlx.h>
#include "parser.h"

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

void my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int make_color(int r, int g, int b)
{
    return(r << 16 | g << 8 | b);
}


void draw_f_c(t_map *m)
{
    int i;
    int j;
    int c_color = make_color(m->ceil.r, m->ceil.g, m->ceil.b);
    int f_color = make_color(m->floor.r, m->floor.g, m->floor.b);

    i = 0;
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

int esc_close(int keycode)
{
    if (keycode == 53)
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

void set_struct(t_map *map_info)
{
    map_info->win_h = 0;
    map_info->win_w = 0;
    map_info->no = NULL;
    map_info->so = NULL;
    map_info->we = NULL;
    map_info->ea = NULL;
    map_info->s = NULL;
    map_info->floor.type = NULL;
    map_info->ceil.type = NULL;
    map_info->screenshot = 0;
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
}

int main(int argc, char **argv)
{
    int fd;
    int ret;
    char map_str[BUF_SIZE + 1];
    int i = 0;
    char **map;
    t_map map_info;
    int err;

    
    set_struct(&map_info);
    fd = open("map.cub", O_RDWR);
    if (fd == -1)
    {
        printf(FD_ERROR);
        return (-1);
    }
    while ((ret = read(fd, map_str, BUF_SIZE)))
        map_str[ret] = '\0';
    close(fd);
    map = ft_split(map_str, '\n');


    if ((err = check_info(map, &map_info)) < 0)
    {
        print_err(err);
        free_arr(map);
        return (-1);
    }

    //Выделяем новый массив под карту онли
    map_info.str_len = longest_str(map);
    map_info.map_len = count_map_len(map, 8);

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
        ft_strcpy(map_info.map[i], map[i + 8]);
        i++;
    }

    if ((err = check_player(map_info.map, &map_info)) < 0)
    {
        print_err(err);
        free_arr(map_info.map);
        free_arr(map);
        return (-1);
    }

    if ((err = check_map(&map, map_info)) < 0)
    {
        print_err(err);
        free_arr(map_info.map);
        free_arr(map);
        return (-1);
    }
    map_info.sprites_len = find_sprites(&map_info, &(map_info.sprites)); //потом почистить массив спрайтов

    free_arr(map);
    map_info.mlx = mlx_init();
    mlx_do_key_autorepeatoff(map_info.mlx);

    if (load_textures(&map_info) < 0)
    {
        printf("%s\n", "Wrong texture file");
        // int e = 0;
        // while (e < map_info.map_len)
        // {
        //     free(map_info.map[e]);
        //     e++;
        // }
        // free(map_info.map);
        // free(map);
        return (-1);
    }

    if (load_sprites(&map_info) < 0)
    {
        printf("%s\n", "Wrong sprites file");
        // int e = 0;
        // while (e < map_info.map_len)
        // {
        //     free(map_info.map[e]);
        //     e++;
        // }
        // free(map_info.map);
        // free(map);
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

    // mlx_hook(map_info.win, 2, 1L<<0, esc_close, &map_info); // esc не работают другие клавиши

    mlx_hook(map_info.win, 3, 0, handle_unpressed_key, &map_info);

    mlx_loop(map_info.mlx);
    return (0);
}
