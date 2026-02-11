/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_moves_utils_2_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:00 by cscache           #+#    #+#             */
/*   Updated: 2025/11/01 14:39:27 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

void	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
}

void	rotate_right(t_global *game)
{
	t_player	*player;

	player = &game->player;
	player->pa += player->rot_speed;
	normalize_angle(game->player.pa);
}

void	rotate_left(t_global *game)
{
	t_player	*player;

	player = &game->player;
	player->pa -= player->rot_speed;
	normalize_angle(game->player.pa);
}

int	mouse_move(int x, int y, t_global *game)
{
	static int	last_x = SCREEN_WIDTH / 2;
	double		rotation_speed;
	int			delta_x;

	(void)y;
	rotation_speed = 0.002;
	delta_x = x - last_x;
	game->player.pa += delta_x * rotation_speed;
	normalize_angle(game->player.pa);
	mlx_mouse_move(game->mlx.ptr, game->mlx.win_ptr, \
					SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	last_x = SCREEN_WIDTH / 2;
	return (0);
}

int	close_window(void *param)
{
	t_global	*game;

	game = (t_global *)param;
	clean_exit(game, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
