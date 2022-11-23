/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:09:48 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/23 22:17:41 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../includes/malloc.h"

#define ALLOC 20

int	main()
{
	char	*ptr;

	ptr = malloc(sizeof(char) * 64);
	free(ptr);
	// free(ptr);
	return (0);
}
