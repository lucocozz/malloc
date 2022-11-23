/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:44:05 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/23 01:05:28 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
// #include <stdlib.h>
#include "includes/malloc.h"

#define ALLOC 500

int	main()
{
	// int		i;
	// char	*ptr[ALLOC];

	// for (i = 0; i < ALLOC; i++)
	// 	ptr[i] = malloc(sizeof(char) * 16000);
	// for (i--; i >= 0; i--)
	// 	free(ptr[i]);



	char	*str = malloc(sizeof(char) * 64);

	strcpy(str, "hello world gdgsgssrgdrdrhdrdrtgdrt");
	printf("%s\n", str);
	str = realloc(str, 5);
	str[5] = '\0';
	printf("%s\n", str);
	str = realloc(str, 128);
	strcat(str, "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	printf("%s\n", str);
	free(str);
	return (0);
}