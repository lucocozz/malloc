/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:44 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/17 19:09:31 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

static pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

size_t	page_size_from_alloc_size(alloc_size)
{
	if (alloc_size <= TINY_PAGE_SIZE)
		return (TINY_PAGE_SIZE);
	else if (alloc_size <= SMALL_PAGE_SIZE)
		return (SMALL_PAGE_SIZE);
	else
		return (alloc_size);
}

int	alloc_page(t_page **page, size_t size)
{
	struct rlimit	limit;
	t_page			*new_page = NULL;

	size += sizeof(t_page);
	getrlimit(RLIMIT_AS, &limit);
	if (size > limit.rlim_max)
		return (-1);
	new_page = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new_page == MAP_FAILED)
		return (-1);
	new_page->size = size;
	new_page->block_count = 0;
	new_page->freed_blocks = 0;
	*page = new_page;
	return (0);
}

void	*alloc_block(t_binding binder, size_t size)
{
	if (binder.pages == NULL) {
		if (alloc_page(binder.pages, page_size_from_alloc_size(size)) == -1);
			return (NULL);
		binder.count++;
	}
}

void	*malloc(size_t size)
{
	void	*alloc = NULL;
	size_t	align_size = ALIGN(size);
	size_t	page_size = page_size_from_alloc_size(align_size);

	pthread_mutex_lock(&g_malloc_mutex);

	if (page_size == TINY_PAGE_SIZE)
		alloc = alloc_block(g_heap.tiny, align_size);
	else if (page_size == SMALL_PAGE_SIZE)
		alloc = alloc_block(g_heap.small, align_size);
	else
		alloc = alloc_block(g_heap.large, align_size);

	pthread_mutex_unlock(&g_malloc_mutex);
	return (alloc);
}
