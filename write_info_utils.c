/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_info_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnorcros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:42:23 by lnorcros          #+#    #+#             */
/*   Updated: 2021/04/06 17:42:24 by lnorcros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_n_s_xpm(t_map *info)
{
	int i;

	i = ft_strlen(info->no);
	if (i < 5)
		return (-11);
	i--;
	if (info->no[i] != 'm' || info->no[i - 1] != 'p' ||
		info->no[i - 2] != 'x' || info->no[i - 3] != '.')
		return (-11);
	i = ft_strlen(info->so);
	if (i < 5)
		return (-11);
	i--;
	if (info->so[i] != 'm' || info->so[i - 1] != 'p' ||
		info->so[i - 2] != 'x' || info->so[i - 3] != '.')
		return (-11);
	return (0);
}

int	check_w_e_xpm(t_map *info)
{
	int	i;

	i = ft_strlen(info->we);
	if (i < 5)
		return (-11);
	i--;
	if (info->we[i] != 'm' || info->we[i - 1] != 'p' ||
		info->we[i - 2] != 'x' || info->we[i - 3] != '.')
		return (-11);
	i = ft_strlen(info->ea);
	if (i < 5)
		return (-11);
	i--;
	if (info->ea[i] != 'm' || info->ea[i - 1] != 'p' ||
		info->ea[i - 2] != 'x' || info->ea[i - 3] != '.')
		return (-11);
	return (0);
}

int	check_spr_xpm(t_map *info)
{
	int	i;

	i = ft_strlen(info->s);
	if (i < 5)
		return (-12);
	i--;
	if (info->s[i] != 'm' || info->s[i - 1] != 'p' ||
		info->s[i - 2] != 'x' || info->s[i - 3] != '.')
		return (-12);
	return (0);
}

int	check_info(char **map, t_map *info)
{
	int	ret;

	if ((ret = check_let(map, info)) < 0)
		return (ret);
	if ((ret = check_n_s_xpm(info)) < 0)
		return (ret);
	if ((ret = check_w_e_xpm(info)) < 0)
		return (ret);
	if ((ret = check_spr_xpm(info)) < 0)
		return (ret);
	if (!(info->no) || !(info->so) || !(info->we) || !(info->ea) ||
		!(info->ea) || !(info->floor.type) || !(info->ceil.type))
		return (-6);
	if (info->winh <= 0 || info->winw <= 0)
		return (-7);
	if (!(info->floor.b >= 0 && info->floor.b <= 255) ||
		!(info->floor.r >= 0 && info->floor.r <= 255) ||
		!(info->floor.g >= 0 && info->floor.g <= 255) ||
		!(info->ceil.g >= 0 && info->ceil.g <= 255) ||
		!(info->ceil.r >= 0 && info->ceil.r <= 255) ||
		!(info->ceil.b >= 0 && info->ceil.b <= 255))
		return (-8);
	return (0);
}

int	use_gnl(char ***map, char **line, char **map_str, int fd)
{
	char	*tmp;

	(*map_str)[0] = '\0';
	while ((get_next_line(fd, line)))
	{
		tmp = *map_str;
		*map_str = ft_strjoin(tmp, *line);
		free(tmp);
		tmp = *map_str;
		*map_str = ft_strjoin(tmp, "\n");
		free(tmp);
		free(*line);
	}
	tmp = *map_str;
	*map_str = ft_strjoin(tmp, *line);
	free(tmp);
	free(*line);
	close(fd);
	if (!(*map = ft_split(*map_str, '\n')))
	{
		print_err(-100);
		free(*map_str);
		return (-1);
	}
	return (0);
}
