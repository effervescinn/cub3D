#include "main.h"

void my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	char *dst;

	dst = data->ad + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int make_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void draw_f_c(t_map *m)
{
	int	i;
	int	j;
	int	c_color;
	int	f_color;

	i = 0;
	c_color = make_color(m->ceil.r, m->ceil.g, m->ceil.b);
	f_color = make_color(m->floor.r, m->floor.g, m->floor.b);
	while (i < (m->winh / 2))
	{
		j = -1;
		while (++j < m->winw)
			my_mlx_pixel_put(m, j, i, c_color);
		i++;
	}
	while (i < (m->winh))
	{
		j = -1;
		while (++j < m->winw)
			my_mlx_pixel_put(m, j, i, f_color);
		i++;
	}
}

void sort_sprites(int *spriteOrder, double *spriteDistance, int len)
{
	int		i;
	int		j;
	double	dist_perm;
	int		order_perm;

	i = 0;
	while (i < len - 1)
	{
		j = len - 1;
		while (j > i)
		{
			if (spriteDistance[j - 1] < spriteDistance[j])
			{
				dist_perm = spriteDistance[j - 1];
				order_perm = spriteOrder[j - 1];
				spriteDistance[j - 1] = spriteDistance[j];
				spriteDistance[j] = dist_perm;
				spriteOrder[j - 1] = spriteOrder[j];
				spriteOrder[j] = order_perm;
			}
			j--;
		}
		i++;
	}
}
void	set_walls_s(t_map *m, int p)
{
	m->walls.camerax = 2 * p / (double)m->winw - 1;
	m->walls.rayx = m->dx + m->px * m->walls.camerax;
	m->walls.rayy = m->dy + m->py * m->walls.camerax;
	m->walls.mapx = (int)(m->x);
	m->walls.mapy = (int)(m->y);
	m->walls.ddx = fabs(1 / m->walls.rayx);
	m->walls.ddy = fabs(1 / m->walls.rayy);
	m->walls.hit = 0;
}

void	move_ray(t_map *m)
{
	if (m->walls.rayx < 0)
	{
		m->walls.stepx = -1;
		m->walls.sdx = (m->x - m->walls.mapx) * m->walls.ddx;
	}
	else
	{
		m->walls.stepx = 1;
		m->walls.sdx = (m->walls.mapx + 1.0 - m->x) * m->walls.ddx;
	}
	if (m->walls.rayy < 0)
	{
		m->walls.stepy = -1;
		m->walls.sdy = (m->y - m->walls.mapy) * m->walls.ddy;
	}
	else
	{
		m->walls.stepy = 1;
		m->walls.sdy = (m->walls.mapy + 1.0 - m->y) * m->walls.ddy;
	}
}

void	check_hit(t_map *m)
{
	while (m->walls.hit == 0)
	{
		if (m->walls.sdx < m->walls.sdy)
		{
			m->walls.sdx += m->walls.ddx;
			m->walls.mapx += m->walls.stepx;
			m->walls.side = 0;
		}
		else
		{
			m->walls.sdy += m->walls.ddy;
			m->walls.mapy += m->walls.stepy;
			m->walls.side = 1;
		}
		if (m->map[m->walls.mapy][m->walls.mapx] != '0' &&
			m->map[m->walls.mapy][m->walls.mapx] != 'N' &&
			m->map[m->walls.mapy][m->walls.mapx] != 'W' &&
			m->map[m->walls.mapy][m->walls.mapx] != 'E' &&
			m->map[m->walls.mapy][m->walls.mapx] != 'S' &&
			m->map[m->walls.mapy][m->walls.mapx] != '2')
			m->walls.hit = 1;
	}
}

void	get_tex_color(t_map *m, t_img tex_str, unsigned int *color)
{
	unsigned int	*tmp;

	tmp = (unsigned int *)tex_str.ad;
	*color = tmp[tex_str.w * m->walls.texy + m->walls.texx];
}

