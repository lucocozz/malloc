/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:41 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/20 22:34:28 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	*__memcpy(void *dest, void const *src, size_t n)
{
	u_char	*tmp = dest;

	for (uint i = 0; i < n; i++)
		*(tmp + i) = *(u_char *)src++;
	return (dest);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new;

	if (size == 0 && ptr != NULL) {
		free(ptr);
		return (NULL);
	}
	if ((new = malloc(size)) == NULL)
		return (NULL);
	if (ptr != NULL) {
		__memcpy(new, ptr, size);
		free(ptr);
	}
	return (new);
}
