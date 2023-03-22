/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_freed.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:42:50 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/21 22:04:26 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static size_t	__print_blocks(t_page *page)
{
	size_t	total = 0;
	t_block	*block = page->blocks;

	for (uint i = 0; i < page->block_count; i++) {
		ft_putstr("  ");
		ft_print_address(((void *)block + HEADER_PAGE_SIZE));
		ft_putstr(" - ");
		ft_print_address(((void *)block + block->size));
		ft_putstr(" : ");
		if (block->allocated == true) {
			ft_putnbr(block->size - sizeof(t_block));
			ft_putstr(" bytes\n");
			total += (block->size - sizeof(t_block));
		}
		else
			ft_putstr("freed\n");
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

void	show_alloc_mem_freed(void)
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
