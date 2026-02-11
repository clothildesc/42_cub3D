/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_moves_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:14:37 by cscache           #+#    #+#             */
/*   Updated: 2025/10/22 13:33:51 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"

static void	update_pos(t_global *game, double new_x, double new_y)
{
	int		tile_x;
	int		tile_y;

	tile_x = (int)(new_x / TILE_SIZE);
	tile_y = (int)(new_y / TILE_SIZE);
	if (tile_y >= 0 && tile_y < game->config.map_height
		&& tile_x >= 0 && tile_x < game->config.map_width
		&& game->config.map[tile_y][tile_x] != '1')
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
		game->player.tile.x = tile_x;
		game->player.tile.y = tile_y;
	}
}

void	move_forward(t_global *game)
{
	double		new_x;
	double		new_y;
	t_player	*player;

	player = &game->player;
	new_x = player->pos.x + cos(player->pa) * player->move_speed;
	new_y = player->pos.y + sin(player->pa) * player->move_speed;
	update_pos(game, new_x, new_y);
}

void	move_backward(t_global *game)
{
	double		new_x;
	double		new_y;
	t_player	*player;

	player = &game->player;
	new_x = player->pos.x - cos(player->pa) * player->move_speed;
	new_y = player->pos.y - sin(player->pa) * player->move_speed;
	update_pos(game, new_x, new_y);
}

void	move_left(t_global *game)
{
	double		new_x;
	double		new_y;
	t_player	*player;

	player = &game->player;
	new_x = player->pos.x + cos(player->pa - M_PI / 2) * player->move_speed;
	new_y = player->pos.y + sin(player->pa - M_PI / 2) * player->move_speed;
	update_pos(game, new_x, new_y);
}

void	move_right(t_global *game)
{
	double		new_x;
	double		new_y;
	t_player	*player;

	player = &game->player;
	new_x = player->pos.x + cos(player->pa + M_PI / 2) * player->move_speed;
	new_y = player->pos.y + sin(player->pa + M_PI / 2) * player->move_speed;
	update_pos(game, new_x, new_y);
}
