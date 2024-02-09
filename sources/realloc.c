/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:41 by lucocozz          #+#    #+#             */
/*   Updated: 2024/02/09 18:07:04 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static int	__block_defragmentation(t_block *block, size_t size)
{
	t_block	*next = block->next;
	t_page	*page = block->parent;

	if (next != NULL && next->allocated == false && block->size + next->size >= size)
	{
		block->size += next->size;
		block->next = next->next;
		page->block_count--;
		page->freed_count--;
		return (true);
	}
	return (false);
}

static void	__clean_fragmentation(t_block *block)
{
	if (block != NULL && block->next != NULL && block->next->allocated == false)
	{
		t_page	*page = block->parent;
		t_block	*next = block->next;

		block->size += next->size;
		block->next = next->next;
		if (next->next != NULL)
			next->next->prev = block;
		page->block_count--;
		page->freed_count--;
	}
}

static int __block_fragmentation(t_block *block, size_t size)
{
	t_block	*fragment;
	t_page	*page = block->parent;

	if (ft_distance(block, block->next) - size >= BLOCK_SIZE(ALIGNMENT))
	{
		if (block->next != NULL)
		{
			fragment = BLOCK_SHIFT(block, size);
			fragment->allocated = false;
			fragment->parent = page;
			fragment->size = block->size - size;
			fragment->next = block->next;
			fragment->prev = block;
			fragment->magic = MAGIC_NUMBER_BLOCK;
			block->next = fragment;
			page->block_count++;
			page->freed_count++;
		}
		else
			page->used_size -= (block->size - size);
		block->size = size;
		__clean_fragmentation(block->next);
		return (true);
	}
	return (false);
}

static int	__check_defragmentation(t_block *block, size_t size)
{
	if (size == block->size)
		return (true);
	else if (size > block->size)
		return (__block_defragmentation(block, size));
	else
		return (__block_fragmentation(block, size));
}

void	*realloc(void *ptr, size_t size)
{
	if (size == 0) {
		if (ptr != NULL)
			free(ptr);
		return (NULL);
	}
	
	if (ptr == NULL)
		return (malloc(size));

	t_block	*block = BLOCK_HEADER_SHIFT_BACK(ptr);

	if (block->magic != MAGIC_NUMBER_BLOCK)
		return (NULL);

	pthread_mutex_lock(&g_heap_mutex);
	int	is_fragmented = __check_defragmentation(block, BLOCK_SIZE(size));
	pthread_mutex_unlock(&g_heap_mutex);
	
	if (is_fragmented == true)
		return (ptr);

	void *new = malloc(size);
	if (new == NULL)
		return (NULL);

	pthread_mutex_lock(&g_heap_mutex);
	ft_strcpy(new, ptr);
	pthread_mutex_unlock(&g_heap_mutex);

	free(ptr);
	return (new);
}
