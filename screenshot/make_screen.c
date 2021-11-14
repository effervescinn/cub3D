/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:41:18 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:41:20 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

	if ((fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) < 0)
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
