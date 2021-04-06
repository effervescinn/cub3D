#ifndef MAIN_H
# define MAIN_H
# include "libft/libft.h"
# include <mlx.h>
# include <stdio.h>

# define BUF_SIZE 1024
# define ESC 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define ERROR "Error"
# define FD_ERROR "Wrong file"
# define RES_ERROR "Resolution error"
# define TEXT_ERROR "Textures error"
# define F_C_ERROR "Floor or ceiling error"
# define ODD_ERROR "Odd line"
# define MISS_ERROR "Missed information"
# define RES_SIZE_ERROR "Wrong resolution"
# define COLOR_ERROR "Wrong colors"
# define PLAYER_ERROR "Player is not one"
# define MAP_ERROR "Invalid map"
# define XPM_WALL_ERROR "Invalid texture format"
# define XPM_SPRITE_ERROR "Invalid sprite format"
# define WRONG_TEXTURES "Can't load textures"
# define WRONG_SPRITE "Can't load sprite"
# define MALLOC_ERROR "Malloc error"
# define IMAGE_ERROR "Image error"
# define WINDOW_ERROR "Window error"

typedef struct	s_d_spr
{
	double	sprx;
	double	spry;
	double	id;
	double	tx;
	double	ty;
	int		scr_x;
	int		h;
	int		starty;
	int		endy;
	int		w;
	int		startx;
	int		endx;
	int		texx;
	int		texy;
}				t_d_spr;

typedef struct	s_walls
{
	double	camerax;
	double	rayx;
	double	rayy;
	int		mapx;
	int		mapy;
	double	sdx;
	double	sdy;
	double	ddx;
	double	ddy;
	double	wall_d;
	int		stepx;
	int		stepy;
	int		side;
	int		hit;
	int		lh;
	int		start;
	int		end;
	double	wallx;
	int		texx;
	double	step;
	double	texpos;
	int		texy;
}				t_walls;

typedef struct	s_color
{
	char	*type;
	int		r;
	int		g;
	int		b;
	int		color;
}				t_color;

typedef struct s_keys {
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
}				t_keys;

typedef struct	s_spr
{
	double	x;
	double	y;
}				t_spr;

typedef struct  s_img
{
	void	*img;
	char	*ad;
	int		bpp;
	int		ll;
	int		end;
	int		w;
	int		h;
}               t_img;

typedef struct	s_map
{
	t_keys	keys;
	
	void	*mlx;
	void	*win;
	int		winh;
	int		winw;

	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;

	int		map_len;
	int		str_len;
	char	**map;
	char	*map_str;
	int		x_player;
	int		y_player;

	void	*img;
	char	*ad;
	int		bpp;
	int		ll;
	int		end;

	double	x;
	double	y;
	
	double	dx;
	double	dy;
	double	px;
	double	py;

	t_img	no_t;
	t_img	so_t;
	t_img	we_t;
	t_img	ea_t;
	t_img	spr;

	int		spr_l;
	t_spr	*sprites;

	int		screenshot;

	t_color	floor;
	t_color	ceil;
	t_walls	walls;
	t_d_spr	d_sprs;
}				t_map;

void    		my_mlx_pixel_put(t_map *data, int x, int y, int color);
int     		make_color(int r, int g, int b);
void    		draw_f_c(t_map *m);
void    		sort_sprites(int *spriteOrder, double *spriteDistance, int len);
void			set_walls_s(t_map *m, int p);
void			move_ray(t_map *m);
void			check_hit(t_map *m);
void			get_tex_color(t_map *m, t_img tex_str, unsigned int *color);
void			draw_line(t_map *m, int p);
void			count_w_c(t_map *m);
void			draw_walls(t_map *m, double **buffer);
void			set_sprites(t_map *m, double **spr_dist, int **spr_ord);
void			set_sprs_v(t_map *m, int *stripe);
void			pixel_sprs(t_map *m, int *stripe, double *buffer);
void			draw_sprs(t_map *m, int *spr_ord, double *buffer);
void			set_bitmap(t_map *m, int *fd);
void			make_screen(t_map *m);
void			draw_picture(t_map *m);
void			free_arr(char ***arr);
int				esc_close(int keycode);
int				close_all(t_map *m);
void			l_r_hook(t_map *m);
void			esc_hook(t_map *m);
void			w_s_hook(t_map *m);
void			a_d_hook(t_map *m);
int				key_hook(t_map *m);
int				pressed_key(int keycode, t_map *m);
int				unpressed_key(int keycode, t_map *m);
void			track_hooks(t_map *m);
void			set_struct(t_map *m);
void			err_first(int err);
void			err_second(int err);
void			print_err(int err);
int				write_info(char ***map, t_map *m, char **argv);
void			big_res(t_map *m);
void			calloc_clean(t_map *m, char ***map);
int				copy_map(t_map *m, char ***map);
int				check_conf(t_map *m, char ***map, int *err);
void			destroy_text(t_map *m);
void			destroy_spr(t_map *m);
int				load_images(t_map *m, int *err);
int				main_image(t_map *m);
int				check_args(t_map *m, int argc, char **argv);
char			*get_ad(void *ptr, int *bpp, int *sl, int *e);
void			ft_strcpy(char *dst, const char *src);
int				check_r(char *map_line, t_map *map_info);
int				set_walls(char *map_line, t_map *map_info, int *i);
int				check_sides(char *map_line, t_map *map_info);
int				set_f_c(char *map_line, t_color *c_type);
int				check_f_c(char *map_line, t_map *m);
int				verify_sides(char **map, int *i);
int				verify_f_c(char **map, int *i);
int				check_let(char **map, t_map *map_info);
int				check_n_s_xpm(t_map *info);
int				check_w_e_xpm(t_map *info);
int				check_spr_xpm(t_map *info);
int				check_info(char **map, t_map *info);
int				count_map_len(char **map, int i);
void			set_n(t_map *map_info);
void			set_s(t_map *map_info);
void			set_w(t_map *map_info);
void			set_e(t_map *map_info);
void			set_dir(t_map *map_info, char letter);
int				check_player(char **map_arr, t_map *map_info);
int				flood_fill(char ***map_arr, int x, int y, t_map map_info);
int				longest_str(char **map);
int				check_map(char ***map, t_map map_info);
int				load_textures(t_map *m);
int				load_sprites(t_map *m);
int				spr_arr(t_map *map_info, t_spr **sprites, int q);
int				find_sprites(t_map *map_info, t_spr **sprites);
int				get_next_line(int fd, char **line);
int				write_line(char **rest, char **line, char **buf, int *c_r);
int				check_rest(char **rest, char **line);
int				use_gnl(char ***map, char **line, char **map_str, int fd);
void			count_letters(char **map_str, int *i);
int				odd_syms(char **map_str, int *i);
int				map_syms(char **map_str, int *i);
int				check_emptys(char **map_str);

#endif