/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:44:05 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/21 14:41:37 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../includes/malloc.h"

#define ALLOC 23

int	main()
{
	char	*ptr[100];

	for (int i = 0; i < ALLOC; i++)
		ptr[i] = malloc(sizeof(char) * 64);
	for (int i = 0; i < ALLOC; i++)
		free(ptr[i]);
	return (0);
}