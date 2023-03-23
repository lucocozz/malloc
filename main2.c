/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:57:40 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/23 17:50:41 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "includes/malloc.h"

# define MAX_ALLOC		1500
# define INCR			3
# define TEST_NULL(data) if (data == NULL) {ft_putstr("Data is NULL\n"); return -1;}

int	main()
{
	void *data[MAX_ALLOC];

	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		data[i] = malloc(i);
		TEST_NULL(data[i]);
		memset(data[i], 'a', i);
	}

	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		data[i] = realloc(data[i], i / 2);
		TEST_NULL(data[i]);
		char cmp[i / 2];

		memset(cmp, 'a', i / 2);
		if (memcmp(cmp, data[i], i / 2) != 0) {
			ft_putstr("Segmant corrupted\n");
			return -1;
		}
	}

	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i / 2];

		memset(cmp, 'a', i / 2);
		if (memcmp(cmp, data[i], i / 2) != 0) {
			ft_putstr("Segmant corrupted\n");
			return -1;
		}
	}

	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i / 2);
		if (memcmp(cmp, data[i], i / 2) != 0) {
			ft_putstr("Segmant corrupted\n");
			return -1;
		}
		free(data[i]);
	}
	return 0;
}
