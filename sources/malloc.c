/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:44 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/22 16:29:27 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_heap g_heap = {
	.tiny = {
		.count = 0,
		.pages = NULL,
	},
	.small = {
		.count = 0,
		.pages = NULL,
	},
	.large = {
		.count = 0,
		.pages = NULL,
	}
};

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

static size_t	__page_size_from_alloc_size(size_t alloc_size)
{
	if (alloc_size <= TINY_PAGE_SIZE)
		return (TINY_PAGE_SIZE);
	else if (alloc_size <= SMALL_PAGE_SIZE)
		return (SMALL_PAGE_SIZE);
	else
		return (alloc_size);
}

static t_page	*__alloc_page(size_t size)
{
	struct rlimit	limit;
	t_page			*page = NULL;

	size += sizeof(t_page);
	getrlimit(RLIMIT_AS, &limit);
	if (size > limit.rlim_max)
		return (NULL);
	page = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (page == MAP_FAILED)
		return (NULL);
	page->size = size;
	page->used_size = sizeof(t_page);
	page->block_count = 0;
	page->freed_count = 0;
	page->blocks = NULL;
	page->next = NULL;
	page->prev = NULL;
	return (page);
}

static t_block	*__find_fitting_block(t_page *page, size_t alloc_size)
{
	t_block	*last_block = NULL;
	t_block	*block = page->blocks;

	// Create block at start of page if none exists
	if (page->blocks == NULL) {
		page->block_count = 1;
		page->blocks = (void *)page + sizeof(t_page);
		page->blocks->next = NULL;
		page->blocks->prev = NULL;
		return (page->blocks);
	}

	// Search for a free block
	for (uint i = 0; i < page->block_count; i++) {
		if (block->allocated == false && alloc_size <= block->size)
			return (block);
		last_block = block;
		block = block->next;
	}

	// Add block at end if there is space available
	if (alloc_size <= page->size - page->used_size) {
		block = (void *)last_block + last_block->size;
		block->next = NULL;
		block->prev = last_block;
		last_block->next = block;
		page->block_count++;
		return (block);
	}
	return (NULL);
}

static t_index	__find_first_fit(t_binding *binder, size_t alloc_size)
{
	t_block	*block = NULL;
	t_page	*last_page = NULL;
	t_page	*page = binder->pages;

	// Search a page with a avalaible block
	while (page != NULL) {
		if ((block = __find_fitting_block(page, alloc_size)) != NULL)
			return ((t_index){.page = page, .block = block});
		last_page = page;
		page = page->next;
	}

	// Create a new page if none is available
	page = __alloc_page(__page_size_from_alloc_size(alloc_size));
	if (page == NULL)
		return ((t_index){NULL, NULL});
	if (last_page != NULL) {
		last_page->next = page;
		page->prev = last_page;
	}
	else
		binder->pages = page;
	binder->count++;
	return ((t_index){.page = page, .block = __find_fitting_block(page, alloc_size)});
}

static void	__block_fragmentation(t_block *block, t_page *parent)
{
	t_block	*next_block = block + block->size;

	if (block->next != NULL && block->next != next_block &&
		(size_t)(block->next - next_block) >= sizeof(t_block) + ALIGNMENT) // doesn't fragment if space is too small
	{
		next_block->next = block->next;
		block->next->prev = next_block;
		next_block->prev = block;
		next_block->allocated = false;
		next_block->parent = parent;
		next_block->size = block->next - next_block;
		block->next = next_block;
		parent->block_count++;
	}
}

static void	*__do_alloc(t_binding *binder, size_t alloc_size)
{
	t_index	index;

	index = __find_first_fit(binder, alloc_size);
	if (index.page == NULL)
		return (NULL);
	index.block->allocated = true;
	index.block->size = alloc_size;
	index.block->parent = index.page;
	index.page->used_size += index.block->size;
	__block_fragmentation(index.block, index.page);
	return ((void *)index.block + sizeof(t_block));
}

void	*malloc(size_t size)
{
	void	*alloc;
	size_t	alloc_size = ALIGN(size + sizeof(t_block));
	size_t	page_size = __page_size_from_alloc_size(alloc_size);

	if (size == 0)
		return (NULL);
	pthread_mutex_lock(&g_malloc_mutex);

	if (page_size == TINY_PAGE_SIZE)
		alloc = __do_alloc(&g_heap.tiny, alloc_size);
	else if (page_size == SMALL_PAGE_SIZE)
		alloc = __do_alloc(&g_heap.small, alloc_size);
	else
		alloc = __do_alloc(&g_heap.large, alloc_size);

	pthread_mutex_unlock(&g_malloc_mutex);
	return (alloc);
}
