/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:23:00 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 20:47:53 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

void	teleport_player(int door_idx, t_global *game)
{
	int			target;
	int			rand_idx;
	t_point_i	target_door;

	target = -1;
	while (target == -1)
	{
		rand_idx = rand() % game->config.doors_nb;
		if (rand_idx != door_idx)
			target = rand_idx;
	}
	target_door.x = game->config.doors[target].tile.x;
	target_door.y = game->config.doors[target].tile.y;
	if (is_valid_door(game, target_door.x, target_door.y + 1))
		target_door.y += 1;
	else if (is_valid_door(game, target_door.x + 1, target_door.y))
		target_door.x += 1;
	else if (is_valid_door(game, target_door.x, target_door.y - 1))
		target_door.y -= 1;
	else if (is_valid_door(game, target_door.x - 1, target_door.y))
		target_door.x -= 1;
	game->player.pos.x = target_door.x * TILE_SIZE + TILE_SIZE / 2;
	game->player.pos.y = target_door.y * TILE_SIZE + TILE_SIZE / 2;
	game->player.tile.x = target_door.x;
	game->player.tile.y = target_door.y;
}

void	try_open_door(t_global *game)
{
	t_point_d	d;
	t_door		*doors;
	t_player	player;
	int			i;

	i = 0;
	doors = game->config.doors;
	player = game->player;
	while (i < game->config.doors_nb)
	{
		d.x = (doors[i].tile.x + 0.5) * TILE_SIZE - player.pos.x;
		d.y = (doors[i].tile.y + 0.5) * TILE_SIZE - player.pos.y;
		if (sqrt(d.x * d.x + d.y * d.y) < TILE_SIZE * 2 \
			&& !doors[i].is_open)
		{
			ft_putendl_fd("Door triggered...", 1);
			doors[i].is_open = true;
			doors[i].open_time = get_timestamp_in_ms();
			doors[i].is_portal = (rand() % 2 == 0);
			doors[i].state = OPENED;
			game->config.map[doors[i].tile.y][doors[i].tile.x] = 'O';
			break ;
		}
		i++;
	}
}

void	manage_portal(t_global *game, t_door *door, long long now, \
														long long elapsed)
{
	if (door->state == OPENED && elapsed > 120)
	{
		door->curr_frame++;
		door->open_time = now;
		if (door->curr_frame == game->config.door_textures.frame_nb - 1)
		{
			ft_putendl_fd("Portal active...", 1);
			door->state = PORTAL_ACTIVE;
			door->open_time = now;
		}
	}
	else if (door->state == PORTAL_ACTIVE && elapsed > 800)
	{
		ft_putendl_fd("Teleportation!", 1);
		teleport_player(door->index, game);
		door->is_portal = 0;
		door->curr_frame = 0;
		door->is_open = false;
		door->state = CLOSED;
		game->config.map[door->tile.y][door->tile.x] = 'D';
	}
}

void	manage_sliding_door(t_global *game, t_door *door, long long now, \
														long long elapsed)
{
	if (door->state == OPENED)
	{
		game->config.map[door->tile.y][door->tile.x] = 'Z';
		ft_putendl_fd("Door opened!", 1);
		door->state = HIDDEN;
		door->open_time = now;
	}
	else if (door->state == HIDDEN)
	{
		if (elapsed > 4000 && !is_player_in_door_tile(game))
		{
			door->is_open = false;
			door->state = CLOSED;
			game->config.map[door->tile.y][door->tile.x] = 'D';
			ft_putendl_fd("Door closed!", 1);
		}
	}
}

void	update_doors(t_global *game)
{
	long long	now;
	long long	elapsed;
	t_door		*door;
	int			i;

	now = get_timestamp_in_ms();
	i = 0;
	while (i < game->config.doors_nb)
	{
		door = &game->config.doors[i];
		if (!door->is_open)
		{
			i++;
			continue ;
		}
		elapsed = now - door->open_time;
		if (door->is_portal)
			manage_portal(game, door, now, elapsed);
		else
			manage_sliding_door(game, door, now, elapsed);
		i++;
	}
}
