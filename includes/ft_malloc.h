/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:28:58 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/19 17:29:54 by lucocozz         ###   ########.fr       */
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
# include <sys/types.h>

# define ALIGNMENT 8
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

															// if getpagesize() == 4096
# define TINY_PAGE_SIZE (size_t)(4 * getpagesize()) 		// 16384
# define SMALL_PAGE_SIZE (size_t)(16 * getpagesize()) 		// 65536

typedef struct s_block {
	size_t			size;
	bool			allocated;
	struct s_block	*next;
	struct s_page	*parent;
}	t_block;

typedef struct s_page {
	size_t			size;
	size_t			used_size;
	uint			block_count;
	uint			freed_count;
	t_block			*blocks;
	struct s_page	*next;
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

static pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

#endif
