/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:44 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/04 19:49:13 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	void	*mem = NULL;
	int		offset = 0;

	pthread_mutex_lock(&g_malloc_mutex);
	
	mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (mem == MAP_FAILED)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&g_malloc_mutex);
	return (mem);
}
