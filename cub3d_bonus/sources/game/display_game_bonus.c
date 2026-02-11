/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:36:25 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 20:32:35 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

static void	draw_background(t_global *game, int col)
{
	int	y;

	y = 0;
	while (y < game->wall.top)
	{
		put_pixel_to_img(&game->mlx.img_game, col, y, \
						game->config.colors.ceiling);
		y++;
	}
	y = game->wall.bottom;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_to_img(&game->mlx.img_game, col, y, \
							game->config.colors.floor);
		y++;
	}
}

static void	set_texture(t_global *game)
{
	char			tile;
	t_ray_params	*p;
	t_wall			*wall;
	t_door			*door;

	p = &game->params;
	wall = &game->wall;
	tile = game->config.map[(int)p->map.y][(int)p->map.x];
	if (tile == '1')
		wall->tex.img = game->config.wall_textures[wall->dir];
	else if (tile == 'D' || tile == 'O')
	{
		door = get_door(game, p->map.x, p->map.y);
		if (!door)
			return ;
		if (door->is_portal)
			wall->tex.img = \
				game->config.door_textures.open_frame[door->curr_frame];
		else
			wall->tex.img = game->config.door_textures.closed;
	}
}

static void	draw_wall(t_global *game, int col)
{
	t_wall	*wall;
	int		y;
	int		color;

	wall = &game->wall;
	set_texture(game);
	init_texture(game);
	y = wall->top;
	while (y < wall->bottom)
	{
		color = get_texture_color(&wall->tex.img, wall);
		put_pixel_to_img(&game->mlx.img_game, col, y, color);
		wall->tex.pos += wall->tex.step;
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
}
