/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 21:53:12 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/24 01:59:01 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <sys/types.h>

int		ft_strlen(char *str);
void	ft_putnbr_base(long nbr, char *base);
void	ft_putnbr(long nbr);
void	ft_putstr(const char *str);
void	ft_putchar(const char c);
void	ft_print_address(void *ptr);
void	ft_bzero(void *mem, size_t n);
void	*ft_memcpy(void *dest, void const *src, size_t n);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t n);
long	ft_distance(void *ptr1, void *ptr2);

#endif
