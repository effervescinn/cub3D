#ifndef PARSER_H
# define PARSER_H
# include "libft/libft.h"
# include <mlx.h>

void ft_strcpy(char *dst, const char *src);
int check_r(char *map_line, t_map *map_info);
int check_sides(char *map_line, t_map *map_info);
int set_f_c(char *map_line, t_color *c_type);
int check_f_c(char *map_line, t_map *m);
int check_info(char **map, t_map *map_info);
int count_map_len(char **map, int i);
void set_dir(t_map *map_info, char letter);
int check_player(char **map_arr, t_map *map_info);
int flood_fill(char ***map_arr, int x, int y, t_map map_info);
int longest_str(char **map);
int check_map(char ***map, t_map map_info);


int load_textures(t_map *map_info);
int load_sprites(t_map *map_info);
int find_sprites(t_map *map_info, t_spr **sprites);

#endif
