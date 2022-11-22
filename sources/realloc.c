/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:41 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/22 19:59:21 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	*__memcpy(void *dest, void const *src, size_t n)
{
	char		*d = dest;
	const char	*s = src;

	while (n--)
		*d++ = *s++;
	return (dest);
}

static int	__block_defragmentation(t_block *block, size_t size)
{
	t_block	*next = block->next;
	t_page	*page = block->parent;

	if (next != NULL && next->allocated == false && block->size + next->size >= size)
	{
		block->size += next->size;
		block->next = next->next;
		next->prev = block;
		page->block_count--;
		return (1);
	}
	return (0);
}

static int __block_fragmentation(t_block *block, size_t size)
{
	t_block	*next;
	t_page	*page = block->parent;

	if (size > sizeof(t_block) + ALIGNMENT)
	{
		next = (void *)block + size;
		next->allocated = false;
		next->parent = page;
		next->size = block->size - size;
	}
	return (0);
}

static int	__check_defragmentation(t_block *block, size_t size)
{
	size += sizeof(t_block);
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

	if (size == 0) {
		if (ptr != NULL)
			free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));

	if (__check_defragmentation(ptr, size) == 1)
		return (ptr);

	new = malloc(size);
	if (new == NULL)
		return (NULL);
	__memcpy(new, ptr, size);
	free(ptr);
	return (new);
}
