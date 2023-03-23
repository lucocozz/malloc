/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:44 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/23 02:04:44 by lucocozz         ###   ########.fr       */
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

pthread_mutex_t g_heap_mutex = PTHREAD_MUTEX_INITIALIZER;

static size_t	__page_size_from_block_size(size_t block_size)
{
	if (block_size <= TINY_BLOCK_SIZE_MAX)
		return (TINY_PAGE_SIZE);
	else if (block_size <= SMALL_BLOCK_SIZE_MAX)
		return (SMALL_PAGE_SIZE);
	else
		return (LARGE_PAGE_SIZE(block_size));
}

static t_page	*__alloc_page(size_t size)
{
	struct rlimit	limit;
	t_page			*page = NULL;

	getrlimit(RLIMIT_AS, &limit);
	if (size > limit.rlim_max)
		return (NULL);
	page = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (page == MAP_FAILED)
		return (NULL);
	page->size = size;
	page->used_size = HEADER_PAGE_SIZE;
	page->block_count = 0;
	page->freed_count = 0;
	page->blocks = NULL;
	page->next = NULL;
	page->prev = NULL;
	return (page);
}

static t_block	*__find_fitting_block(t_page *page, size_t block_size)
{
	t_block	*last_block = NULL;
	t_block	*block = page->blocks;

	// Create block at start of page if none exists
	if (page->blocks == NULL) {
		page->block_count = 1;
		page->blocks = PAGE_HEADER_SHIFT(page);
		page->blocks->next = NULL;
		page->blocks->prev = NULL;
		page->used_size += block_size;
		return (page->blocks);
	}

	// Search for a free block
	for (uint i = 0; i < page->block_count; i++) {
		if (block->allocated == false && block_size <= block->size) {
			page->freed_count--;
			return (block);
		}
		last_block = block;
		block = block->next;
	}

	// Add block at end if there is space available
	if (block_size <= page->size - page->used_size) {
		block = BLOCK_SHIFT(last_block, last_block->size);
		block->next = NULL;
		block->prev = last_block;
		last_block->next = block;
		page->used_size += block_size;
		page->block_count++;
		return (block);
	}
	return (NULL);
}

static t_index	__find_first_fit(t_binding *binder, size_t block_size)
{
	t_block	*block = NULL;
	t_page	*last_page = NULL;
	t_page	*page = binder->pages;

	// Search a page with a avalaible block
	while (page != NULL) {
		if ((block = __find_fitting_block(page, block_size)) != NULL)
			return ((t_index){.page = page, .block = block});
		last_page = page;
		page = page->next;
	}

	// Create a new page if none is available
	page = __alloc_page(__page_size_from_block_size(block_size));
	if (page == NULL)
		return ((t_index){NULL, NULL});
	if (last_page != NULL) {
		last_page->next = page;
		page->prev = last_page;
	}
	else
		binder->pages = page;
	binder->count++;
	return ((t_index){.page = page, .block = __find_fitting_block(page, block_size)});
}

static int	__block_fragmentation(t_block *block)
{
	t_page	*parent = block->parent;
	t_block	*next_block = BLOCK_SHIFT(block, block->size);

	if (block->next != NULL && block->next != next_block &&
		(size_t)(next_block - block->next) >= BLOCK_SIZE(ALIGNMENT)) // doesn't fragment if space is too small
	{
		next_block->next = block->next;
		block->next->prev = next_block;
		next_block->prev = block;
		next_block->allocated = false;
		next_block->parent = parent;
		next_block->size = block->next - next_block;
		block->next = next_block;
		parent->block_count++;
		parent->freed_count++;
		return (1);
	}
	return (0);
}

static void	*__do_alloc(t_binding *binder, size_t block_size)
{
	t_index	index;

	index = __find_first_fit(binder, block_size);
	if (index.page == NULL)
		return (NULL);
	ft_memcpy(index.block->canary, CANARY, CANARY_SIZE);
	index.block->allocated = true;
	index.block->size = block_size;
	index.block->parent = index.page;
	__block_fragmentation(index.block);
	// VALGRIND_MALLOCLIKE_BLOCK(index.block, block_size, 0, 0);
	return (BLOCK_HEADER_SHIFT(index.block));
}

void	*malloc(size_t size)
{
	void	*alloc;
	size_t	block_size = BLOCK_SIZE(size);

	if (size == 0)
		return (NULL);
	pthread_mutex_lock(&g_heap_mutex);

	if (block_size <= TINY_BLOCK_SIZE_MAX)
		alloc = __do_alloc(&g_heap.tiny, block_size);
	else if (block_size <= SMALL_BLOCK_SIZE_MAX)
		alloc = __do_alloc(&g_heap.small, block_size);
	else
		alloc = __do_alloc(&g_heap.large, block_size);

	pthread_mutex_unlock(&g_heap_mutex);
	return (alloc);
}
