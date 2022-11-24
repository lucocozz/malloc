/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:09:48 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/24 19:00:26 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "includes/malloc.h"

#define ALLOC 400

static void	__simple_alloc_free(void)
{
	ft_putstr("\n\nTEST 1: simple alloc and free\n");
	ft_putstr("--------------------------------------\n");

	char	*ptr = NULL;

	ptr = malloc(sizeof(char) * 16);
	if (ptr != NULL)
	{
		strcpy(ptr, "hello world\n");
		show_alloc_mem_ex();
		free(ptr);
		show_alloc_mem();
	}
	else
		ft_putstr("malloc() failed\n");
}

static void	__multiple_allocs(void)
{
	ft_putstr("\n\nTEST 2: multiple allocations\n");
	ft_putstr("--------------------------------------\n");

	int	*ptr[ALLOC] = { NULL };

	for (uint i = 0; i < ALLOC; i++)
		ptr[i] = malloc(sizeof(int) * 64);
	
	show_alloc_mem();

	for (uint i = 0; i < ALLOC; i++)
		free(ptr[i]);

	show_alloc_mem();
}

static void	__multiple_size(void)
{
	ft_putstr("\n\nTEST 3: multiple size\n");
	ft_putstr("--------------------------------------\n");

	void	*tiny = malloc(64);
	void	*small = malloc(30000);
	void	*large = malloc(100000);

	show_alloc_mem();

	free(tiny);
	free(small);
	free(large);

	show_alloc_mem();
}

static void	__last_block_freed(void)
{
	ft_putstr("\n\nTEST 4: last block freed was removed\n");
	ft_putstr("--------------------------------------\n");

	void	*ptr1 = malloc(64);
	void	*ptr2 = malloc(64);
	void	*ptr3 = malloc(64);

	free(ptr1);
	show_alloc_mem_freed();

	free(ptr3);
	show_alloc_mem_freed();

	free(ptr2);
	show_alloc_mem_freed();
}

static void	__check_defragmentation(void)
{
	ft_putstr("\n\nTEST 5: check block defragmentation\n");
	ft_putstr("--------------------------------------\n");

	void	*ptr1 = malloc(64);
	void	*ptr2 = malloc(64);
	void	*ptr3 = malloc(64);
	void	*ptr4 = malloc(64);
	void	*ptr5 = malloc(64);

	free(ptr2);
	free(ptr4);
	show_alloc_mem_freed();

	free(ptr3);
	show_alloc_mem_freed();

	free(ptr1);
	free(ptr5);
	show_alloc_mem_freed();
}

static void	__check_fragmentation(void)
{
	ft_putstr("\n\nTEST 6: check block fragmentation\n");
	ft_putstr("--------------------------------------\n");

	void	*ptr1 = malloc(64);
	void	*ptr2 = malloc(512);
	void	*ptr3 = malloc(16);
	void	*ptr4;

	show_alloc_mem_freed();
	free(ptr2);

	show_alloc_mem_freed();
	ptr4 = malloc(128);

	show_alloc_mem_freed();
	free(ptr1);
	free(ptr3);
	free(ptr4);

	show_alloc_mem_freed();
}

static void	__malloc_failed(void)
{
	ft_putstr("\n\nTEST 7: check malloc failure\n");
	ft_putstr("--------------------------------------\n");
	void	*ptr = malloc(99999999999999);

	if (ptr == NULL)
		ft_putstr("malloc() error: too big allocation\n");
	else
		ft_putstr("malloc(): success\n");
}

static void	__test_realloc(void)
{
	ft_putstr("\n\nTEST 7: check malloc failure\n");
	ft_putstr("--------------------------------------\n");

	void	*ptr = malloc(16);

	strcpy(ptr, "hello word");
	show_alloc_mem_ex();

// TODO:
	ptr = realloc(ptr, 64);
	show_alloc_mem_ex();
}

int	main()
{
	__simple_alloc_free();
	__multiple_allocs();
	__multiple_size();
	__last_block_freed();
	__check_defragmentation();
	__check_fragmentation();
	__malloc_failed();
	__test_realloc();
	return (0);
}
