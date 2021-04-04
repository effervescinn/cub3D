#ifndef MAIN_H
# define MAIN_H
# include "libft/libft.h"
# include "raycast.h"
# include "parser.h"

void my_mlx_pixel_put(t_map *data, int x, int y, int color);
int make_color(int r, int g, int b);
void free_arr(char ***arr);
void draw_f_c(t_map *m);
void sort_sprites(int *spriteOrder, double *spriteDistance, int len);
int esc_close(int keycode);
int close_all(t_map *map_info);
int key_hook(t_map *map_info);
int pressed_key(int keycode, t_map *map_info);
int unpressed_key(int keycode, t_map *map_info);
void track_hooks(t_map *map_info);
void set_struct(t_map *map_info);
void print_err(int err);
int write_info(char ***map, t_map *map_info, char **argv);
void big_res(t_map *map_info);
void calloc_clean(t_map *map_info, char ***map);
int copy_map(t_map *m, char ***map);
int check_conf(t_map *map_info, char ***map, int *err);
void destroy_text(t_map *map_info);
void destroy_spr(t_map *map_info);
int load_images(t_map *map_info, int *err);
int main_image(t_map *m);
int check_args(t_map *m, int argc, char **argv);

#endif