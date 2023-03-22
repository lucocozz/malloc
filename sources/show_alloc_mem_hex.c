/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:42:50 by lucocozz          #+#    #+#             */
/*   Updated: 2023/02/10 01:38:19 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static size_t	__print_blocks(t_page *page)
{
	size_t	total = 0;
	t_block	*block = page->blocks;

	for (uint i = 0; i < page->block_count; i++)
	{
		if (block->allocated == true)
		{
			ft_putstr("  ");
			ft_print_address(((void *)block + HEADER_PAGE_SIZE));
			ft_putstr(" - ");
			ft_print_address(((void *)block + block->size));
			ft_putstr(" : ");
			ft_putnbr(block->size - sizeof(t_block));
			ft_putstr(" bytes\n");
			print_memory((void *)block + sizeof(t_block), block->size - sizeof(t_block));
			total += (block->size - sizeof(t_block));
		}
		block = block->next;
	}
	return (total);
}

static size_t	__print_pages(t_binding *binder, const char *type)
{
	size_t	total = 0;
	t_page	*page = binder->pages;

	for (uint i = 0; i < binder->count; i++) {
		ft_putstr(type);
		ft_putstr(" : ");
		ft_print_address((void *)page);
		ft_putchar('\n');
		total += __print_blocks(page);
		page = page->next;
	}
	return (total);
}

void	show_alloc_mem_hex(void)
{
	size_t	total = 0;

	pthread_mutex_lock(&g_heap_mutex);
	total += __print_pages(&g_heap.tiny, "TINY");
	total += __print_pages(&g_heap.small, "SMALL");
	total += __print_pages(&g_heap.large, "LARGE");
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" bytes\n");
	pthread_mutex_unlock(&g_heap_mutex);
}
