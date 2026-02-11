/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:24:22 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 17:10:09 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

void	setup_horizontal_ray(t_global *game, double ray_angle, \
								t_ray_params *params)
{
	normalize_angle(ray_angle);
	params->ray_hit.y = floor(game->player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (sin(ray_angle) > 0)
	{
		params->ray_hit.y += TILE_SIZE;
		params->step.y = TILE_SIZE;
	}
	else
	{
		params->ray_hit.y -= 0.0001;
		params->step.y = -TILE_SIZE;
	}
	params->ray_hit.x = game->player.pos.x + \
	(params->ray_hit.y - game->player.pos.y) / tan(ray_angle);
	params->step.x = TILE_SIZE / tan(ray_angle);
	if ((cos(ray_angle) < 0 && params->step.x > 0) \
	|| (cos(ray_angle) > 0 && params->step.x < 0))
		params->step.x = -params->step.x;
	params->ray_dir.x = cos(ray_angle);
	params->ray_dir.y = sin(ray_angle);
}

void	setup_vertical_ray(t_global *game, double ray_angle, \
								t_ray_params *params)
{
	normalize_angle(ray_angle);
	params->ray_hit.x = floor(game->player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (cos(ray_angle) > 0)
	{
		params->ray_hit.x += TILE_SIZE;
		params->step.x = TILE_SIZE;
	}
	else
	{
		params->ray_hit.x -= 0.0001;
		params->step.x = -TILE_SIZE;
	}
	params->ray_hit.y = game->player.pos.y + \
	(params->ray_hit.x - game->player.pos.x) * tan(ray_angle);
	params->step.y = TILE_SIZE * tan(ray_angle);
	if ((sin(ray_angle) < 0 && params->step.y > 0) \
	|| (sin(ray_angle) > 0 && params->step.y < 0))
		params->step.y = -params->step.y;
	params->ray_dir.x = cos(ray_angle);
	params->ray_dir.y = sin(ray_angle);
}

double	cast_ray(t_global *game, t_ray_params *params)
{
	char	tile;

	while (!params->found_wall)
	{
		params->map.x = (int)floor(params->ray_hit.x / TILE_SIZE);
		params->map.y = (int)floor(params->ray_hit.y / TILE_SIZE);
		if (params->map.x < 0 || params->map.x >= game->config.map_width \
			|| params->map.y < 0 || params->map.y >= game->config.map_height)
			break ;
		tile = game->config.map[(int)params->map.y][(int)params->map.x];
		if (tile == '1' || tile == 'D' || tile == 'O')
			params->found_wall = true;
		else
		{
			params->ray_hit.x += params->step.x;
			params->ray_hit.y += params->step.y;
		}
	}
	return (sqrt(pow(params->ray_hit.x - game->player.pos.x, 2) + \
				pow(params->ray_hit.y - game->player.pos.y, 2)));
}

void	set_wall_dir(t_global *game, double ray_angle, bool horiz)
{
	if (horiz)
	{
		if (sin(ray_angle) > 0)
			game->wall.dir = SOUTH;
		else
			game->wall.dir = NORTH;
	}
	else
	{
		if (cos(ray_angle) > 0)
			game->wall.dir = EAST;
		else
			game->wall.dir = WEST;
	}
}

void	get_distance(t_global *game, double ray_angle, \
						t_ray_params *params)
{
	t_ray_params	horiz;
	t_ray_params	vert;
	double			horiz_dist;
	double			vert_dist;

	init_ray_params(&horiz);
	init_ray_params(&vert);
	setup_vertical_ray(game, ray_angle, &vert);
	vert_dist = cast_ray(game, &vert);
	setup_horizontal_ray(game, ray_angle, &horiz);
	horiz_dist = cast_ray(game, &horiz);
	if (horiz_dist < vert_dist)
	{
		*params = horiz;
		(*params).distance = horiz_dist;
		set_wall_dir(game, ray_angle, true);
	}
	else
	{
		*params = vert;
		(*params).distance = vert_dist;
		set_wall_dir(game, ray_angle, false);
	}
}
