/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:48 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/20 21:49:29 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	__link_blocks(t_page *page, t_block *first, t_block *second)
{
	first->size += second->size;
	first->next = second->next;
	page->block_count--;
	page->freed_count--;
}

static void	__clean_last_block(t_page *page)
{
	t_block	*block = page->blocks;

	for (uint i = 0; i < page->block_count - 2; i++)
		block = block->next;
	if (block->next->allocated == false) {
		page->used_size -= block->next->size;
		page->block_count--;
		page->freed_count--;
		block->next = NULL;
	}
}

static void	__block_defragmentation(t_page *page, t_block *block)
{
	t_block	*prev = NULL;
	t_block	*current = page->blocks;

	if (current == block)
		return ;
	while (current != block) {
		prev = current;
		current = current->next;
	}
	if (prev->allocated == false)
		__link_blocks(page, prev, current);
	if (current->next != NULL && current->next->allocated == false) {
		if (prev->allocated != false)
			prev = current;
		__link_blocks(page, prev, current);
	}
	__clean_last_block(page);
}

static t_binding	*__get_binder(t_page *page)
{
	if (page->size == TINY_PAGE_SIZE + sizeof(t_page))
		return (&g_heap.tiny);
	else if (page->size == SMALL_PAGE_SIZE + sizeof(t_page))
		return (&g_heap.small);
	else
		return (&g_heap.large);
}

static void	__free_page(t_page *page)
{
	t_binding	*binder = __get_binder(page);

	if (page->prev != NULL)
		page->prev->next = page->next;
	if (page->next != NULL)
		page->next->prev = page->prev;
	binder->count--;
	if (binder->pages == page)
		binder->pages = NULL;
	munmap(page, page->size);
}

void	free(void *ptr)
{
	t_block	*block = (t_block *)ptr - sizeof(t_block);
	t_page	*page = block->parent;

	pthread_mutex_lock(&g_malloc_mutex);

	block->allocated = false;
	page->freed_count++;
	if (page->freed_count == page->block_count)
		__free_page(page);
	else
		__block_defragmentation(page, block);

	pthread_mutex_unlock(&g_malloc_mutex);
}
