/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:48 by lucocozz          #+#    #+#             */
/*   Updated: 2024/02/09 18:04:47 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	__merge_blocks(t_page *page, t_block *first, t_block *second)
{
	first->size += second->size;
	first->next = second->next;
	if (second->next != NULL)
		second->next->prev = first;
	page->block_count--;
	page->freed_count--;
}

static void	__clean_last_block(t_block *block)
{
	t_block	*prev = block->prev;
	t_page	*page = block->parent;

	if (block->next == NULL) {
		page->used_size -= block->size;
		page->block_count--;
		page->freed_count--;
		if (prev != NULL)
			prev->next = NULL;
	}
}

static void	__block_defragmentation(t_page *page, t_block *block)
{
	t_block	*prev = NULL;
	t_block	*next = NULL;

	prev = block->prev;
	if (prev != NULL && prev->allocated == false) {
		__merge_blocks(page, prev, block);
		block = prev;
	}
	next = block->next;
	if (next != NULL && next->allocated == false)
		__merge_blocks(page, block, next);
	__clean_last_block(block);
}

static t_binding	*__get_binder(t_page *page)
{
	if (page->size == TINY_PAGE_SIZE)
		return (&g_heap.tiny);
	else if (page->size == SMALL_PAGE_SIZE)
		return (&g_heap.small);
	else
		return (&g_heap.large);
}

static void	__free_page(t_page *page)
{
	t_binding	*binder = __get_binder(page);

	if (binder->count > 1)
	{
		binder->count--;
		if (binder->pages == page)
			binder->pages = page->next;
	
		if (page->prev != NULL)
			page->prev->next = page->next;
		if (page->next != NULL)
			page->next->prev = page->prev;

		if (munmap(page, page->size) == -1)
			ft_putstr("free(): munmap error\n");
	}
}

void	free(void *ptr)
{
	t_page	*page;
	t_block	*block = BLOCK_HEADER_SHIFT_BACK(ptr);

	if (ptr == NULL)
		return;
	if (block->magic != MAGIC_NUMBER_BLOCK)
		return;

	pthread_mutex_lock(&g_heap_mutex);

	page = block->parent;
	block->allocated = false;
	page->freed_count++;
	if (page->freed_count == page->block_count)
		__free_page(page);
	else
		__block_defragmentation(page, block);

	pthread_mutex_unlock(&g_heap_mutex);
}
