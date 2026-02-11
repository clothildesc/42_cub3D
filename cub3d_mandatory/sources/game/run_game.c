/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:10:29 by cscache           #+#    #+#             */
/*   Updated: 2025/10/25 15:43:08 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"

int	render(t_global *game)
{
	update_player(game);
	display_game(game);
	return (0);
}

void	run_game(t_global *game)
{
	init_game(game);
	mlx_loop_hook(game->mlx.ptr, &render, game);
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx.win_ptr, 17, 0, close_window, game);
	mlx_loop(game->mlx.ptr);
}