void	draw_line(t_map *m, int p)
{
	unsigned int	color;
	int				y;

	y = m->walls.start;
	while (y < m->walls.end)
	{
		m->walls.texy = (int)(m->walls.texpos) & (m->we_t.h - 1);
		m->walls.texpos += m->walls.step;
		if (m->walls.side == 0 && m->walls.rayx >= 0)
			get_tex_color(m, m->we_t, &color);
		else if (m->walls.side == 0 && m->walls.rayx <= 0)
			get_tex_color(m, m->ea_t, &color);
		else if (m->walls.side == 1 && m->walls.rayy <= 0)
			get_tex_color(m, m->no_t, &color);
		else if (m->walls.side == 1 && m->walls.rayy >= 0)
			get_tex_color(m, m->so_t, &color);
		my_mlx_pixel_put(m, p, y, color);
		y++;
	}
}

void	count_w_c(t_map *m)
{
	if (m->walls.side == 0)
		m->walls.wall_d = (m->walls.mapx - m->x +
		(1 - m->walls.stepx) / 2) / m->walls.rayx;
	else
		m->walls.wall_d = (m->walls.mapy - m->y +
		(1 - m->walls.stepy) / 2) / m->walls.rayy;
	m->walls.lh = (int)(m->winh / m->walls.wall_d);
	m->walls.start = (m->winh - m->walls.lh) / 2;
	if (m->walls.start < 0)
		m->walls.start = 0;
	m->walls.end = m->walls.lh / 2 + m->winh / 2;
	if (m->walls.end >= m->winh)
		m->walls.end = m->winh - 1;
}

void	draw_walls(t_map *m, double **buffer)
{
	int	p;

	p = -1;
	while (++p < m->winw)
	{
		set_walls_s(m, p);
		move_ray(m);
		check_hit(m);
		count_w_c(m);
		if (m->walls.side == 0)
			m->walls.wallx = m->y + m->walls.wall_d * m->walls.rayy;
		else
			m->walls.wallx = m->x + m->walls.wall_d * m->walls.rayx;
		m->walls.wallx -= floor((m->walls.wallx));
		m->walls.texx = (int)(m->walls.wallx * (double)(m->no_t.w));
		if (m->walls.side == 0 && m->walls.rayx <= 0)
			m->walls.texx = m->ea_t.w - 1 - m->walls.texx;
		if (m->walls.side == 1 && m->walls.rayy >= 0)
			m->walls.texx = m->so_t.w - 1 - m->walls.texx;
		m->walls.step = 1.0 * m->no_t.h / m->walls.lh;
		m->walls.texpos = (m->walls.start - m->winh / 2 + m->walls.lh / 2);
		m->walls.texpos *= m->walls.step;
		draw_line(m, p);
		(*buffer)[p] = m->walls.wall_d;
	}
}

void	set_sprites(t_map *m, double **spr_dist, int **spr_ord)
{
	int	i;

	i = 0;
	while (i < m->spr_l)
	{
		(*spr_ord)[i] = i;
		(*spr_dist)[i] = (m->x - m->sprites[i].x) * (m->x - m->sprites[i].x);
		(*spr_dist)[i] += (m->y - m->sprites[i].y) * (m->y - m->sprites[i].y);
		i++;
	}
	sort_sprites(*spr_ord, *spr_dist, m->spr_l);
}

void	set_sprs_v(t_map *m, int *stripe)
{
	m->d_sprs.id = 1.0 / (m->px * m->dy - m->dx * m->py);
	m->d_sprs.tx = m->d_sprs.id * (m->dy * m->d_sprs.sprx -
	m->dx * m->d_sprs.spry);
	m->d_sprs.ty = m->d_sprs.id * (-(m->py) * m->d_sprs.sprx +
	m->px * m->d_sprs.spry);
	m->d_sprs.scr_x = (int)((m->winw / 2) * (1 + m->d_sprs.tx / m->d_sprs.ty));
	m->d_sprs.h = abs((int)(m->winh / (m->d_sprs.ty)));
	m->d_sprs.starty = (-1) * m->d_sprs.h / 2 + m->winh / 2;
	if (m->d_sprs.starty < 0)
		m->d_sprs.starty = 0;
	m->d_sprs.endy = m->d_sprs.h / 2 + m->winh / 2;
	if (m->d_sprs.endy >= m->winh)
		m->d_sprs.endy = m->winh - 1;
	m->d_sprs.w = abs((int)(m->winh / (m->d_sprs.ty)));
	m->d_sprs.startx = (-1) * m->d_sprs.w / 2 + m->d_sprs.scr_x;
	if (m->d_sprs.startx < 0)
		m->d_sprs.startx = 0;
	m->d_sprs.endx = m->d_sprs.w / 2 + m->d_sprs.scr_x;
	if (m->d_sprs.endx >= m->winw)
		m->d_sprs.endx = m->winw - 1;
	*stripe = m->d_sprs.startx - 1;
}

