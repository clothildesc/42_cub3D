/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:06:04 by cscache           #+#    #+#             */
/*   Updated: 2025/10/30 14:34:12 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"

int	key_release(int keycode, void *param)
{
	t_global	*game;

	game = (t_global *)param;
	if (keycode == KEY_W)
		game->key.w = 0;
	else if (keycode == KEY_S)
		game->key.s = 0;
	else if (keycode == KEY_A)
		game->key.a = 0;
	else if (keycode == KEY_D)
		game->key.d = 0;
	else if (keycode == KEY_LEFT)
		game->key.left = 0;
	else if (keycode == KEY_RIGHT)
		game->key.right = 0;
	else if (keycode == KEY_ESC || keycode == KEY_Q)
		game->key.quit = 0;
	return (EXIT_SUCCESS);
}

int	key_press(int keycode, void *param)
{
	t_global	*game;

	game = (t_global *)param;
	if (keycode == KEY_W)
		game->key.w = 1;
	else if (keycode == KEY_S)
		game->key.s = 1;
	else if (keycode == KEY_A)
		game->key.a = 1;
	else if (keycode == KEY_D)
		game->key.d = 1;
	else if (keycode == KEY_LEFT)
		game->key.left = 1;
	else if (keycode == KEY_RIGHT)
		game->key.right = 1;
	else if (keycode == KEY_ESC || keycode == KEY_Q)
		game->key.quit = 1;
	return (EXIT_SUCCESS);
}

void	update_player(t_global *game)
{
	if (game->key.w)
		move_forward(game);
	if (game->key.s)
		move_backward(game);
	if (game->key.d)
		move_right(game);
	if (game->key.a)
		move_left(game);
	if (game->key.left)
		rotate_left(game);
	if (game->key.right)
		rotate_right(game);
	if (game->key.quit)
		clean_exit(game, EXIT_SUCCESS);
}
