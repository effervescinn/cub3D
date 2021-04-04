#include "raycast.h"

void set_walls_s(t_map *map_info, int p)
{
    map_info->walls.cameraX = 2 * p / (double)map_info->win_w - 1;
    map_info->walls.rayDirX = map_info->dirX + map_info->planeX * map_info->walls.cameraX;
    map_info->walls.rayDirY = map_info->dirY + map_info->planeY * map_info->walls.cameraX;
    map_info->walls.mapX = (int)(map_info->posX);
    map_info->walls.mapY = (int)(map_info->posY);
    map_info->walls.deltaDistX = fabs(1 / map_info->walls.rayDirX);
    map_info->walls.deltaDistY = fabs(1 / map_info->walls.rayDirY);
    map_info->walls.hit = 0;
}

void move_ray(t_map *map_info)
{
    if (map_info->walls.rayDirX < 0)
    {
        map_info->walls.stepX = -1;
        map_info->walls.sideDistX = (map_info->posX - map_info->walls.mapX) * map_info->walls.deltaDistX;
    }
    else
    {
        map_info->walls.stepX = 1;
        map_info->walls.sideDistX = (map_info->walls.mapX + 1.0 - map_info->posX) * map_info->walls.deltaDistX;
    }
    if (map_info->walls.rayDirY < 0)
    {
        map_info->walls.stepY = -1;
        map_info->walls.sideDistY = (map_info->posY - map_info->walls.mapY) * map_info->walls.deltaDistY;
    }
    else
    {
        map_info->walls.stepY = 1;
        map_info->walls.sideDistY = (map_info->walls.mapY + 1.0 - map_info->posY) * map_info->walls.deltaDistY;
    }
}

void check_hit(t_map *map_info)
{
    while (map_info->walls.hit == 0)
    {
        if (map_info->walls.sideDistX < map_info->walls.sideDistY)
        {
            map_info->walls.sideDistX += map_info->walls.deltaDistX;
            map_info->walls.mapX += map_info->walls.stepX;
            map_info->walls.side = 0;
        }
        else
        {
            map_info->walls.sideDistY += map_info->walls.deltaDistY;
            map_info->walls.mapY += map_info->walls.stepY;
            map_info->walls.side = 1;
        }
        if (map_info->map[map_info->walls.mapY][map_info->walls.mapX] != '0' && map_info->map[map_info->walls.mapY][map_info->walls.mapX] != 'N' && map_info->map[map_info->walls.mapY][map_info->walls.mapX] != 'W' && map_info->map[map_info->walls.mapY][map_info->walls.mapX] != 'E' && map_info->map[map_info->walls.mapY][map_info->walls.mapX] != 'S' && map_info->map[map_info->walls.mapY][map_info->walls.mapX] != '2')
            map_info->walls.hit = 1;
    }
}

void draw_line(t_map *map_info, int p)
{
    unsigned int color;
    int y;

    y = 0;
    while (y < map_info->walls.drawEnd)
    {
        map_info->walls.texY = (int)(map_info->walls.texPos) & (map_info->we_text.height - 1);
        map_info->walls.texPos += map_info->walls.step;
        if (map_info->walls.side == 0 && map_info->walls.rayDirX >= 0)
            color = ((unsigned int *)(map_info->we_text.addr))[map_info->we_text.width * map_info->walls.texY + map_info->walls.texX];
        else if (map_info->walls.side == 0 && map_info->walls.rayDirX <= 0)
            color = ((unsigned int *)(map_info->ea_text.addr))[map_info->ea_text.width * map_info->walls.texY + map_info->walls.texX];
        else if (map_info->walls.side == 1 && map_info->walls.rayDirY <= 0)
            color = ((unsigned int *)(map_info->no_text.addr))[map_info->no_text.width * map_info->walls.texY + map_info->walls.texX];
        else if (map_info->walls.side == 1 && map_info->walls.rayDirY >= 0)
            color = ((unsigned int *)(map_info->so_text.addr))[map_info->so_text.width * map_info->walls.texY + map_info->walls.texX];
        my_mlx_pixel_put(map_info, p, y, color);
        y++;
    }
}

