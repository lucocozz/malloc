/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:38:08 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/25 17:42:17 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/malloc.h"

int main(void)
{
    int   i;
    char  *addr;

    i = 0;
    while (i < 1024) 
    {
		addr = mmap(NULL, 4 * getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        addr[0] = 42;
		munmap(addr, 4 * getpagesize());
        i++; 
    }
    return (0);
}