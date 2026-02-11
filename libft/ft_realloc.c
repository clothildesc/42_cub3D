/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuger <bsuger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:20:25 by bsuger            #+#    #+#             */
/*   Updated: 2025/10/25 16:31:18 by bsuger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *to_realloc, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	tocopy;

	if (to_realloc == NULL)
	{
		if (new_size == 0)
			return (NULL);
		return (malloc(new_size));
	}
	if (new_size == 0)
	{
		(free(to_realloc), to_realloc = NULL);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (new_size < old_size)
		tocopy = new_size;
	else
		tocopy = old_size;
	(ft_bzero(new_ptr, tocopy), ft_memcpy(new_ptr, to_realloc, tocopy));
	free(to_realloc);
	to_realloc = NULL;
	return (new_ptr);
}
