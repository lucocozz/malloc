/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_alloc_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:44:05 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/23 21:43:26 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../includes/malloc.h"

#define ALLOC 100

int	main()
{
	int		i;
	char	*ptr[ALLOC];

	for (i = 0; i < ALLOC; i++)
		ptr[i] = malloc(sizeof(char) * 64);
	show_alloc_mem();
	for (i--; i >= 0; i--)
		free(ptr[i]);
	show_alloc_mem();
	return (0);
}