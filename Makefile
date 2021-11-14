INCLUDES = includes
GAME_BASE = game_base
PARSER = parser
SCREENSHOT = screenshot
UTILS = utils
GAME_BASE_C = $(GAME_BASE)/check_args.c $(GAME_BASE)/draw_f_c_sprites.c $(GAME_BASE)/draw_line.c $(GAME_BASE)/draw_picture.c $(GAME_BASE)/draw_sprites.c $(GAME_BASE)/draw_walls.c $(GAME_BASE)/errors.c $(GAME_BASE)/handle_hooks.c $(GAME_BASE)/hooks.c $(GAME_BASE)/load_images.c $(GAME_BASE)/main.c
UTILS_C = $(UTILS)/my_mlx_pixel_put.c $(UTILS)/utils.c
PARSER_C = $(PARSER)/check_conf.c $(PARSER)/check_emptys.c $(PARSER)/check_let.c $(PARSER)/check_sides_floor_color.c $(PARSER)/copy_map.c $(PARSER)/floodfill.c $(PARSER)/get_next_line.c $(PARSER)/set_dir.c $(PARSER)/write_info_utils.c $(PARSER)/write_info.c
SCREENSHOT_C = $(SCREENSHOT)/make_screen.c
FILES = $(GAME_BASE_C) $(UTILS_C) $(PARSER_C) $(SCREENSHOT_C)
OFILES = $(patsubst %.c,%.o,$(FILES))
DEPS = $(patsubst %.o,%.d,$(OFILES))
DEPFLAGS = -MMD -MF $(@:.o=.d)
CC = gcc
NAME = cub3D
FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -framework OpenGL -framework AppKit
MLX = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
FT_LIB = $(LIBFT_DIR)/libft.a
MLX_DIR = ./minilibx
LIBFT_DIR = ./libft
LIBS = $(MLX_LIB) $(FT_LIB)



all:		$(NAME)

$(NAME):	$(OFILES)
			make -C $(LIBFT_DIR)
			make -C $(MLX_DIR)
			$(CC) $(FLAGS) $(MLX_FLAGS) $(LIBS) $(OFILES) -o $(NAME) 
-include $(DEPS)

%.o: 		%.c
			$(CC) $(FLAGS) -I$(INCLUDES) -c $< $(DEPFLAGS) -o $(<:.c=.o)

clean:
			make clean -C $(LIBFT_DIR)
			make clean -C $(MLX_DIR)
			rm -rf $(OFILES)
			rm -rf $(DEPS)
			rm -rf screen.bmp

fclean:		clean
			make fclean -C $(LIBFT_DIR)
			rm -rf $(NAME) 

re:			fclean all


.PHONY:		all clean fclean re
