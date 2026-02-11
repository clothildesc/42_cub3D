/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 10:56:09 by bsuger            #+#    #+#             */
/*   Updated: 2025/10/27 11:28:25 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"

void	free_textures(t_global *game)
{
	int	i;

	i = 0;
	if (game)
	{
		while (i < 4)
		{
			if (game->config.textures[i].ptr)
			{
				mlx_destroy_image(game->mlx.ptr, game->config.textures[i].ptr);
				game->config.textures[i].ptr = NULL;
			}
			i++;
		}
	}
}

void	free_mlx(t_global *game)
{
	if (game && game->mlx.ptr)
	{
		if (game->mlx.img_game.ptr)
		{
			mlx_destroy_image(game->mlx.ptr, game->mlx.img_game.ptr);
			game->mlx.img_game.ptr = NULL;
		}
		free_textures(game);
		if (game->mlx.win_ptr)
		{
			mlx_destroy_window(game->mlx.ptr, game->mlx.win_ptr);
			game->mlx.win_ptr = NULL;
		}
		mlx_destroy_display(game->mlx.ptr);
		free(game->mlx.ptr);
		game->mlx.ptr = NULL;
	}
}

void	free_map(t_global *game)
{
	int	i;

	if (!game || !game->config.map)
		return ;
	i = 0;
	while (i <= game -> config.map_height)
	{
		ft_free((void **)&game->config.map[i]);
		i++;
	}
	ft_free((void **)&game->config.map);
}

void	destructor_game(t_global *game)
{
	int	i;

	i = 0;
	if (game)
	{
		free_mlx(game);
		free_map(game);
		while (i < 4)
		{
			ft_free((void **)&game -> config.texture_paths[i]);
			i++;
		}
		free(game);
	}
}

void	clean_exit(t_global *game, int exit_code)
{
	destructor_game(game);
	exit(exit_code);
}
