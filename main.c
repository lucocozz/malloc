/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:09:48 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/23 22:12:14 by lucocozz         ###   ########.fr       */
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
		strcpy(ptr, "hello world\n\t\r\v");
		show_alloc_mem_hex();
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

	void	*tiny = malloc(16);
	void	*small = malloc(512);
	void	*large = malloc(4096);

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

	void	*ptr1 = malloc(32);
	void	*ptr2 = malloc(128);
	void	*ptr3 = malloc(16);
	void	*ptr4;

	show_alloc_mem_freed();
	free(ptr2);

	show_alloc_mem_freed();
	ptr4 = malloc(64);

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
	else {
		ft_putstr("malloc(): success\n");
		free(ptr);
	}
	show_alloc_mem_freed();
}

static void	__test_realloc(void)
{
	ft_putstr("\n\nTEST 8: test basic realloc\n");
	ft_putstr("--------------------------------------\n");

	void	*ptr = malloc(32);

	memcpy(ptr, "hello word test toto", 21);
	show_alloc_mem_hex();

	ptr = realloc(ptr, 64);
	show_alloc_mem_hex();

	ptr = realloc(ptr, 8);
	show_alloc_mem_hex();

	free(ptr);
	show_alloc_mem_freed();
}

static void	__realloc_defragmentation(void)
{
	ft_putstr("\n\nTEST 9: realloc (de)fragmentation\n");
	ft_putstr("--------------------------------------\n");

	void	*ptr1 = malloc(16);
	void	*ptr2 = malloc(128);
	void	*ptr3 = malloc(16);

	void	*ptr;

	show_alloc_mem_freed();

	ptr = realloc(ptr2, 16);
	show_alloc_mem_freed();

	if (ptr == ptr2)
		ft_putstr("address is equal\n");

	ptr = realloc(ptr2, 32);
	show_alloc_mem_freed();

	if (ptr == ptr2)
		ft_putstr("address is equal\n");

	free(ptr1);
	free(ptr2);
	free(ptr3);
	show_alloc_mem_freed();
}

// static void	*__test_thread(void *none)
// {
// 	(void)none;
// 	void	*ptr[20];


// 	for (uint i = 0; i < 20; i++) {
// 		ptr[i] = malloc(16);
// 		usleep(1000);
// 	}
// 	show_alloc_mem_freed();

// 	for (uint i = 0; i < 20; i++) {
// 		free(ptr[i]);
// 		usleep(1000);
// 	}
// 	show_alloc_mem_freed();

// 	return (NULL);
// }

// static void	__thread_safe_test(void)
// {
// 	ft_putstr("\n\nTEST 10: thread safe test\n");
// 	ft_putstr("--------------------------------------\n");
	
// 	pthread_t	thread1;
// 	pthread_t	thread2;

// 	pthread_create(&thread1, NULL, &__test_thread, NULL);
// 	pthread_create(&thread2, NULL, &__test_thread, NULL);
// 	pthread_join(thread1, NULL);
// 	pthread_join(thread2, NULL);
	
// 	show_alloc_mem_freed();
// }

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
	__realloc_defragmentation();
	// __thread_safe_test();
	ft_putnbr(TINY_PAGE_SIZE / getpagesize()); ft_putchar('\n');
	ft_putnbr(SMALL_PAGE_SIZE / getpagesize()); ft_putchar('\n');
	return (0);
}
