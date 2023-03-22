/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:28:58 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/22 17:21:47 by lucocozz         ###   ########.fr       */
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
# include "libft.h"

# define MAP_UNINITIALIZED 0x4000000

# define CANARY "lucocozz_malloc"
# define CANARY_SIZE 16
# define ALIGNMENT 8
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

# define MIN_PAGE_BLOCKS 128
# define HEADER_PAGE_SIZE sizeof(t_page)

// TINY
# define TINY_BLOCK_SIZE 256
# define TINY_BLOCK_SIZE_ALIGNED ALIGN(TINY_BLOCK_SIZE + sizeof(t_block))
# define TINY_PAGE_SIZE (((MIN_PAGE_BLOCKS * TINY_BLOCK_SIZE_ALIGNED + HEADER_PAGE_SIZE) / getpagesize() + 1) * getpagesize())

// SMALL
# define SMALL_BLOCK_SIZE 2048
# define SMALL_BLOCK_SIZE_ALIGNED ALIGN(SMALL_BLOCK_SIZE + sizeof(t_block))
# define SMALL_PAGE_SIZE (((MIN_PAGE_BLOCKS * SMALL_BLOCK_SIZE_ALIGNED + HEADER_PAGE_SIZE) / getpagesize() + 1) * getpagesize())


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
