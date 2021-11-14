/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:39:02 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:39:05 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
