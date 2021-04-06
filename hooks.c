/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:40:51 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:40:52 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	esc_hook(t_map *m)
{
	if (m->keys.esc == 1)
		close_all(m);
}

void	l_r_hook(t_map *m)
{
	double	oldpx;
	double	olddx;
	double	speed;
	double	move;

	speed = 0.03;
	move = 0.08;
	if (m->keys.left == 1)
	{
		olddx = m->dx;
		m->dx = m->dx * cos(-speed) - m->dy * sin(-speed);
		m->dy = (olddx * sin(-speed) + m->dy * cos(-speed));
		oldpx = m->px;
		m->px = (m->px * cos(-speed) - m->py * sin(-speed));
		m->py = (oldpx * sin(-speed) + m->py * cos(-speed));
	}
	if (m->keys.right == 1)
	{
		olddx = m->dx;
		m->dx = m->dx * cos(speed) - m->dy * sin(speed);
		m->dy = (olddx * sin(speed) + m->dy * cos(speed));
		oldpx = m->px;
		m->px = (m->px * cos(speed) - m->py * sin(speed));
		m->py = (oldpx * sin(speed) + m->py * cos(speed));
	}
}

void	w_s_hook(t_map *m)
{
	double	speed;
	double	move;

	speed = 0.03;
	move = 0.08;
	if (m->keys.w == 1)
	{
		if (m->map[(int)(m->y + (m->dy) * move)][(int)(m->x)] != '1')
			m->y += (m->dy) * move;
		if (m->map[(int)(m->y)][(int)(m->x + (m->dx) * move)] != '1')
			m->x += (m->dx) * move;
	}
	if (m->keys.s == 1)
	{
		if (m->map[(int)(m->y - (m->dy) * move)][(int)(m->x)] != '1')
			m->y -= (m->dy) * move;
		if (m->map[(int)(m->y)][(int)(m->x - (m->dx) * move)] != '1')
			m->x -= (m->dx) * move;
	}
}

void	a_d_hook(t_map *m)
{
	double	speed;
	double	move;

	speed = 0.03;
	move = 0.08;
	if (m->keys.a == 1)
	{
		if (m->map[(int)(m->y - (m->dx) * move)][(int)(m->x)] != '1')
			m->y -= (m->dx) * move;
		if (m->map[(int)(m->y)][(int)(m->x + (m->dy) * move)] != '1')
			m->x += (m->dy) * move;
	}
	if (m->keys.d == 1)
	{
		if (m->map[(int)(m->y + (m->dx) * move)][(int)(m->x)] != '1')
			m->y += (m->dx) * move;
		if (m->map[(int)(m->y)][(int)(m->x - (m->dy) * move)] != '1')
			m->x -= (m->dy) * move;
	}
}
