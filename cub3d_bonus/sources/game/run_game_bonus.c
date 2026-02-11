/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:10:29 by cscache           #+#    #+#             */
/*   Updated: 2025/11/05 08:55:06 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

int	render(t_global *game)
{
	update_player(game);
	update_doors(game);
	display_game(game);
	display_minimap(game);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win_ptr, \
								game->mlx.img_game.ptr, 0, 0);
	return (0);
}

void	run_game(t_global *game)
{
	init_game(game);
	mlx_loop_hook(game->mlx.ptr, &render, game);
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx.win_ptr, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->mlx.win_ptr, 17, 0, close_window, game);
	mlx_loop(game->mlx.ptr);
}
