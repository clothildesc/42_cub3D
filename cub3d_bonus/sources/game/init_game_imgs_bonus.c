/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_imgs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:02:11 by cscache           #+#    #+#             */
/*   Updated: 2025/10/31 19:09:57 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

static void	init_wall_textures(t_global *game)
{
	t_img	*wall_tex;
	int		i;

	wall_tex = game->config.wall_textures;
	i = 0;
	while (i < 4)
	{
		load_texture(game, &wall_tex[i], game->config.texture_paths[i]);
		i++;
	}
}

static void	init_door_textures(t_global *game)
{
	t_img	*open_frames;
	t_img	*closed;

	closed = &game->config.door_textures.closed;
	open_frames = game->config.door_textures.open_frame;
	load_texture(game, closed, "textures/door.xpm");
	load_texture(game, &open_frames[0], "textures/door_open_1.xpm");
	load_texture(game, &open_frames[1], "textures/door_open_2.xpm");
	load_texture(game, &open_frames[2], "textures/door_open_3.xpm");
	load_texture(game, &open_frames[3], "textures/door_open_4.xpm");
	game->config.door_textures.frame_nb = 4;
}

static void	init_mlx_img_game(t_global *game)
{
	game->mlx.img_game.ptr = mlx_new_image(game->mlx.ptr, SCREEN_WIDTH, \
															SCREEN_HEIGHT);
	if (!game->mlx.img_game.ptr)
	{
		display_error_message("Failed to create mlx image game");
		clean_exit(game, EXIT_FAILURE);
	}	
	game->mlx.img_game.addr = mlx_get_data_addr(game->mlx.img_game.ptr, \
											&game->mlx.img_game.bits_per_px, \
											&game->mlx.img_game.size_line, \
											&game->mlx.img_game.endian);
}

void	init_imgs(t_global *game)
{
	init_mlx_img_game(game);
	init_wall_textures(game);
	init_door_textures(game);
}
