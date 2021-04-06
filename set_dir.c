/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:41:34 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:41:36 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	set_n(t_map *main_info)
{
	main_info->dx = 0;
	main_info->dy = -1;
	main_info->px = 0.57;
	main_info->py = 0;
}

void	set_s(t_map *main_info)
{
	main_info->dx = 0;
	main_info->dy = 1;
	main_info->px = -0.57;
	main_info->py = 0;
}

void	set_w(t_map *main_info)
{
	main_info->dx = -1;
	main_info->dy = 0;
	main_info->px = 0;
	main_info->py = -0.57;
}

void	set_e(t_map *main_info)
{
	main_info->dx = 1;
	main_info->dy = 0;
	main_info->px = 0;
	main_info->py = 0.57;
}

void	set_dir(t_map *main_info, char letter)
{
	if (letter == 'N')
		set_n(main_info);
	else if (letter == 'S')
		set_s(main_info);
	else if (letter == 'W')
		set_w(main_info);
	else if (letter == 'E')
		set_e(main_info);
}
