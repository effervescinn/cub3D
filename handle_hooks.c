#include "main.h"

int		unpressed_key(int keycode, t_map *m)
{
	if (keycode == KEY_W)
		m->keys.w = 0;
	if (keycode == KEY_S)
		m->keys.s = 0;
	if (keycode == KEY_A)
		m->keys.a = 0;
	if (keycode == KEY_D)
		m->keys.d = 0;
	if (keycode == KEY_LEFT)
		m->keys.left = 0;
	if (keycode == KEY_RIGHT)
		m->keys.right = 0;
	return (0);
}

int		pressed_key(int keycode, t_map *m)
{
	if (keycode == KEY_W)
		m->keys.w = 1;
	if (keycode == KEY_S)
		m->keys.s = 1;
	if (keycode == KEY_A)
		m->keys.a = 1;
	if (keycode == KEY_D)
		m->keys.d = 1;
	if (keycode == KEY_LEFT)
		m->keys.left = 1;
	if (keycode == KEY_RIGHT)
		m->keys.right = 1;
	if (keycode == ESC)
		m->keys.esc = 1;
	return (0);
}

int		key_hook(t_map *m)
{
	esc_hook(m);
	l_r_hook(m);
	w_s_hook(m);
	a_d_hook(m);
	draw_picture(m);
	return (0);
}

void	track_hooks(t_map *m)
{
	mlx_loop_hook(m->mlx, key_hook, m);
	mlx_hook(m->win, 2, 0, pressed_key, m);
	mlx_hook(m->win, 17, 0, close_all, m);
	mlx_hook(m->win, 3, 0, unpressed_key, m);
	mlx_loop(m->mlx);
}