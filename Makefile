# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cscache <cscache@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/22 17:31:31 by bsuger            #+#    #+#              #
#    Updated: 2025/11/06 11:31:55 by bsuger           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0m

CFLAGS= -Wall -Wextra -Werror -g
CC = cc

OBJS_DIR = obj
INCLUDES_DIR = includes
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

INCLUDES_DIR_MAND = cub3d_mandatory/includes
SRCS_DIR_MAND = cub3d_mandatory/sources
OBJS_DIR_MAND = $(OBJS_DIR)/mandatory

INCLUDES_DIR_BONUS = cub3d_bonus/includes
SRCS_DIR_BONUS = cub3d_bonus/sources
OBJS_DIR_BONUS = $(OBJS_DIR)/bonus

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft -lm -lz

INCLUDES_MAND = -I$(INCLUDES_DIR_MAND) -I$(LIBFT_DIR) -I$(MLX_DIR)
INCLUDES_BONUS = -I$(INCLUDES_DIR_BONUS) -I$(LIBFT_DIR) -I$(MLX_DIR)

NAME = cub3d

HEADERS_MAND = $(INCLUDES_DIR_MAND)/cub3d.h \
			$(INCLUDES_DIR_MAND)/parsing.h \
			$(INCLUDES_DIR_MAND)/game.h

HEADERS_BONUS = $(INCLUDES_DIR_BONUS)/cub3d_bonus.h \
			$(INCLUDES_DIR_BONUS)/game_bonus.h \
			$(INCLUDES_DIR_BONUS)/parsing_bonus.h

SRCS_MAND = $(SRCS_DIR_MAND)/game/init_destroy.c \
		$(SRCS_DIR_MAND)/game/display_error.c \
		$(SRCS_DIR_MAND)/game/init_game_imgs.c \
		$(SRCS_DIR_MAND)/game/init_game.c \
		$(SRCS_DIR_MAND)/game/manage_moves.c \
		$(SRCS_DIR_MAND)/game/manage_moves_utils.c \
		$(SRCS_DIR_MAND)/game/manage_moves_utils_2.c \
		$(SRCS_DIR_MAND)/game/cast_rays.c \
		$(SRCS_DIR_MAND)/game/display_game.c \
		$(SRCS_DIR_MAND)/game/display_game_utils.c \
		$(SRCS_DIR_MAND)/game/run_game.c \
		$(SRCS_DIR_MAND)/parsing/check_args.c \
		$(SRCS_DIR_MAND)/parsing/parse_file.c \
		$(SRCS_DIR_MAND)/parsing/extract_map.c \
		$(SRCS_DIR_MAND)/parsing/flood_fill.c \
		$(SRCS_DIR_MAND)/parsing/pass_line.c \
		$(SRCS_DIR_MAND)/parsing/transform_map.c \
		$(SRCS_DIR_MAND)/parsing/extract_rgb.c \
		$(SRCS_DIR_MAND)/parsing/extract_rgb_utils.c \
		$(SRCS_DIR_MAND)/parsing/parse_file_utils.c \
		cub3d_mandatory/main.c \

SRCS_BONUS = $(SRCS_DIR_BONUS)/game/init_destroy_bonus.c \
		$(SRCS_DIR_BONUS)/game/display_error_bonus.c \
		$(SRCS_DIR_BONUS)/game/init_game_imgs_bonus.c \
		$(SRCS_DIR_BONUS)/game/init_game_imgs_utils_bonus.c \
		$(SRCS_DIR_BONUS)/game/init_game_bonus.c \
		$(SRCS_DIR_BONUS)/game/manage_moves_bonus.c \
		$(SRCS_DIR_BONUS)/game/manage_moves_utils_bonus.c \
		$(SRCS_DIR_BONUS)/game/manage_moves_utils_2_bonus.c \
		$(SRCS_DIR_BONUS)/game/cast_rays_bonus.c \
		$(SRCS_DIR_BONUS)/game/display_game_bonus.c \
		$(SRCS_DIR_BONUS)/game/display_game_utils_bonus.c \
		$(SRCS_DIR_BONUS)/game/run_game_bonus.c \
		$(SRCS_DIR_BONUS)/minimap/display_minimap_bonus.c \
		$(SRCS_DIR_BONUS)/minimap/cast_rays_minimap_bonus.c \
		$(SRCS_DIR_BONUS)/minimap/clip_rays_minimap_bonus.c \
		$(SRCS_DIR_BONUS)/doors/open_door_bonus.c \
		$(SRCS_DIR_BONUS)/doors/open_door_utils_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/check_args_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/parse_file_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/extract_map_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/flood_fill_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/pass_line_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/transform_map_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/extract_rgb_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/extract_rgb_utils_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/parse_file_utils_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/check_doors_bonus.c \
		$(SRCS_DIR_BONUS)/parsing/check_textures_bonus.c \
		cub3d_bonus/main_bonus.c \

OBJS_MAND = $(SRCS_MAND:%.c=$(OBJS_DIR_MAND)/%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJS_DIR_BONUS)/%.o)

all: $(NAME)

bonus: .bonus

.bonus: $(LIBFT) $(MLX) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@touch .bonus
	@rm -f .mandatory
	@echo "$(COLOUR_GREEN)✅ BONUS COMPILATION DONE$(COLOUR_END)"

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(OBJS_DIR_MAND)/$(SRCS_DIR_MAND)/%.o: $(SRCS_DIR_MAND)/%.c $(HEADERS_MAND)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES_MAND) -O3 -c $< -o $@

$(OBJS_DIR_MAND)/cub3d_mandatory/%.o: cub3d_mandatory/%.c $(HEADERS_MAND)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES_MAND) -O3 -c $< -o $@

$(OBJS_DIR_BONUS)/$(SRCS_DIR_BONUS)/%.o: $(SRCS_DIR_BONUS)/%.c $(HEADERS_BONUS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -O3 -c $< -o $@

$(OBJS_DIR_BONUS)/cub3d_bonus/%.o: cub3d_bonus/%.c $(HEADERS_BONUS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -O3 -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJS_MAND)
	$(CC) $(CFLAGS) $(OBJS_MAND) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@touch .mandatory
	@rm -f .bonus
	@echo "$(COLOUR_GREEN)✅ MANDATORY COMPILATION DONE$(COLOUR_END)"

clean:
	@make clean -C $(LIBFT_DIR) 1>/dev/null
	@/bin/rm -rf $(OBJS_DIR)
	@rm -f .bonus .mandatory
	@echo "$(COLOUR_GREEN)🧹 clean done$(COLOUR_END)"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) 1>/dev/null
	@if [ -d "$(MLX_DIR)" ]; then \
		make clean -C $(MLX_DIR) 1>/dev/null; \
	fi
	@echo "$(COLOUR_GREEN)🧹 fclean done$(COLOUR_END)"

re: fclean all

re_bonus: fclean bonus

dev: all clean

val:
	@make -s dev
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./cub3d ./maps/good/subject_map.cub

valbad:
	@make -s dev
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./cub3d ./maps/bad/forbidden.cub

.PHONY: all bonus clean fclean re re_bonus dev val valbad
