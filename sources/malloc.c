/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:44 by lucocozz          #+#    #+#             */
/*   Updated: 2022/10/30 18:12:32 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	void	*mem = NULL;

	pthread_mutex_lock(&g_malloc_mutex);
	
	pthread_mutex_unlock(&g_malloc_mutex);
	return (mem);
}
