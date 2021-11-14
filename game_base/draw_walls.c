/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:39:44 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:39:46 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
