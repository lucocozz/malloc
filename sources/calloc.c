/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:48 by lucocozz          #+#    #+#             */
/*   Updated: 2023/02/09 16:48:41 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	size_t	mem_size = nmemb * size;
	void	*ptr = malloc(mem_size);

	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, mem_size);
	return (ptr);
}
