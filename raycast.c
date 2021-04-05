#include "raycast.h"

void set_walls_s(t_map *m, int p)
{
    m->walls.cameraX = 2 * p / (double)m->win_w - 1;
    m->walls.rayx = m->dirX + m->planeX * m->walls.cameraX;
    m->walls.rayy = m->dirY + m->planeY * m->walls.cameraX;
    m->walls.mapX = (int)(m->posX);
    m->walls.mapY = (int)(m->posY);
    m->walls.deltaDistX = fabs(1 / m->walls.rayx);
    m->walls.deltaDistY = fabs(1 / m->walls.rayy);
    m->walls.hit = 0;
}

void move_ray(t_map *m)
{
    if (m->walls.rayx < 0)
    {
        m->walls.stepX = -1;
        m->walls.sideDistX = (m->posX - m->walls.mapX) * m->walls.deltaDistX;
    }
    else
    {
        m->walls.stepX = 1;
        m->walls.sideDistX = (m->walls.mapX + 1.0 - m->posX) * m->walls.deltaDistX;
    }
    if (m->walls.rayy < 0)
    {
        m->walls.stepY = -1;
        m->walls.sideDistY = (m->posY - m->walls.mapY) * m->walls.deltaDistY;
    }
    else
    {
        m->walls.stepY = 1;
        m->walls.sideDistY = (m->walls.mapY + 1.0 - m->posY) * m->walls.deltaDistY;
    }
}

void check_hit(t_map *m)
{
    while (m->walls.hit == 0)
    {
        if (m->walls.sideDistX < m->walls.sideDistY)
        {
            m->walls.sideDistX += m->walls.deltaDistX;
            m->walls.mapX += m->walls.stepX;
            m->walls.side = 0;
        }
        else
        {
            m->walls.sideDistY += m->walls.deltaDistY;
            m->walls.mapY += m->walls.stepY;
            m->walls.side = 1;
        }
        if (m->map[m->walls.mapY][m->walls.mapX] != '0' &&
            m->map[m->walls.mapY][m->walls.mapX] != 'N' &&
            m->map[m->walls.mapY][m->walls.mapX] != 'W' &&
            m->map[m->walls.mapY][m->walls.mapX] != 'E' &&
            m->map[m->walls.mapY][m->walls.mapX] != 'S' &&
            m->map[m->walls.mapY][m->walls.mapX] != '2')
            m->walls.hit = 1;
    }
}

void draw_line(t_map *m, int p)
{
    unsigned int color;
    int y;

    y = m->walls.drawStart;
    while (y < m->walls.drawEnd)
    {
        m->walls.texY = (int)(m->walls.texPos) & (m->we_t.height - 1);
        m->walls.texPos += m->walls.step;
        if (m->walls.side == 0 && m->walls.rayx >= 0)
            color = ((unsigned int *)(m->we_t.addr))[m->we_t.width * m->walls.texY + m->walls.texX];
        else if (m->walls.side == 0 && m->walls.rayx <= 0)
            color = ((unsigned int *)(m->ea_t.addr))[m->ea_t.width * m->walls.texY + m->walls.texX];
        else if (m->walls.side == 1 && m->walls.rayy <= 0)
            color = ((unsigned int *)(m->no_t.addr))[m->no_t.width * m->walls.texY + m->walls.texX];
        else if (m->walls.side == 1 && m->walls.rayy >= 0)
            color = ((unsigned int *)(m->so_t.addr))[m->so_t.width * m->walls.texY + m->walls.texX];
        my_mlx_pixel_put(m, p, y, color);
        y++;
    }
}

void count_w_c(t_map *m)
{
    if (m->walls.side == 0)
        m->walls.wall_d = (m->walls.mapX - m->posX + (1 - m->walls.stepX) / 2) / m->walls.rayx;
    else
        m->walls.wall_d = (m->walls.mapY - m->posY + (1 - m->walls.stepY) / 2) / m->walls.rayy;
    m->walls.lh = (int)(m->win_h / m->walls.wall_d);
    m->walls.drawStart = m->win_h / 2 - m->walls.lh / 2;
    if (m->walls.drawStart < 0)
        m->walls.drawStart = 0;
    m->walls.drawEnd = m->walls.lh / 2 + m->win_h / 2;
    if (m->walls.drawEnd >= m->win_h)
        m->walls.drawEnd = m->win_h - 1;
}

void draw_walls(t_map *m, double **zBuffer)
{
    int p;

    p = -1;
    while (++p < m->win_w)
    {
        set_walls_s(m, p);
        move_ray(m);
        check_hit(m);
        count_w_c(m);
        if (m->walls.side == 0)
            m->walls.wallX = m->posY + m->walls.wall_d * m->walls.rayy;
        else
            m->walls.wallX = m->posX + m->walls.wall_d * m->walls.rayx;
        m->walls.wallX -= floor((m->walls.wallX));
        m->walls.texX = (int)(m->walls.wallX * (double)(m->no_t.width));
        if (m->walls.side == 0 && m->walls.rayx <= 0)
            m->walls.texX = m->ea_t.width - 1 - m->walls.texX;
        if (m->walls.side == 1 && m->walls.rayy >= 0)
            m->walls.texX = m->so_t.width - 1 - m->walls.texX;
        m->walls.step = 1.0 * m->no_t.height / m->walls.lh;
        m->walls.texPos = (m->walls.drawStart - m->win_h / 2 + m->walls.lh / 2);
        m->walls.texPos *= m->walls.step;
        draw_line(m, p);
        (*zBuffer)[p] = m->walls.wall_d;
    }
}

