/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sides_floor_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:38:35 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:38:36 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_f_c(char *map_line, t_color *c_type)
{
	while (*map_line == ' ')
		map_line++;
	if (!(*map_line >= '0' && *map_line <= '9'))
		return (-1);
	c_type->r = ft_atoi(map_line);
	while (*map_line >= '0' && *map_line <= '9')
		map_line++;
	if (*(map_line++) != ',')
		return (-1);
	if (!(*map_line >= '0' && *map_line <= '9'))
		return (-1);
	c_type->g = ft_atoi(map_line);
	while (*map_line >= '0' && *map_line <= '9')
		map_line++;
	if (*(map_line++) != ',')
		return (-1);
	if (!(*map_line >= '0' && *map_line <= '9'))
		return (-1);
	c_type->b = ft_atoi(map_line);
	while (*map_line >= '0' && *map_line <= '9')
		map_line++;
	if (*map_line)
		return (-1);
	return (0);
}

int	check_f_c(char *map_line, t_map *m)
{
	if (*map_line == 'F')
	{
		if (m->floor.type)
			return (-1);
		m->floor.type = "F";
		map_line++;
		if (set_f_c(map_line, &(m->floor)) < 0)
			return (-1);
	}
	if (*map_line == 'C')
	{
		if (m->ceil.type)
			return (-1);
		m->ceil.type = "C";
		map_line++;
		if (set_f_c(map_line, &(m->ceil)) < 0)
			return (-1);
	}
	return (0);
}

int	set_walls(char *map_line, t_map *main_info, int *i)
{
	if (map_line[0] == 'N')
	{
		if (main_info->no)
			return (-1);
		main_info->no = ft_strdup(&(map_line[*i]));
	}
	else if (map_line[0] == 'W')
	{
		if (main_info->we)
			return (-1);
		main_info->we = ft_strdup(&(map_line[*i]));
	}
	else if (map_line[0] == 'E')
	{
		if (main_info->ea)
			return (-1);
		main_info->ea = ft_strdup(&(map_line[*i]));
	}
	else if (map_line[0] == 'S' && map_line[1] == 'O')
	{
		if (main_info->so)
			return (-1);
		main_info->so = ft_strdup(&(map_line[*i]));
	}
	return (0);
}

int	check_sides(char *map_line, t_map *main_info)
{
	int	i;

	i = 0;
	if (map_line[i] == 'S' && map_line[i + 1] == ' ')
		i += 1;
	else
		i += 2;
	if (map_line[i++] != ' ' || !map_line[i])
		return (-1);
	while (map_line[i] == ' ')
		i++;
	if (map_line[i] == '\0')
		return (-1);
	if (set_walls(map_line, main_info, &i) < 0)
		return (-1);
	else if (map_line[0] == 'S' && map_line[1] == ' ')
	{
		if (main_info->s)
			return (-1);
		main_info->s = ft_strdup(&(map_line[i]));
	}
	return (0);
}
