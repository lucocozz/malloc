/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:44:05 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/23 20:22:06 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
// #include <stdlib.h>
#include "includes/malloc.h"

#define ALLOC 200

int	main()
{
	int		i;
	char	*ptr[ALLOC];

	for (i = 0; i < ALLOC; i++)
		ptr[i] = malloc(sizeof(char) * 64);
	show_alloc_mem();
	for (i--; i >= 0; i--)
		free(ptr[i]);
	return (0);
}