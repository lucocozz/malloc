/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:44:05 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/04 19:43:32 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/ft_malloc.h"

int	main()
{
	char *mem = NULL;

	mem = malloc(sizeof(char) * 10);
	printf("%p\n", mem);
	return (0);
}