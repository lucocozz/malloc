/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_page_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:53:19 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/03 18:01:11 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "../includes/malloc.h"

static int	__print_pages(t_binding *binder, const char *type)
{
	ft_putstr(type);
	ft_putstr(": ");
	ft_putnbr(binder->count);
	ft_putstr(" page(s)\n");
	return (binder->count);
}

void	show_page_num(void)
{
	size_t	total = 0;

	pthread_mutex_lock(&g_heap_mutex);
	total += __print_pages(&g_heap.tiny, "TINY");
	total += __print_pages(&g_heap.small, "SMALL");
	total += __print_pages(&g_heap.large, "LARGE");
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" page(s)\n");
	pthread_mutex_unlock(&g_heap_mutex);
}
