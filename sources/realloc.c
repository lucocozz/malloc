/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:41 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/22 21:22:07 by lucocozz         ###   ########.fr       */
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
		return (1);
	}
	return (0);
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

	if (block->size > sizeof(t_block) + ALIGNMENT)
	{
		if (block->next != NULL)
		{
			fragment = BLOCK_SHIFT(block, size);
			fragment->allocated = false;
			fragment->parent = page;
			fragment->size = block->size - size;
			fragment->next = block->next;
			fragment->prev = block;
			ft_memcpy(fragment->canary, CANARY, CANARY_SIZE);
			block->next = fragment;
			page->block_count++;
			page->freed_count++;
		}
		else
			page->used_size -= (block->size - size);
		block->size = size;
		__clean_fragmentation(block->next);
		return (1);
	}
	return (0);
}

static int	__check_defragmentation(t_block *block, size_t size)
{
	if (size == block->size)
		return (1);
	else if (size > block->size)
		return (__block_defragmentation(block, size));
	else
		return (__block_fragmentation(block, size));
}

void	*realloc(void *ptr, size_t size)
{
	void	*new;
	int		check;
	t_block	*block;

	if (size == 0) {
		if (ptr != NULL)
			free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));

	pthread_mutex_lock(&g_heap_mutex);
	block = BLOCK_HEADER_SHIFT_BACK(ptr);
	check = __check_defragmentation(block, BLOCK_SIZE(size));
	pthread_mutex_unlock(&g_heap_mutex);

	if (check == 1)
		return (ptr);

	new = malloc(size);
	if (new == NULL)
		return (NULL);

	pthread_mutex_lock(&g_heap_mutex);
	t_block	*new_block = BLOCK_HEADER_SHIFT_BACK(new);
	t_page	*page = new_block->parent;
	(void)page;

	if (block != NULL) {
		if (BLOCK_SIZE(size) < block->size)
			ft_memcpy(new, ptr, size);
		else
			ft_memcpy(new, ptr, block->size - sizeof(t_block));
	}
	pthread_mutex_unlock(&g_heap_mutex);
	free(ptr);
	return (new);
}
