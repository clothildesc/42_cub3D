/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_moves_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:14:37 by cscache           #+#    #+#             */
/*   Updated: 2025/11/05 17:59:37 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

static void	update_pos(t_global *game, double new_x, double new_y)
{
	int		tile_x;
	int		tile_y;
	char	c;

	tile_x = new_x / TILE_SIZE;
	tile_y = new_y / TILE_SIZE;
	c = game->config.map[tile_y][tile_x];
	if (tile_y >= 0 && tile_y < game->config.map_height \
		&& c != '1' && c != 'D' && c != 'O')
	{
		game->player.pos.y = new_y;
		game->player.tile.y = tile_y;
	}
	if (tile_x >= 0 && tile_x < game->config.map_width
		&& c != '1' && c != 'D' && c != 'O')
	{
		game->player.pos.x = new_x;
		game->player.tile.x = tile_x;
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
