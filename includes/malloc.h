/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:28:58 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/23 19:18:04 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/types.h>
# include <valgrind/valgrind.h>
# include "libft.h"

# define CANARY "lucocozz_malloc"
# define CANARY_SIZE 16
# define ALIGNMENT 8
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

# define BLOCK_SIZE(size) ALIGN(size + sizeof(t_block))
# define BLOCK_DISTANCE(block1, block2) (size_t)((void*)block2 - (void*)block1)

// BLOCK
# define HEADER_BLOCK_SIZE sizeof(t_block)
# define BLOCK_HEADER_SHIFT(block) ((void*)block + sizeof(t_block))
# define BLOCK_HEADER_SHIFT_BACK(ptr) ((t_block*)((void*)ptr - sizeof(t_block)))
# define BLOCK_SHIFT(block, size) ((void*)block + size)

// PAGE
# define HEADER_PAGE_SIZE sizeof(t_page)
# define PAGE_HEADER_SHIFT(page) ((void*)page + sizeof(t_page))
# define PAGE_HEADER_SHIFT_BACK(ptr) ((void*)ptr - sizeof(t_page))


# define MIN_PAGE_BLOCKS 128

// TINY
# define TINY_BLOCK_SIZE_MAX 256
# define TINY_BLOCK_SIZE BLOCK_SIZE(TINY_BLOCK_SIZE_MAX)
# define TINY_PAGE_SIZE (((MIN_PAGE_BLOCKS * TINY_BLOCK_SIZE_MAX + HEADER_PAGE_SIZE) / getpagesize() + 1) * getpagesize())

// SMALL
# define SMALL_BLOCK_SIZE_MAX 2048
# define SMALL_BLOCK_SIZE BLOCK_SIZE(SMALL_BLOCK_SIZE_MAX)
# define SMALL_PAGE_SIZE (((MIN_PAGE_BLOCKS * SMALL_BLOCK_SIZE_MAX + HEADER_PAGE_SIZE) / getpagesize() + 1) * getpagesize())

// LARGE
# define LARGE_PAGE_SIZE(size) (((BLOCK_SIZE(size) + HEADER_PAGE_SIZE) / getpagesize() + 1) * getpagesize())



typedef struct s_block {
	char			canary[CANARY_SIZE];
	size_t			size;
	bool			allocated;
	struct s_page	*parent;
	struct s_block	*next;
	struct s_block	*prev;
}	t_block;

typedef struct s_page {
	size_t			size;
	size_t			used_size;
	uint			block_count;
	uint			freed_count;
	t_block			*blocks;
	struct s_page	*next;
	struct s_page	*prev;
}	t_page;

typedef struct s_index {
	t_block		*block;
	t_page		*page;
}	t_index;

typedef struct s_binding {
	size_t		count;
	t_page		*pages;
}	t_binding;

typedef struct s_heap {
	t_binding	tiny;
	t_binding	small;
	t_binding	large;
}	t_heap;

extern t_heap g_heap;
extern pthread_mutex_t g_heap_mutex;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*calloc(size_t nmemb, size_t size);
void	show_alloc_mem(void);
void	show_alloc_mem_hex(void);
void	show_alloc_mem_freed(void);
void	show_page_num(void);
void	print_memory(void *address, uint size);

#endif
