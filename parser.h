#ifndef PARSER_H
# define PARSER_H
# include "libft/libft.h"
# include <mlx.h>

void ft_strcpy(char *dst, const char *src);
int check_r(char *map_line, t_map *map_info);
int set_walls(char *map_line, t_map *map_info, int *i);
int check_sides(char *map_line, t_map *map_info);
int set_f_c(char *map_line, t_color *c_type);
int check_f_c(char *map_line, t_map *m);
int verify_sides(char **map, int *i);
int verify_f_c(char **map, int *i);
int check_let(char **map, t_map *map_info);
int check_n_s_xpm(t_map *info);
int check_w_e_xpm(t_map *info);
int check_spr_xpm(t_map *info);

int check_info(char **map, t_map *map_info);
int count_map_len(char **map, int i);
void set_n(t_map *map_info);
void set_s(t_map *map_info);
void set_w(t_map *map_info);
void set_e(t_map *map_info);

void set_dir(t_map *map_info, char letter);
int check_player(char **map_arr, t_map *map_info);
int flood_fill(char ***map_arr, int x, int y, t_map map_info);
int longest_str(char **map);
int check_map(char ***map, t_map map_info);


int load_textures(t_map *map_info);
int load_sprites(t_map *map_info);
int spr_arr(t_map *map_info, t_spr **sprites, int q);
int find_sprites(t_map *map_info, t_spr **sprites);

#endif
