/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:44:05 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/17 18:59:52 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/ft_malloc.h"

int	main()
{
	int *a = malloc(sizeof(int) * 1);
	int *b = malloc(sizeof(int) * 7);
	int	*c = malloc(sizeof(int) * 1);

	printf("%ld\n", b - a);
	printf("%ld\n", c - b);
	free(a);
	free(b);
	free(c);
	return (0);
}