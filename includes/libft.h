/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 21:53:12 by lucocozz          #+#    #+#             */
/*   Updated: 2023/02/09 18:59:14 by lucocozz         ###   ########.fr       */
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
void	*ft_memcpy(void *dst, void const *src, size_t n);

#endif
