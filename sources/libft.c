/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:33:54 by lucocozz          #+#    #+#             */
/*   Updated: 2023/02/09 16:46:10 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_is_alnum(char c)
{
	if ((c >= '0' && c <= '9') ||
	(c >= 'a' && c <= 'z') ||
	(c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

static void	ft_print_nb(long int nb, char *base, int size)
{
	if (nb >= size)
		ft_print_nb(nb / size, base, size);
	write(1, &base[nb % size], 1);
}

static int	ft_check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = i;
		if (!ft_is_alnum(base[i]))
			return (0);
		while (base[++j])
			if (base[i] == base[j])
				return (0);
		i++;
	}
	return (i < 2 ? 0 : 1);
}

void	ft_putnbr_base(long nbr, char *base)
{
	long int	nb;

	nb = (long int)nbr;
	if (ft_check_base(base))
	{
		if (nb < 0)
		{
			write(1, "-", 1);
			nb *= -1;
		}
		ft_print_nb(nb, base, ft_strlen(base));
	}
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr(long nbr)
{
	ft_putnbr_base(nbr, "0123456789");
}

void	ft_putchar(const char c)
{
	write(STDOUT_FILENO, &c, 1);
}

void	ft_putstr(const char *str)
{
	size_t	len = 0;

	while (str[len] != '\0')
		len++;
	write(STDOUT_FILENO, str, len);
}

void	ft_print_address(void *ptr)
{
	long	address = (long)ptr;

	ft_putstr("0x");
	ft_putnbr_base(address, "0123456789ABCDEF");
}

void	ft_bzero(void *mem, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)mem;
	for (i = 0; i < n; ++i)
		ptr[i] = 0;
}