void set_sprites(t_map *m, double **spr_dist, int **spr_ord)
{
    int i;

    i = 0;
    while (i < m->spr_l)
    {
        (*spr_ord)[i] = i;
        (*spr_dist)[i] = (m->posX - m->sprites[i].x) * (m->posX - m->sprites[i].x);
        (*spr_dist)[i] += (m->posY - m->sprites[i].y) * (m->posY - m->sprites[i].y);
        i++;
    }
    sort_sprites(*spr_ord, *spr_dist, m->spr_l);
}

void set_sprs_v(t_map *m, int *stripe)
{
    m->d_sprs.invDet = 1.0 / (m->planeX * m->dirY - m->dirX * m->planeY);
    m->d_sprs.transformX = m->d_sprs.invDet * (m->dirY * m->d_sprs.spriteX - m->dirX * m->d_sprs.spriteY);
    m->d_sprs.transformY = m->d_sprs.invDet * ((m->planeY) * -1 * m->d_sprs.spriteX + m->planeX * m->d_sprs.spriteY);
    m->d_sprs.spriteScreenX = (int)((m->win_w / 2) * (1 + m->d_sprs.transformX / m->d_sprs.transformY));
    m->d_sprs.spriteHeight = abs((int)(m->win_h / (m->d_sprs.transformY)));
    m->d_sprs.drawStartY = (-1) * m->d_sprs.spriteHeight / 2 + m->win_h / 2;
    if (m->d_sprs.drawStartY < 0)
        m->d_sprs.drawStartY = 0;
    m->d_sprs.drawEndY = m->d_sprs.spriteHeight / 2 + m->win_h / 2;
    if (m->d_sprs.drawEndY >= m->win_h)
        m->d_sprs.drawEndY = m->win_h - 1;
    m->d_sprs.spriteWidth = abs((int)(m->win_h / (m->d_sprs.transformY)));
    m->d_sprs.drawStartX = (-1) * m->d_sprs.spriteWidth / 2 + m->d_sprs.spriteScreenX;
    if (m->d_sprs.drawStartX < 0)
        m->d_sprs.drawStartX = 0;
    m->d_sprs.drawEndX = m->d_sprs.spriteWidth / 2 + m->d_sprs.spriteScreenX;
    if (m->d_sprs.drawEndX >= m->win_w)
        m->d_sprs.drawEndX = m->win_w - 1;
    *stripe = m->d_sprs.drawStartX - 1;
}

void pixel_sprs(t_map *m, int *stripe, double *buffer)
{
    int y;
    int d;
    unsigned int color;

    while (++(*stripe) < m->d_sprs.drawEndX)
    {
        m->d_sprs.texX = (int)(256 * (*stripe - (-(m->d_sprs.spriteWidth) / 2 + m->d_sprs.spriteScreenX)) * m->no_t.width / m->d_sprs.spriteWidth) / 256;
        if (m->d_sprs.transformY > 0 && *stripe > 0 && *stripe < m->win_w && m->d_sprs.transformY < buffer[*stripe])
        {
            y = m->d_sprs.drawStartY - 1;
            while (++y < m->d_sprs.drawEndY)
            {
                d = (y)*256 - m->win_h * 128 + m->d_sprs.spriteHeight * 128;
                m->d_sprs.texY = ((d * m->no_t.height) / m->d_sprs.spriteHeight) / 256;
                color = ((unsigned int *)(m->spr.addr))[m->no_t.width * m->d_sprs.texY + m->d_sprs.texX];
                if ((color & 0xFFFFFF) != 0)
                    my_mlx_pixel_put(m, *stripe, y, color);
            }
        }
    }
}

void draw_sprs(t_map *m, int *spr_ord, double *buffer)
{
    int i;
    int stripe;

    i = -1;
    while (++i < m->spr_l)
    {
        if (!(((int)m->posX == (int)m->sprites[spr_ord[i]].x) &&
              ((int)m->posY == (int)m->sprites[spr_ord[i]].y)))
        {
            m->d_sprs.spriteX = m->sprites[spr_ord[i]].x - m->posX;
            m->d_sprs.spriteY = m->sprites[spr_ord[i]].y - m->posY;
            set_sprs_v(m, &stripe);
            pixel_sprs(m, &stripe, buffer);
        }
    }
}

void set_bitmap(t_map *m, int *fd)
{
    unsigned char bitmap[54];
    int i;
    int filesize;

    filesize = m->win_w * m->win_h * 4 + 54;
    i = 0;
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
    *(int *)(bitmap + 18) = m->win_w;
    *(int *)(bitmap + 22) = m->win_h;
    *(bitmap + 26) = 1;
    *(bitmap + 28) = 32;
    write(*fd, bitmap, 54);
}

void make_screen(t_map *m)
{
    int fd;
    unsigned int *color;
    int i;
    int j;

    if ((fd = open("screen.bmp", O_CREAT)) < 0)
        close_all(m);
    set_bitmap(m, &fd);
    i = (m->win_h - 1) * m->win_w;
    color = (unsigned int *)m->addr;
    while (i >= 0)
    {
        j = 0;
        while (j < m->win_w)
        {
            write(fd, &color[i], 4);
            j++;
            i++;
        }
        i -= 2 * m->win_w;
    }
    close(fd);
    close_all(m);
}

void draw_picture(t_map *m)
{
    double *zBuffer;
    double *spr_dist;
    int *spr_ord;

    zBuffer = (double *)malloc(m->win_w * sizeof(double));
    spr_dist = (double *)malloc(m->spr_l * sizeof(double));
    spr_ord = (int *)malloc(m->spr_l * sizeof(int));
    draw_f_c(m);
    draw_walls(m, &zBuffer);
    set_sprites(m, &spr_dist, &spr_ord);
    draw_sprs(m, spr_ord, zBuffer);
    free(zBuffer);
    free(spr_dist);
    free(spr_ord);
    if (m->screenshot == 1)
        make_screen(m);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}