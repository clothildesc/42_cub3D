/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:36:25 by cscache           #+#    #+#             */
/*   Updated: 2025/10/25 15:46:07 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"

static void	draw_background(t_global *game, int col)
{
	int	y;

	y = 0;
	while (y < game->infos.wall_top)
	{
		put_pixel_to_img(&game->mlx.img_game, col, y, \
						game->config.colors.ceiling);
		y++;
	}
	y = game->infos.wall_bottom;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_to_img(&game->mlx.img_game, col, y, \
							game->config.colors.floor);
		y++;
	}
}

static void	draw_wall(t_global *game, int col)
{
	t_wall_infos	*i;
	t_img			tex;
	int				y;
	int				color;

	i = &game->infos;
	tex = game->config.textures[i->wall_dir];
	init_wall_texture(game);
	y = i->wall_top;
	while (y < i->wall_bottom)
	{
		color = get_texture_color(&tex, i);
		put_pixel_to_img(&game->mlx.img_game, col, y, color);
		i->tex_pos += i->step;
		y++;
	}
}

void	display_game(t_global *game)
{
	int		col;
	double	ray_angle;

	ray_angle = game->player.pa - (FOV / 2);
	col = 0;
	while (col < SCREEN_WIDTH)
	{
		get_distance(game, ray_angle, &game->params);
		set_wall_infos(game, ray_angle);
		draw_background(game, col);
		draw_wall(game, col);
		ray_angle += FOV / SCREEN_WIDTH;
		col++;
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win_ptr, \
								game->mlx.img_game.ptr, 0, 0);
}
