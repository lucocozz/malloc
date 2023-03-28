/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:38:08 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/27 18:05:12 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int i;
    char *addr;

    i = 0;
    #ifdef LIBFT
        printf("mmap\n");
    #else
        printf("malloc\n");
    #endif
    while (i < 1024) 
    {
        #ifdef LIBFT
            addr = mmap(NULL, 4 * getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        #else
            addr = malloc(4 * getpagesize());
        #endif
        addr[0] = 42;
        #ifdef LIBFT
            munmap(addr, 4 * getpagesize());
        #else
            free(addr);
        #endif
        i++; 
    }
    return (0);
}