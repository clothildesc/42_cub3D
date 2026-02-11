/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_moves_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:00 by cscache           #+#    #+#             */
/*   Updated: 2025/10/20 13:49:21 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"

void	rotate_right(t_global *game)
{
	t_player	*player;

	player = &game->player;
	player->pa += player->rot_speed;
	if (player->pa < 0)
		player->pa += 2 * M_PI;
	if (player->pa > 2 * M_PI)
		player->pa -= 2 * M_PI;
}

void	rotate_left(t_global *game)
{
	t_player	*player;

	player = &game->player;
	player->pa -= player->rot_speed;
	if (player->pa < 0)
		player->pa += 2 * M_PI;
	if (player->pa > 2 * M_PI)
		player->pa -= 2 * M_PI;
}

int	close_window(void *param)
{
	t_global	*game;

	game = (t_global *)param;
	clean_exit(game, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
