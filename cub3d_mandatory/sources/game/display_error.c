/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:07:21 by cscache           #+#    #+#             */
/*   Updated: 2025/10/27 10:52:59 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"

void	display_error_message(char *message)
{
	ft_putendl_fd("Error", 2);
	if (message)
		ft_putendl_fd(message, 2);
}