void draw_walls(t_map *map_info, double **zBuffer)
{
    int p;

    p = 0;
    while (p < map_info->win_w)
    {
        set_walls_s(map_info, p);
        move_ray(map_info);
        check_hit(map_info);
        if (map_info->walls.side == 0)
            map_info->walls.perpWallDist = (map_info->walls.mapX - map_info->posX + (1 - map_info->walls.stepX) / 2) / map_info->walls.rayDirX;
        else
            map_info->walls.perpWallDist = (map_info->walls.mapY - map_info->posY + (1 - map_info->walls.stepY) / 2) / map_info->walls.rayDirY;
        map_info->walls.lineHeight = (int)(map_info->win_h / map_info->walls.perpWallDist);
        map_info->walls.drawStart = (-1) * map_info->walls.lineHeight / 2 + map_info->win_h / 2;
        if (map_info->walls.drawStart < 0)
            map_info->walls.drawStart = 0;
        map_info->walls.drawEnd = map_info->walls.lineHeight / 2 + map_info->win_h / 2;
        if (map_info->walls.drawEnd >= map_info->win_h)
            map_info->walls.drawEnd = map_info->win_h - 1;
        if (map_info->walls.side == 0)
            map_info->walls.wallX = map_info->posY + map_info->walls.perpWallDist * map_info->walls.rayDirY;
        else
            map_info->walls.wallX = map_info->posX + map_info->walls.perpWallDist * map_info->walls.rayDirX;
        map_info->walls.wallX -= floor((map_info->walls.wallX));
        map_info->walls.texX = (int)(map_info->walls.wallX * (double)(map_info->no_text.width));
        if (map_info->walls.side == 0 && map_info->walls.rayDirX <= 0)
            map_info->walls.texX = map_info->ea_text.width - 1 - map_info->walls.texX;
        if (map_info->walls.side == 1 && map_info->walls.rayDirY >= 0)
            map_info->walls.texX = map_info->so_text.width - 1 - map_info->walls.texX;
        map_info->walls.step = 1.0 * map_info->no_text.height / map_info->walls.lineHeight;
        map_info->walls.texPos = (map_info->walls.drawStart - map_info->win_h / 2 + map_info->walls.lineHeight / 2) * map_info->walls.step;
        draw_line(map_info, p);
        (*zBuffer)[p] = map_info->walls.perpWallDist;
        p++;
    }
}

void set_sprites(t_map *map_info, double **spriteDistance, int **spriteOrder)
{
    int i;

    i = 0;
    while (i < map_info->spr_l) //считаем расстояние до спрайтов
    {
        (*spriteOrder)[i] = i;
        (*spriteDistance)[i] = ((map_info->posX - map_info->sprites[i].x) * (map_info->posX - map_info->sprites[i].x) + (map_info->posY - map_info->sprites[i].y) * (map_info->posY - map_info->sprites[i].y));
        i++;
    }
    sort_sprites(*spriteOrder, *spriteDistance, map_info->spr_l);
}

