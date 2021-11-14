/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_let.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:38:24 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:38:26 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	verify_f_c(char **map, int *i)
{
	if ((map[*i][0] == 'F' && map[*i][1] == ' ') ||
		(map[*i][0] == 'C' && map[*i][1] == ' '))
		return (-1);
	else
		return (0);
}

int	verify_sides(char **map, int *i)
{
	if ((map[*i][0] == 'N' && map[*i][1] == 'O') ||
		(map[*i][0] == 'S' && map[*i][1] == 'O') ||
		(map[*i][0] == 'W' && map[*i][1] == 'E') ||
		(map[*i][0] == 'E' && map[*i][1] == 'A') ||
		(map[*i][0] == 'S' && map[*i][1] == ' '))
		return (1);
	else
		return (0);
}

int	check_r(char *map_line, t_map *main_info)
{
	if (main_info->winh || main_info->winw)
		return (-1);
	map_line++;
	while (*map_line == ' ')
		map_line++;
	if (!(*map_line >= '0' && *map_line <= '9'))
		return (-1);
	main_info->winw = ft_atoi(map_line);
	while (*map_line >= '0' && *map_line <= '9')
		map_line++;
	while (*map_line == ' ')
		map_line++;
	if (!(*map_line >= '0' && *map_line <= '9'))
		return (-1);
	main_info->winh = ft_atoi(map_line);
	while (*map_line >= '0' && *map_line <= '9')
		map_line++;
	if (*map_line)
		return (-1);
	return (0);
}

int	check_let(char **map, t_map *main_info)
{
	int	i;

	i = -1;
	while (++i < 8 && map[i])
	{
		if (map[i][0] == 'R' && map[i][1] == ' ')
		{
			if (check_r(map[i], main_info) < 0)
				return (-2);
		}
		else if (verify_sides(map, &i))
		{
			if (check_sides(map[i], main_info) < 0)
				return (-3);
		}
		else if (verify_f_c(map, &i))
		{
			if (check_f_c(map[i], main_info) < 0)
				return (-4);
		}
		else
			return (-5);
	}
	return (0);
}
