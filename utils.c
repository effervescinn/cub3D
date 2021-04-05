#include "main.h"

int		close_all(t_map *m)
{
	free(m->sprites);
	free_arr(&(m->map));
	mlx_destroy_image(m->mlx, m->img);
	if (m->win)
		mlx_destroy_window(m->mlx, m->win);
	exit(0);
	return (0);
}

void	free_arr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
}

void	print_err(int err)
{
	err_first(err);
	err_second(err);
}

char	*get_ad(void *ptr, int *bpp, int *sl, int *e)
{
	return (mlx_get_data_addr(ptr, bpp, sl, e));
}

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
}
