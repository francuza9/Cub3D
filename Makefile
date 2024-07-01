
NAME = cub3D

CC = cc

CFLAGS = -Werror -Wall -Wextra -g

BUILD_DIR = ./build/

PARSING_DIR = ./src/parsing/
EXEC_DIR = ./src/execution/
INIT_EXIT_DIR = ./src/init_exit/
UTILS_DIR = ./src/utils/

LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
MATH_FLAGS = -lm

SRCS =	main.c \
		$(addprefix $(PARSING_DIR),\
			add_layer.c\
			parse_cub_file.c\
			parse_map_1.c\
			parse_map_2.c\
			parse_map_3.c\
			parse_map_4.c\
			parse_textures_1.c\
			parse_textures_2.c\
			parse_textures_3.c\
			parse_textures_4.c)\
		$(addprefix $(INIT_EXIT_DIR),\
			init_game.c\
			mlx_hooks.c\
			exit_game.c)\
		$(addprefix $(EXEC_DIR),\
			moves.c \
			minimap.c \
			pointer.c \
			mouse.c \
			render_loops.c \
			ray_casting.c \
			start_execution.c) \
		$(addprefix $(UTILS_DIR),\
			parsing_utils.c\
			minimap_utils.c\
			split_mod.c\
			trgb_utils.c)


OBJS = $(SRCS:.c=.o)
BUILDS = $(addprefix $(BUILD_DIR), $(OBJS))

all : $(NAME)

bonus : bonus_flags all

$(NAME) : $(BUILDS) $(LIBFT)
	$(CC) $(CFLAGS)  $(BUILDS) $(LIBFT) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)

$(LIBFT) :
	cd $(LIBFT_DIR) && make

$(BUILD_DIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bonus_flags :
	@$(eval CFLAGS += -D BONUS=1)
	@$(eval NAME = $(NAME)_bonus)

clean :
	rm -rf $(BUILDS) $(BUILD_DIR)
	@cd $(LIBFT_DIR) && make clean

fclean : clean
	rm -f $(NAME) $(NAME)_bonus
	@cd $(LIBFT_DIR) && make fclean

re : fclean all

.PHONY : all clean fclean re bonus
