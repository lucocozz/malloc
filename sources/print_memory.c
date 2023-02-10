/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 01:31:53 by lucocozz          #+#    #+#             */
/*   Updated: 2023/02/10 02:31:23 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#define HEXASET "0123456789abcdef"
#define HEX_SPACING "  "
#define LINE_SPACING "    "
#define BYTE_SPACING ' '

static void	__print_hexa_byte(char c)
{
	ft_putchar(HEXASET[(c & 0xF0) >> 4]);
	ft_putchar(HEXASET[c & 0x0F]);
}

static void	__print_hexa_line(char *mem, uint size)
{
	uint i;

	for (i = 0; i < 16 && i < size; ++i) {
		__print_hexa_byte(mem[i]);
		if (i % 2 != 0)
			ft_putchar(BYTE_SPACING);
	}
	for (; i < 16; ++i) {
		ft_putstr(HEX_SPACING);
		if (i % 2 != 0)
			ft_putchar(BYTE_SPACING);
	}
	ft_putchar(' ');
	for (i = 0; i < 16 && i < size; ++i) {
		if (mem[i] >= 32 && mem[i] <= 126)
			ft_putchar(mem[i]);
		else
			ft_putchar('.');
	}
	ft_putchar('\n');
}

void	print_memory(void *address, uint size)
{
	char	*mem = (char *)address;

	for (uint i = 0; i < size; i += 16) {
		ft_putstr(LINE_SPACING);
		ft_print_address((void *)mem);
		ft_putstr(HEX_SPACING);
		__print_hexa_line(mem + i, size - i);
	}
}
