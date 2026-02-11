/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:07:38 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 17:15:00 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

long long	get_timestamp_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putendl_fd("Error: gettimeofday()", 2);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
 * check if the target door has an adjacent 0 to teleport the player
*/
bool	is_valid_door(t_global *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->config.map_width || \
						y >= game->config.map_height)
		return (false);
	return (game->config.map[y][x] == '0');
}

t_door	*get_door(t_global *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->config.doors_nb)
	{
		if (game->config.doors[i].tile.x == x && \
			game->config.doors[i].tile.y == y)
			return (&game->config.doors[i]);
		i++;
	}
	return (NULL);
}

bool	is_player_in_door_tile(t_global *game)
{
	char		**map;
	t_player	player;

	map = game->config.map;
	player = game->player;
	if (map[player.tile.y][player.tile.x] == 'Z' \
		|| map[player.tile.y][player.tile.x] == 'O')
		return (true);
	return (false);
}
