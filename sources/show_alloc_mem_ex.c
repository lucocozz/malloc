/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:42:50 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/23 21:41:03 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	ft_hex(long nb)
{
	const char hex[] = "0123456789abcdef";

	if (nb > 0) {
		ft_hex(nb / 16);
		ft_putchar(hex[nb % 16]);
	}
}

static void	ft_print_hex(u_char *str, uint offset)
{
	for (uint i = offset; i < offset + 16; i++)
	{
		if (str[i])
			ft_hex(str[i]);
		else
			ft_putstr("  ");
		if (i % 2 != 0)
			ft_putchar(' ');
	}
}

static void	ft_print_ascii(u_char *str, uint offset)
{
	for (uint i = offset; i < offset + 16 && str[i]; i++)
	{
		if (str[i] >= 32 && str[i] <= 126)
			ft_putchar(str[i]);
		else
			ft_putchar('.');
	}
}

static void	ft_print_memory(void *address, uint size)
{
	u_char	*tmp = (u_char *)address;

	for (uint i = 0; i < size; i += 16)
	{
		ft_putstr("    ");
		ft_print_address((void *)&tmp[i]);
		ft_putstr("  ");
		ft_print_hex(tmp, i);
		ft_putchar(' ');
		ft_print_ascii(tmp, i);
		ft_putchar('\n');
	}
}

static size_t	__print_blocks(t_page *page)
{
	size_t	total = 0;
	t_block	*block = page->blocks;

	for (uint i = 0; i < page->block_count; i++) {
		ft_putstr("  ");
		ft_print_address(((void *)block + sizeof(t_page)));
		ft_putstr(" - ");
		ft_print_address(((void *)block + block->size));
		ft_putstr(" : ");
		ft_putnbr(block->size - sizeof(t_block));
		ft_putstr(" bytes\n");
		ft_print_memory((void *)block + sizeof(t_block), block->size - sizeof(t_block));
		total += (block->size - sizeof(t_block));
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

void	show_alloc_mem_ex(void)
{
	size_t	total = 0;

	pthread_mutex_lock(&g_malloc_mutex);
	total += __print_pages(&g_heap.tiny, "TINY");
	total += __print_pages(&g_heap.small, "SMALL");
	total += __print_pages(&g_heap.large, "LARGE");
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" bytes\n");
	pthread_mutex_unlock(&g_malloc_mutex);
}
