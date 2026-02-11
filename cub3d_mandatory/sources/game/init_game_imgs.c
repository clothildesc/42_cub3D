/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_imgs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:02:11 by cscache           #+#    #+#             */
/*   Updated: 2025/10/27 10:53:22 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"

static void	get_textures_data(t_global *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->config.textures[i].addr = \
		mlx_get_data_addr(game->config.textures[i].ptr, \
		&game->config.textures[i].bits_per_px, \
		&game->config.textures[i].size_line, \
		&game->config.textures[i].endian);
		i++;
	}
}

static void	init_textures(t_global *game)
{
	game->config.textures[NORTH].ptr = \
	mlx_xpm_file_to_image(game->mlx.ptr, game->config.texture_paths[NORTH], \
	&game->config.textures[NORTH].width, &game->config.textures[NORTH].height);
	game->config.textures[SOUTH].ptr = \
	mlx_xpm_file_to_image(game->mlx.ptr, game->config.texture_paths[SOUTH], \
	&game->config.textures[SOUTH].width, &game->config.textures[SOUTH].height);
	game->config.textures[WEST].ptr = \
	mlx_xpm_file_to_image(game->mlx.ptr, game->config.texture_paths[WEST], \
	&game->config.textures[WEST].width, &game->config.textures[WEST].height);
	game->config.textures[EAST].ptr = \
	mlx_xpm_file_to_image(game->mlx.ptr, game->config.texture_paths[EAST], \
	&game->config.textures[EAST].width, &game->config.textures[EAST].height);
	if (!game->config.textures[NORTH].ptr || !game->config.textures[SOUTH].ptr \
		|| !game->config.textures[WEST].ptr || !game->config.textures[EAST].ptr)
	{
		display_error_message("Failed to load image");
		clean_exit(game, EXIT_FAILURE);
	}
	get_textures_data(game);
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
		&game->mlx.img_game.bits_per_px, &game->mlx.img_game.size_line, \
		&game->mlx.img_game.endian);
}

void	init_imgs(t_global *game)
{
	init_mlx_img_game(game);
	init_textures(game);
}
