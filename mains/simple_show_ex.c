/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_alloc_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:44:05 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/23 21:34:11 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../includes/malloc.h"

#define ALLOC 20

int	main()
{
	int		i;
	char	*ptr[ALLOC];

	for (i = 0; i < ALLOC; i++) {
		ptr[i] = malloc(sizeof(char) * 64);
		strcpy(ptr[i], "hello world rhgdrg srgd drhg rdhg 35346");
	}
	show_alloc_mem_ex();
	for (i--; i >= 0; i--)
		free(ptr[i]);
	show_alloc_mem();
	return (0);
}