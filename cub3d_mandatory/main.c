/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:42:38 by cscache           #+#    #+#             */
/*   Updated: 2025/11/06 11:30:22 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	t_global	*game;

	if (argc != 2)
	{
		display_error_message("Wrong number of arguments");
		return (EXIT_FAILURE);
	}
	game = ft_calloc(1, sizeof(t_global));
	if (game == NULL)
		return (EXIT_FAILURE);
	if (check_args(game, argc, argv) == 1 || parsing_map(game, argv[1]) == 1)
		return (EXIT_FAILURE);
	run_game(game);
	destructor_game(game);
	return (EXIT_SUCCESS);
}
