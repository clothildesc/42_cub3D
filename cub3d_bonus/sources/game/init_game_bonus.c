/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:35:03 by cscache           #+#    #+#             */
/*   Updated: 2025/10/30 11:00:54 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

void	init_ray_params(t_ray_params *params)
{
	ft_bzero(params, sizeof(*params));
	params->found_wall = false;
	params->map.x = 0;
	params->map.y = 0;
}

static void	set_player_position(t_player *player)
{
	player->pos.x = player->tile.x * TILE_SIZE + (TILE_SIZE / 2);
	player->pos.y = player->tile.y * TILE_SIZE + (TILE_SIZE / 2);
	if (player->dir == 'N')
		player->pa = M_PI / 2 * 3;
	if (player->dir == 'S')
		player->pa = M_PI / 2;
	if (player->dir == 'E')
		player->pa = 0;
	if (player->dir == 'W')
		player->pa = M_PI;
	player->move_speed = 0.8;
	player->rot_speed = 0.013;
}

static void	init_window(t_global *game)
{
	game->mlx.ptr = mlx_init();
	if (!game->mlx.ptr)
	{
		display_error_message("Failed to initialize mlx");
		clean_exit(game, EXIT_FAILURE);
	}
	game->mlx.win_ptr = mlx_new_window(game->mlx.ptr, SCREEN_WIDTH, \
													SCREEN_HEIGHT, "cub3d");
	if (!game->mlx.win_ptr)
	{
		display_error_message("Failed to open window");
		clean_exit(game, EXIT_FAILURE);
	}
}

void	init_game(t_global *game)
{
	init_window(game);
	init_imgs(game);
	set_player_position(&game->player);
}
