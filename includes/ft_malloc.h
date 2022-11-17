/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:28:58 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/17 19:08:11 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <pthread.h>
# include <stdbool.h>

# define ALIGNMENT 16
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

													// if getpagesize() == 4096
# define TINY_PAGE_SIZE (4 * getpagesize()) 		// 16384
# define TINY_BLOCK_SIZE (TINY_PAGE_SIZE / 128) 	// 128
# define SMALL_PAGE_SIZE (16 * getpagesize()) 		// 65536
# define SMALL_BLOCK_SIZE (SMALL_PAGE_SIZE / 128) 	// 512
// # define LARGE_PAGE_SIZE (64 * getpagesize()) 		// 262144
// # define LARGE_BLOCK_SIZE (LARGE_PAGE_SIZE / 128) 	// 2048

typedef struct s_block {
	size_t			size;
	bool			allocated;
}	t_block;

typedef struct s_page {
	size_t			size;
	size_t			block_count;
	size_t			freed_blocks;
	t_block			*blocks;
	struct s_page	*next;
	struct s_page	*prev;
}	t_page;

typedef struct s_binding {
	size_t		count;
	t_page		*pages;
}	t_binding;

typedef struct s_heap {
	t_binding	tiny;
	t_binding	small;
	t_binding	large;
}	t_heap;

static t_heap g_heap = {
	.tiny = {
		.count = 0,
		.pages = NULL,
	},
	.small = {
		.count = 0,
		.pages = NULL,
	},
	.large = {
		.count = 0,
		.pages = NULL,
	}
};

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

#endif
