#include "main.h"

int	check_n_s_xpm(t_map *info)
{
	int	i;

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

int	write_info(char ***map, t_map *m, char **argv)
{
	int		fd;
	int		ret;
	int		err;
	char	map_str[BUF_SIZE + 1];

	if (((fd = open(argv[1], O_RDWR)) < 0))
	{
		print_err(-17);
		return (-1);
	}
	while ((ret = read(fd, map_str, BUF_SIZE)))
		map_str[ret] = '\0';
	close(fd);
	if (!(*map = ft_split(map_str, '\n')))
	{
		print_err(-100);
		return (-1);
	}
	if ((err = check_info(*map, m)) < 0)
	{
		print_err(err);
		free_arr(map);
		return (-1);
	}
	return (0);
}