void	pixel_sprs(t_map *m, int *stripe, double *buffer)
{
	int				y;
	int				d;
	unsigned int	color;

	while (++(*stripe) < m->d_sprs.endx)
	{
		m->d_sprs.texx = (int)(256 * (*stripe - (-(m->d_sprs.w) /
		2 + m->d_sprs.scr_x)) * m->no_t.w / m->d_sprs.w) / 256;
		if (m->d_sprs.ty > 0 && *stripe > 0 && *stripe <
		m->winw && m->d_sprs.ty < buffer[*stripe])
		{
			y = m->d_sprs.starty - 1;
			while (++y < m->d_sprs.endy)
			{
				d = (y) * 256 - m->winh * 128 + m->d_sprs.h * 128;
				m->d_sprs.texy = ((d * m->no_t.h) / m->d_sprs.h) / 256;
				color = ((unsigned int *)(m->spr.ad))[m->no_t.w *
				m->d_sprs.texy + m->d_sprs.texx];
				if ((color & 0xFFFFFF) != 0)
					my_mlx_pixel_put(m, *stripe, y, color);
			}
		}
	}
}

void	draw_sprs(t_map *m, int *spr_ord, double *buffer)
{
	int	i;
	int	stripe;

	i = -1;
	while (++i < m->spr_l)
	{
		if (!(((int)m->x == (int)m->sprites[spr_ord[i]].x) &&
			((int)m->y == (int)m->sprites[spr_ord[i]].y)))
		{
			m->d_sprs.sprx = m->sprites[spr_ord[i]].x - m->x;
			m->d_sprs.spry = m->sprites[spr_ord[i]].y - m->y;
			set_sprs_v(m, &stripe);
			pixel_sprs(m, &stripe, buffer);
		}
	}
}

void	set_bitmap(t_map *m, int *fd)
{
	unsigned char	bitmap[54];
	int				i;
	int				filesize;

	filesize = m->winw * m->winh * 4 + 54;
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
	*(int *)(bitmap + 18) = m->winw;
	*(int *)(bitmap + 22) = m->winh;
	*(bitmap + 26) = 1;
	*(bitmap + 28) = 32;
	write(*fd, bitmap, 54);
}

void	make_screen(t_map *m)
{
	int				fd;
	unsigned int	*color;
	int				i;
	int				j;

	if ((fd = open("screen.bmp", O_CREAT)) < 0)
		close_all(m);
	set_bitmap(m, &fd);
	i = (m->winh - 1) * m->winw;
	color = (unsigned int *)m->ad;
	while (i >= 0)
	{
		j = 0;
		while (j < m->winw)
		{
			write(fd, &color[i], 4);
			j++;
			i++;
		}
		i -= 2 * m->winw;
	}
	close(fd);
	close_all(m);
}

void	draw_picture(t_map *m)
{
	double	*buffer;
	double	*spr_dist;
	int		*spr_ord;

	buffer = (double *)malloc(m->winw * sizeof(double));
	spr_dist = (double *)malloc(m->spr_l * sizeof(double));
	spr_ord = (int *)malloc(m->spr_l * sizeof(int));
	draw_f_c(m);
	draw_walls(m, &buffer);
	set_sprites(m, &spr_dist, &spr_ord);
	draw_sprs(m, spr_ord, buffer);
	free(buffer);
	free(spr_dist);
	free(spr_ord);
	if (m->screenshot == 1)
		make_screen(m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}
