/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_rays_minimap_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:16:13 by cscache           #+#    #+#             */
/*   Updated: 2025/11/03 20:24:39 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "game_bonus.h"
#include "parsing_bonus.h"

static void	init_clip_data(t_minimap_clip *clip, t_point_d *start, \
											t_point_d *end, t_minimap *mini)
{
	clip->delta.x = end->x - start->x;
	clip->delta.y = end->y - start->y;
	clip->dir[0] = -clip->delta.x;
	clip->dir[1] = clip->delta.x;
	clip->dir[2] = -clip->delta.y;
	clip->dir[3] = clip->delta.y;
	clip->dist[0] = start->x - mini->offset.x;
	clip->dist[1] = mini->offset.x + (mini->visible_width * mini->scale) \
					- start->x;
	clip->dist[2] = start->y - mini->offset.y;
	clip->dist[3] = mini->offset.y + (mini->visible_height * mini->scale) \
					- start->y;
	clip->t_in = 0.0;
	clip->t_out = 1.0;
}

static bool	check_edge(t_minimap_clip *clip, int edge)
{
	double	t;

	if (clip->dir[edge] == 0.0)
	{
		if (clip->dist[edge] < 0.0)
			return (false);
	}
	else
	{
		t = clip->dist[edge] / clip->dir[edge];
		if (clip->dir[edge] < 0.0)
		{
			if (t > clip->t_in)
				clip->t_in = t;
		}
		else
		{
			if (t < clip->t_out)
				clip->t_out = t;
		}
	}
	return (clip->t_in <= clip->t_out);
}

static bool	test_all_edges(t_minimap_clip *clip)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!check_edge(clip, i))
			return (false);
		i++;
	}
	return (true);
}

static void	apply_clip(t_point_d *start, t_point_d *end, t_minimap_clip *data)
{
	end->x = start->x + data->t_out * data->delta.x;
	end->y = start->y + data->t_out * data->delta.y;
	start->x = start->x + data->t_in * data->delta.x;
	start->y = start->y + data->t_in * data->delta.y;
}

bool	clip_ray(t_minimap *mini, t_point_d *start, t_point_d *end)
{
	t_minimap_clip	data;

	init_clip_data(&data, start, end, mini);
	if (!test_all_edges(&data))
		return (false);
	apply_clip(start, end, &data);
	return (true);
}
