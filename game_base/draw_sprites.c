/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:39:31 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:39:34 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	sort_sprites(int *sprite_order, double *sprite_distance, int len)
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
			if (sprite_distance[j - 1] < sprite_distance[j])
			{
				dist_perm = sprite_distance[j - 1];
				order_perm = sprite_order[j - 1];
				sprite_distance[j - 1] = sprite_distance[j];
				sprite_distance[j] = dist_perm;
				sprite_order[j - 1] = sprite_order[j];
				sprite_order[j] = order_perm;
			}
			j--;
		}
		i++;
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
