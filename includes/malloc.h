/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:28:58 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/25 16:32:26 by lucocozz         ###   ########.fr       */
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

# define ALIGNMENT 8
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

															// if getpagesize() == 4096
# define TINY_PAGE_SIZE (size_t)(10 * getpagesize()) 		// 40960
# define TINY_BLOCK_SIZE (size_t)(TINY_PAGE_SIZE / 128)		// 320 (ALIGN(256 + sizeof(t_block)) == 307) 
# define SMALL_PAGE_SIZE (size_t)(34 * getpagesize())		// 139264
# define SMALL_BLOCK_SIZE (size_t)(SMALL_PAGE_SIZE / 128)	// 1088 (ALIGN(1024 + sizeof(t_block)) == 1072)

typedef struct s_block {
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
void	show_alloc_mem(void);
void	show_alloc_mem_ex(void);
void	show_alloc_mem_freed(void);

int		ft_strlen(char *str);
void	ft_putnbr_base(long nbr, char *base);
void	ft_putnbr(long nbr);
void	ft_putstr(const char *str);
void	ft_putchar(const char c);
void	ft_print_address(void *ptr);

#endif
