/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_minimap_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:30:29 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 19:11:26 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

static void	set_minimap(t_global *game, t_minimap *mini)
{
	mini->scale = 24;
	mini->visible_height = 10;
	if (mini->visible_height > game->config.map_height)
		mini->visible_height = game->config.map_height;
	mini->visible_width = 10;
	if (mini->visible_width > game->config.map_width)
		mini->visible_width = game->config.map_width;
	mini->offset.x = 20;
	mini->offset.y = SCREEN_HEIGHT - (mini->visible_height * mini->scale) - 20;
	mini->start_col = game->player.tile.x - mini->visible_width / 2;
	if (mini->start_col < 0)
		mini->start_col = 0;
	if (mini->start_col + mini->visible_width > game->config.map_width)
		mini->start_col = game->config.map_width - mini->visible_width;
	mini->start_row = game->player.tile.y - mini->visible_height / 2;
	if (mini->start_row < 0)
		mini->start_row = 0;
	if (mini->start_row + mini->visible_height > game->config.map_height)
		mini->start_row = game->config.map_height - mini->visible_height;
}

static void	set_tile_color_on_minimap(char tile, int *color, char player_dir)
{
	if (tile == '1')
		*color = 0x1D1510;
	else if (tile == '0' || tile == player_dir || tile == 'Z')
		*color = 0xFFFFFF;
	else if (tile == 'D')
		*color = 0x630DB9;
	else if (tile == 'O')
		*color = 0xAE9BC1;
	else
		*color = 0x00909090;
}

static void	draw_pixels_on_minimap(t_global *game, t_minimap *mini, int col, \
																	int row)
{
	t_point_i	square;
	int			color;

	mini->pixel.x = mini->offset.x + (col - mini->start_col) * mini->scale;
	mini->pixel.y = mini->offset.y + (row - mini->start_row) * mini->scale;
	square.y = 0;
	while (square.y < mini->scale)
	{
		square.x = 0;
		while (square.x < mini->scale)
		{
			set_tile_color_on_minimap(game->config.map[row][col], &color, \
														game->player.dir);
			put_pixel_to_img(&game->mlx.img_game, mini->pixel.x + square.x, \
										mini->pixel.y + square.y, color);
			square.x++;
		}
		square.y++;
	}
}

static void	draw_player_on_minimap(t_global *game, t_minimap *mini)
{
	t_point_d	player;
	t_point_i	p;
	int			radius;

	player.x = mini->offset.x + ((game->player.pos.x / TILE_SIZE) - \
		mini->start_col) * mini->scale;
	player.y = mini->offset.y + ((game->player.pos.y / TILE_SIZE) \
		- mini->start_row) * mini->scale;
	radius = 4;
	p.y = -radius;
	while (p.y <= radius)
	{
		p.x = -radius;
		while (p.x <= radius)
		{
			if (p.x * p.x + p.y * p.y <= radius * radius)
				put_pixel_to_img(&game->mlx.img_game, player.x + p.x, \
									player.y + p.y, 0x00FF0000);
			p.x++;
		}
		p.y++;
	}
}

void	display_minimap(t_global *game)
{
	int			col;
	int			row;
	t_minimap	mini;

	set_minimap(game, &mini);
	row = mini.start_row;
	while (row < mini.start_row + mini.visible_height)
	{
		col = mini.start_col;
		while (col < mini.start_col + mini.visible_width)
		{
			draw_pixels_on_minimap(game, &mini, col, row);
			col++;
		}
		row++;
	}
	cast_all_rays_minimap(game, &mini);
	draw_player_on_minimap(game, &mini);
}
