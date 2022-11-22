/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:44:05 by lucocozz          #+#    #+#             */
/*   Updated: 2022/11/22 16:34:05 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../includes/malloc.h"

#define ALLOC 500

int	main()
{
	// char	*ptr[ALLOC];

	// for (int i = 0; i < ALLOC; i++)
	// 	ptr[i] = malloc(sizeof(char) * 16000);
	// for (int i = 0; i < ALLOC; i++)
	// 	free(ptr[i]);



	char	*str = malloc(sizeof(char) * 64);

	strcpy(str, "hello world gdgsgssrgdrdrhdrdrtgdrt");
	printf("%s\n", str);
	str = realloc(str, 10);
	printf("%s\n", str);
	str = realloc(str, 128);
	strcat(str, "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	printf("%s\n", str);
	return (0);
}