void draw_sprs(t_map *map_info, int *spriteOrder, double *zBuffer)
{
    int i;
    int stripe;
    int y;
    int d;
    unsigned int color;

    i = 0;
    while (i < map_info->spr_l)
    {
        if (!(((int)map_info->posX == (int)map_info->sprites[spriteOrder[i]].x) && ((int)map_info->posY == (int)map_info->sprites[spriteOrder[i]].y)))
        {
            map_info->d_sprs.spriteX = map_info->sprites[spriteOrder[i]].x - map_info->posX;
            map_info->d_sprs.spriteY = map_info->sprites[spriteOrder[i]].y - map_info->posY;
            map_info->d_sprs.invDet = 1.0 / (map_info->planeX * map_info->dirY - map_info->dirX * map_info->planeY); //required for correct matrix multiplication

            map_info->d_sprs.transformX = map_info->d_sprs.invDet * (map_info->dirY * map_info->d_sprs.spriteX - map_info->dirX * map_info->d_sprs.spriteY);
            map_info->d_sprs.transformY = map_info->d_sprs.invDet * ((map_info->planeY) * -1 * map_info->d_sprs.spriteX + map_info->planeX * map_info->d_sprs.spriteY); //this is actually the depth inside the screen, that what Z is in 3D
            map_info->d_sprs.spriteScreenX = (int)((map_info->win_w / 2) * (1 + map_info->d_sprs.transformX / map_info->d_sprs.transformY));
            map_info->d_sprs.spriteHeight = abs((int)(map_info->win_h / (map_info->d_sprs.transformY))); //using 'transformY' instead of the real distance prevents fisheye
            map_info->d_sprs.drawStartY = (-1) * map_info->d_sprs.spriteHeight / 2 + map_info->win_h / 2;
            if (map_info->d_sprs.drawStartY < 0)
                map_info->d_sprs.drawStartY = 0;
            map_info->d_sprs.drawEndY = map_info->d_sprs.spriteHeight / 2 + map_info->win_h / 2;
            if (map_info->d_sprs.drawEndY >= map_info->win_h)
                map_info->d_sprs.drawEndY = map_info->win_h - 1;
            map_info->d_sprs.spriteWidth = abs((int)(map_info->win_h / (map_info->d_sprs.transformY)));
            map_info->d_sprs.drawStartX = (-1) * map_info->d_sprs.spriteWidth / 2 + map_info->d_sprs.spriteScreenX;
            if (map_info->d_sprs.drawStartX < 0)
                map_info->d_sprs.drawStartX = 0;
            map_info->d_sprs.drawEndX = map_info->d_sprs.spriteWidth / 2 + map_info->d_sprs.spriteScreenX;
            if (map_info->d_sprs.drawEndX >= map_info->win_w)
                map_info->d_sprs.drawEndX = map_info->win_w - 1;
            stripe = map_info->d_sprs.drawStartX;
            while (stripe < map_info->d_sprs.drawEndX)
            {
                map_info->d_sprs.texX = (int)(256 * (stripe - (-1 * map_info->d_sprs.spriteWidth / 2 + map_info->d_sprs.spriteScreenX)) * map_info->no_text.width / map_info->d_sprs.spriteWidth) / 256;

                if (map_info->d_sprs.transformY > 0 && stripe > 0 && stripe < map_info->win_w && map_info->d_sprs.transformY < zBuffer[stripe])
                {
                    y = map_info->d_sprs.drawStartY;
                    while (y < map_info->d_sprs.drawEndY)
                    {
                        d = (y)*256 - map_info->win_h * 128 + map_info->d_sprs.spriteHeight * 128;
                        map_info->d_sprs.texY = ((d * map_info->no_text.height) / map_info->d_sprs.spriteHeight) / 256;
                        color = ((unsigned int *)(map_info->spr.addr))[map_info->no_text.width * map_info->d_sprs.texY + map_info->d_sprs.texX];
                        if ((color & 0xFFFFFF) != 0)
                            my_mlx_pixel_put(map_info, stripe, y, color);
                        y++;
                    }
                }
                stripe++;
            }
        }
        i++;
    }
}

void make_screen(t_map *map_info)
{
    int fd;
    unsigned char bitmap[54];
    int i = 0;
    int filesize;
    unsigned int *tmp;

    filesize = map_info->win_w * map_info->win_h * 4 + 54;
    if ((fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) < 0)
        close_all(map_info);
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

void draw_picture(t_map *map_info)
{
    double *zBuffer;
    double *spriteDistance;
    int *spriteOrder;

    zBuffer = (double *)malloc(map_info->win_w * sizeof(double));
    spriteDistance = (double *)malloc(map_info->spr_l * sizeof(double));
    spriteOrder = (int *)malloc(map_info->spr_l * sizeof(int));
    draw_f_c(map_info);
    draw_walls(map_info, &zBuffer);
    set_sprites(map_info, &spriteDistance, &spriteOrder);
    draw_sprs(map_info, spriteOrder, zBuffer);
    free(zBuffer);
    free(spriteDistance);
    free(spriteOrder);
    if (map_info->screenshot == 1)
        make_screen(map_info);
    mlx_put_image_to_window(map_info->mlx, map_info->win, map_info->img, 0, 0);
}