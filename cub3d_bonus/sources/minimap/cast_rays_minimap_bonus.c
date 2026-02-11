/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:58:23 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 20:22:37 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

static void	init_bresenham(t_bresenham *algo, t_point_d start, t_point_d end)
{
	algo->start.x = (int)start.x;
	algo->start.y = (int)start.y;
	algo->end.x = (int)end.x;
	algo->end.y = (int)end.y;
	algo->delta.x = abs(algo->end.x - algo->start.x);
	algo->delta.y = abs(algo->end.y - algo->start.y);
	if (algo->start.x < algo->end.x)
		algo->step.x = 1;
	else
		algo->step.x = -1;
	if (algo->start.y < algo->end.y)
		algo->step.y = 1;
	else
		algo->step.y = -1;
	algo->error = algo->delta.x - algo->delta.y;
}

static void	draw_line_to_img(t_img *img, t_point_d start, t_point_d end, \
								int color)
{
	t_bresenham	algo;

	init_bresenham(&algo, start, end);
	while (true)
	{
		put_pixel_to_img(img, algo.start.x, algo.start.y, color);
		if (algo.start.x == algo.end.x && algo.start.y == algo.end.y)
			break ;
		algo.error_temp = 2 * algo.error;
		if (algo.error_temp > -algo.delta.y)
		{
			algo.error -= algo.delta.y;
			algo.start.x += algo.step.x;
		}
		if (algo.error_temp < algo.delta.x)
		{
			algo.error += algo.delta.x;
			algo.start.y += algo.step.y;
		}
	}
}

static t_point_d	game_to_minimap(t_minimap *mini, double x, double y)
{
	t_point_d	p;

	p.x = mini->offset.x + ((x / TILE_SIZE) - mini->start_col) * mini->scale;
	p.y = mini->offset.y + ((y / TILE_SIZE) - mini->start_row) * mini->scale;
	return (p);
}

static void	draw_rays_on_minimap(t_global *game, t_minimap *mini, \
								t_ray_params *params)
{
	t_point_d	start;
	t_point_d	end;

	start = game_to_minimap(mini, game->player.pos.x, game->player.pos.y);
	end = game_to_minimap(mini, params->ray_hit.x, params->ray_hit.y);
	if (!clip_ray(mini, &start, &end))
		return ;
	draw_line_to_img(&game->mlx.img_game, start, end, 0x00FFAA00);
}

void	cast_all_rays_minimap(t_global *game, t_minimap *mini)
{
	double			ray_angle;
	int				ray_count;
	int				max_rays;
	t_ray_params	params;

	max_rays = 60;
	ray_angle = game->player.pa - (FOV / 2);
	ray_count = 0;
	while (ray_count < max_rays)
	{
		get_distance(game, ray_angle, &params);
		draw_rays_on_minimap(game, mini, &params);
		ray_angle += FOV / max_rays;
		ray_count++;
	}
}
